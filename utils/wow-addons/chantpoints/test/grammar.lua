#!/usr/bin/lua5.1

-- http://en.wikipedia.org/wiki/Earley%27s_algorithm

------------------ Constructors:
--[[
Grammar:Set({symbol1, symbol2...}) - matches if any of these symbols matches
Grammar:Set("abcdef...") - matches if any of these characters matches
]]

--[[
Grammar:Range("az") matches any character c: 'a' <= c <= 'z'
]]

--[[
Grammar:Exact("somestring") - matches if this string matches
-]]


------------------- Methods:
--[[
p:Repeat(Min, Max)
matches if p repeats between Min and Max times (greed)
nil == inf
]]

--[[
p:Catch() - добавить в таблицу результатов фрагмент текста, соответствующий p
]]

--[[
p:Table() - собрать все результаты, выброшенные из p в одну таблицу
]]

------------------- Operations:
--[[
x+y matches if x matches or y matches
x+"somestring" is the same as x+Grammar:Exact("somestring")
]]

--[[
x*y matches if xy matches
]]

--[[
x / function, вызвать function(z1,z2,...) для где z1,z2... - результаты, выброшенные из x
и положить значения возвращаемые функцией в результаты
]]

local private = { mt={} }
Grammar = {}

---------------------------------------------------------------------------
-- local functions

function private.debugPrint(s)
    print("DEBUG: "..s)
end

function private.pass(s, first, last, x)
    assert(#x==1)
    return x[1]
end

function private.concat(s, first, last, x)
    local z = {}
    for j, y in ipairs(x) do
        for i, q in ipairs(y) do
            table.insert(z,q)
        end
    end
    return z
end

function private.Symbol(b)
    local t = {}
    t.Repeat = private.Repeat
    t.Catch = private.Catch
    t.Table = private.Table

    t.rules = {}
    t.builder = b or private.pass;
    
    setmetatable(t, private.mt)

    return t
end

--------------------------------------

function private.mt.__add(a,b)
    local a = Grammar:Exact(a)
    local b = Grammar:Exact(b)
    return Grammar:Set({a, b})
end

function private.mt.__mul(a,b)
    local a = Grammar:Exact(a)
    local b = Grammar:Exact(b)
    local t = private.Symbol(private.concat)
    table.insert(t.rules, {a,b})
    return t
end

function Grammar:Set(s)
    local t = private.Symbol()
    if type(s)=="table" then
        for i, sym in pairs(s) do
            table.insert(t.rules, {sym})
        end
        return t
    elseif type(s)=="string" then
        for i = 1, s:len() do
            table.insert(t.rules, {s:sub(i,i)})
        end
        return t
    else
        assert(false)
    end
end

function Grammar:Exact(s)
    if type(s)=="string" then
        local t = private.Symbol()
        local tmp = {}
        for i = 1, s:len() do
            table.insert(tmp, {s:sub(i,i)})
        end
        table.insert(t.rules, tmp)
        return t
    else
        return s
    end
end

function Grammar:Range(s)
    local t = {}
    for i=s:byte(1), s:byte(2) do
        table.insert(t, string.char(i))
    end
    return Grammar:Set(t)
end


function private.Repeat(p, Min, Max)
    local Repeat = private.Repeat
    if Max==nil and (Min==nil or Min<=0) then -- p*
        local t=private.Symbol()
        table.insert(t.rules,{t,p}) -- t -> t p
        table.insert(t.rules,{Grammar.Epsilon}) -- t -> Eps
        return t
    elseif Max==nil and Min~=nil and Min>0 then -- p{Min,}
        return Repeat(p,Min,Min) + Repeat(p,nil,nil)
    elseif Max~=nil and (Min==nil or Min<=0) then
        if Max>0 then                           -- p{,Max}
            local tmp = Repeat(p,0,Max-1)
            return tmp*p + tmp
        elseif Max==0 then
            return Grammar.Epsilon -- p{,0}
        elseif Max<0 then
            return Grammar.Dead -- impossible
        end
    elseif Max~=nil and Min~=nil and Min>0 then
        if Max<Min then
            return Grammar.Dead -- for example p{5,3}
        elseif Max>Min then -- for ex. p{3,5}
            return Repeat(p,Min,Min) * Repeat(p,nil,Max-Min)
        elseif Max==Min then
            return Repeat(p,Min-1,Min-1)*p
        end
    else assert(false)
    end
end

function private.CatchBuilder(s, first, last, x)
    assert(#x==1)
    table.insert(x[1],s:sub(first,last))
    return x[1]
end

function private.Catch(p)
    local t = Symbol(private.CatchBuilder)
    table.insert(t.rules, {p})
    return t
end

function private.TableBuilder(s, first, last, x)
    assert(#x==1)
    return x
end

function private.Table(p)
    local t = Symbol(private.TableBuilder)
    table.insert(t.rules, {p})
    return t
end

Grammar.Epsilon = private.Symbol()
table.insert(Grammar.Epsilon.rules, {})

Grammar.Dead = private.Symbol()



----------------------------------
----------- testing --------------
----------------------------------

local digit = Grammar:Range("09")
local number = digit:Repeat(1,nil)
