#!/usr/bin/lua5.1

local private = {}
peg = {}

--[[
Теория: http://pdos.csail.mit.edu/~baford/packrat/popl04/peg-popl04.pdf

Структура этого модуля. Каждый узел (например p) имеет функцию match
p.match(string,position), returns "nil" (match failed) or  "pos, builder" (match succeeded)

builder() returns list of {capture1, capture2... }


peg.Fake() - возвращает нерабочий узел, который потом нужно доопределить через :define()
p:define(q) - p <- q
это может быть нужно для каких-нибудь рекурсивных правил, типа: A <- "x"A / eps
    c = peg.terminal("x")
    a = peg.Fake()
    a:define(c*a + peg.epsilon)
peg.dot - any single character
peg.epsilon - "empty"
peg.terminal(c) - matches character "c"
peg.concat(x,y) or x*y - sequence
peg.alternative(x,y) or x+y - priority alternation, x/y in original notation
peg.rep(patt,n) - repeat patt exactly n times
peg.rep(patt,{m,n}) - repeat patt at least m and at most n times
peg.rep(patt,{m,nil}) - repeat patt at least m times
patt^z is the same as peg.rep(patt,z)
peg.NOT(patt) - not predicate
-patt is equivalent to peg.NOT(patt)
p-q is equivalent to (-q)*p
peg.lookahead(patt) = peg.NOT(peg.NOT(x))
peg.P(string) - matches whole string
peg.P(number) - any number characters
peg.P(boolean) - constant pattern
peg.R("az") - matches any single character in range a..z
peg.S("+-*/") - matches any single character from this string (set)
peg.Cc({values}) Creates a constant capture. This pattern matches the empty string and produces all given values as its captured values.
p:Cf(func) - folds all captured values with func
p:Cg() - groups all captured values into single capture
p:Ct() - groups all captured values into table
peg.apply(patt, func) - calls func(values) and captures result
patt / func is equivalent to peg:apply(patt,func)
patt(s) returns nil if s doesn't match patt, or list of captures
    if there were no any captures - returns prefix of s matched by patt

patt:C() - Creates a simple capture, which captures the substring of the
    subject that matches patt. The captured value is a string.

]]

private.mt = {}
private.methods = {}

function peg.Fake()
    local t={}
    for x,y in pairs(private.methods) do
        t[x] = y
    end
    setmetatable(t,private.mt)
    return t
end

private.push = function(t,x)
    table.insert(t,x)
    return t
end

private.methods.C =
    function(p)
        local tmp = peg.Fake()
        tmp.made_by = "C"
        tmp.match = private.wrap(
        function(string,position)
            local pos, b = p.match(string,position)
            if pos == nil then return end
            return pos, function()
                            local capture = {string:sub(position,pos-1)}
                            return private.push(b(),capture)
                        end
        end)
        return tmp
    end
peg.C = private.methods.C

peg.profile = false
peg.real_calls = 0
peg.calls = 0
peg.depth = 1
peg.debug = false
peg.cache = nil

private._memo =
    function(func)
        if peg.cache[func] == nil then peg.cache[func]={} end
        local cache=peg.cache[func]
        return
            function(string,position)
                if cache[string] == nil then cache[string]={} end
                local cache=cache[string]
                if cache[position] == nil then
                    --print("saved!")
                    cache[position] = {func(string,position)}
                    return unpack(cache[position])
                end
                --print("cached!!!")
                return unpack(cache[position])
            end
    end

private._debug =
    function(func)
        return
            function(...)
                local tmp="[call]"
                for i=1, peg.depth do tmp=tmp.." " end
                print(tmp..tostring(func),...)
                peg.depth = peg.depth + 1
                local results = {func(...)}
                peg.depth = peg.depth - 1
                return unpack(results)
            end
    end

private._profile =
    function(func,s)
        return function(...) peg[s]=peg[s]+1; return func(...) end
    end

private.wrap =
    function(func)
        local f=func
        if peg.debug then f=private._debug(f) end
        if peg.profile then f=private._profile(f,"real_calls") end
        if peg.cache then f=private._memo(f) end
        if peg.profile then f=private._profile(f,"calls") end
        return f
    end

private.methods.define =
    function(p, q)
        p.match = private.wrap(function(...) return q.match(...) end)
    end

-- constants
private.NoCapture = function() return {} end

peg.terminal =
    function(c)
        local tmp = peg.Fake()
        tmp.match = private.wrap(
            function(string,position)
                if (position > #string) or (string:byte(position)~=c:byte(1)) then return nil
                else return position+1, private.NoCapture
                end
            end)
        return tmp
    end

function private.tconcat(x,y)
    local tmp = {}
    for i,j in pairs(x) do table.insert(tmp,j) end
    for i,j in pairs(y) do table.insert(tmp,j) end
    return tmp
end

function private.magic(f)
    return function(...)
        local tmp = {}
        for i,z in ipairs(arg) do
            if type(z)=="table" then table.insert(tmp,z)
            else table.insert(tmp,peg.P(z))
            end
        end
        return f(unpack(tmp))
    end
end

peg.concat =
    function(x1,x2)
        if x1.made_by=="concat" then return x1.append(x2) end
        if x2.made_by=="concat" then return x2.append(x1) end
        local tmp = peg.Fake()
        --tmp.made_by = "concat"
        tmp.match = private.wrap(
            function(string,position)
                local p1, b1 = x1.match(string,position)
                if p1 == nil then return nil end
                local p2, b2 = x2.match(string,p1)
                if p2 == nil then return nil end
                return p2,
                    function()
                        return private.tconcat(b1(), b2())
                    end
            end)
        --tmp.append =
        return tmp
    end
private.mt.__mul = private.magic(peg.concat)

peg.alternative =
    function(x1,x2)
        local tmp = peg.Fake()
        tmp.match = private.wrap(
            function(string,position)
                local p1, b1 = x1.match(string,position)
                if p1 ~= nil then return p1, b1 end
                local p2, b2 = x2.match(string,position)
                if p2 ~= nil then return p2, b2 end
                return nil
            end)
        return tmp
    end
private.mt.__add = private.magic(peg.alternative)

peg.rep =
    function(patt, q)
        if type(q)=="number" then
            if q<=0 then return peg.epsilon
            else return patt*peg.rep(patt,q-1)
            end
        else
            local min, max = unpack(q)
            if max==nil then
                if min>0 then
                    return peg.rep(patt,min)*peg.rep(patt,{0,nil})
                else
                    local tmp = peg.Fake()
                    tmp:define(patt*tmp + peg.epsilon)
                    return tmp
                end
            else
                if max>0 then
                    if max==1 then return patt + peg.epsilon end
                    if min>0 then
                        return peg.rep(patt,min)*peg.rep(patt,{0, max-min})
                    else
                        return peg.rep(peg.rep(patt,{0,1}),max)
                    end
                end
                if max==0 and min==0 then
                    return peg.epsilon
                end
                if max<0 then
                    return peg.P(false)
                end
            end
        end
        print("ALAAAAAAAAAAARM in peg.rep")
    end
private.mt.__pow = peg.rep

peg.NOT =
    function(patt)
        local tmp = peg.Fake()
        tmp.match = private.wrap(
            function(string,position)
                local p,b = patt.match(string,position)
                if p==nil then return position, private.NoCapture
                else return nil
                end
            end)
        return tmp
    end
private.mt.__unm = peg.NOT

private.lookahead = function(p) return peg.NOT(peg.NOT(p)) end

peg.sub =
    function(p,q)
        return (-q)*p
    end
private.mt.__sub = private.magic(peg.sub)

peg.P =
    function(z)
        if type(z)=="boolean" then
            local tmp = peg.Fake()
            if z then tmp.match = function(s,p) return p, NoCapture end
            else tmp.match = function(...) return nil end
            end
        end
        if type(z)=="number" then
            return peg.dot^z
        end
        if type(z)=="string" then
            local s = peg.terminal(string.char(z:byte(1)))
            for i=2, #z do
                s = s * peg.terminal(string.char(z:byte(i)))
            end
            return s
        end
        if type(z)=="table" then return z end
        print("Can't do peg.P(",z,")")
    end

peg.R =
    function(c)
        local tmp = peg.Fake()
        tmp.match = private.wrap(
            function(string,position)
                if (position > #string) or
                    (string:byte(position)<c:byte(1)) or
                    (string:byte(position)>c:byte(2)) then return nil
                else return position+1, private.NoCapture
                end
            end)
        return tmp
    end

peg.S =
    function(z)
        local s = peg.terminal(string.char(z:byte(1)))
        for i=2, #z do
            s = s + peg.terminal(string.char(z:byte(i)))
        end
        return s
    end

peg.Cc =
    function(t)
        local tmp = peg.Fake()
        tmp.match = private.wrap(
            function(string,position)
                return position,
                    function()
                        if type(t)=="table" then return {t}
                        else return {{t}}
                        end
                    end
            end)
        return tmp
    end

private.fold =
    function(t, f)
        assert(#t>0)
        assert(#t[1]>0)
        s = t[1][1]
        for i=2, #t do
            s = f(s,unpack(t[i]))
        end
        return s
    end

peg.Cf =
    function(patt, func)
        local tmp = peg.Fake()
        tmp.match = private.wrap(
            function(string,position)
                local p, b = patt.match(string,position)
                if p == nil then return nil end
                return p,
                    function()
                        return {{ private.fold(b(), func) }}
                    end
            end)
        return tmp
    end
private.methods.Cf = peg.Cf

private.group =
    function(t)
        local tmp = {}
        for i,j in ipairs(t) do
            for x,y in ipairs(j) do
                table.insert(tmp,y)
            end
        end
        if #tmp>0 then return {tmp}
        else return {} end
    end

peg.Cg =
    function(patt)
        local tmp = peg.Fake()
        tmp.match = private.wrap(
            function(string,position)
                local p, b = patt.match(string,position)
                if p == nil then return nil end
                return p,
                    function()
                        return private.group(b())
                    end
            end)
        return tmp
    end
private.methods.Cg = peg.Cg

peg.Ct =
    function(patt)
        local tmp = peg.Fake()
        tmp.match = private.wrap(
            function(string,position)
                local p, b = patt.match(string,position)
                if p == nil then return nil end
                return p,
                    function()
                        return { private.group(b()) }
                    end
            end)
        return tmp
    end
private.methods.Ct = peg.Ct

peg.apply =
    function(patt, func)
        local tmp = peg.Fake()
        tmp.match = private.wrap(
            function(string,position)
                local p, b = patt.match(string,position)
                if p == nil then return nil end
                return p,
                    function()
                        local g = private.group(b())[1]
                        local r = func(unpack(g))
                        if r == nil then return {}
                        else return {{ r }}
                        end
                    end
            end)
        return tmp
    end
private.mt.__div = peg.apply

private.mt.__call =
    function(patt, string)
        local position, builder = patt:Cg().match(string, 1)
        if position==nil then return nil end
        local result = builder()
        if #result == 0 then return string:sub(1,position-1)
        else return unpack(result[1])
        end
    end

-- sugar
peg.star = function(p) return p^{0,nil} end
private.methods.star = peg.star

peg.plus = function(p) return p^{1,nil} end
private.methods.plus = peg.plus

-- peg.dot matches any single character
peg.dot = peg.Fake()
peg.dot.match =
    function(string,position)
        if position > #string then return nil
        else return position+1, private.NoCapture
        end
    end

peg.epsilon = peg.Fake()
peg.epsilon.match =
    function(string,position)
        return position, private.NoCapture
    end

peg.eof = -peg.dot

--------------------- примеры -----------------------
--- калькулятор
-- local function accum(u,op,v)
--     if op=="+" then return u+v
--     elseif op=="-" then return u-v
--     elseif op=="*" then return u*v
--     elseif op=="/" then return u/v
--     end
-- end
--
-- local space = peg.S" \n\t":star()
-- local digit = peg.R"09"
-- local sign = peg.S"+-"
-- local unsigned = digit:plus()
-- local number = (sign^{0,1}*unsigned*("."*unsigned)^{0,1}):C()/tonumber*space
-- local Open = "(" * space
-- local Close = ")" * space
-- local mulop = peg.S"/*":C() * space
-- local sumop = peg.S"-+":C() * space
--
-- -- необходимо сделать Fake(), т.к. тут рекурсия value -> sum -> mul -> value
-- -- реальная формула для value доопределяется тремя строками ниже
-- local value = peg.Fake()
-- local mul = (value * (mulop*value):Cg():star()):Cf(accum)
-- local sum = (mul * (sumop*mul):Cg():star()):Cf(accum)
--
-- value:define(number + Open*sum*Close)
--
-- local expression = sum * peg.eof
--
-- --print(expression"3 + 5*9 / (1+1) - 12 + 0.012")
--
-- print(expression(io.read()))
