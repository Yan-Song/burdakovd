#!/usr/bin/lua5.1

local private = {}
peg = {}

--[[
Теория: http://pdos.csail.mit.edu/~baford/packrat/popl04/peg-popl04.pdf

Структура этого модуля. Каждый узел (например p) имеет функцию match
p.match(string,position), returns "nil" (match failed) or  "pos, builder" (match succeeded)

builder is a function, that returns abstract syntax tree for this node.
builder() actally returns list of {capture1, capture2... }


peg.Fake() - возвращает нерабочий узел, который потом нужно доопределить через :define()
p:define(q) - p <- q
это может быть нужно для каких-нибудь рекурсивных правил, типа: A <- "x"A / eps
    c = peg.terminal("x")
    a = Fake()
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
peg.lookahead(patt) = peg.NOT(peg.NOT(x))
-patt is equivalent to peg.NOT(patt)


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
        tmp.match = function(string,position)
            local pos, b = p.match(string,position)
            if pos == nil then return end
            return pos, function()
                            local capture = {string:sub(position,pos-1)}
                            return private.push(b(),capture)
                        end
        end
        return tmp
    end

private.methods.define =
    function(p, q)
        p.match = function(...) return q.match(...) end
    end

-- constants
private.NoCapture = function() return {} end

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

peg.terminal =
    function(c)
        local tmp = peg.Fake()
        tmp.match =
            function(string,position)
                if (position > #string) or (string:byte(position)~=c:byte(1)) then return nil
                else return position+1, private.NoCapture
                end
            end
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
        local tmp = peg.Fake()
        tmp.match =
            function(string,position)
                local p1, b1 = x1.match(string,position)
                if p1 == nil then return nil end
                local p2, b2 = x2.match(string,p1)
                if p2 == nil then return nil end
                return p2,
                    function()
                        return private.tconcat(b1(), b2())
                    end
            end
        return tmp
    end
private.mt.__mul = private.magic(peg.concat)

peg.alternative =
    function(x1,x2)
        local tmp = peg.Fake()
        tmp.match =
            function(string,position)
                local p1, b1 = x1.match(string,position)
                if p1 ~= nil then return p1, b1 end
                local p2, b2 = x2.match(string,position)
                if p2 ~= nil then return p2, b2 end
                return nil
            end
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
        tmp.match =
            function(string,position)
                local p,b = patt.match(string,position)
                if p==nil then return position, private.NoCapture
                else return nil
                end
            end
        return tmp
    end
private.mt.__unm = peg.NOT

private.lookahead = function(p) return peg.NOT(peg.NOT(p)) end

peg.P =
    function(z)
        if type(z)=="boolean" then
            local tmp = Fake()
            if z then tmp.match = function(s,p) return p, NoCapture end
            else tmp.match = function(...) return nil end
            end
        end
        print("Can't do peg.P(",z,")")
    end
-- тесты

local text = "ttttest"
print("text: "..text)
local pattern = ((peg.terminal("t")*(-peg.terminal("e")))^{0,nil}):C()
local position, generator = pattern.match(text, 1)
if position then
    print("matched "..(position-1).." characters")
    local tree = generator()
    print("tree: ", tree)
    for x,y in ipairs(tree) do
        print("Capture #"..x..":")
        for i,j in pairs(y) do
            print(" ",i,j)
        end
    end
else
    print("No match")
end

