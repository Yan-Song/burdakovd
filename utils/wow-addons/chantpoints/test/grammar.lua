#!/usr/bin/lua5.1

-- http://en.wikipedia.org/wiki/Earley%27s_algorithm

------------------ Constructors:
--[[
Grammar:Set({symbol1, symbol2...}) - matches if any of these symbols matches
Grammar:Set("abcdef...") - matches if any of these characters matches
]]

--[[
Grammar:Range("az") matches character between 'a' and 'z'
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

Grammar = {}

---------------------------------------------------------------------------
-- local functions

local private = {}

local function debugPrint(s)
    print("DEBUG: "..s)
end

local function pass(x)
    return x
end

local function concat(x,y)
    z = {}
    for i, q in pairs(x) do
        table.insert(z,q)
    end
    for i, q in pairs(y) do
        table.insert(z,q)
    end
    return z
end

local mt = {

}

local function Symbol(b)
    t = {}
    t.Repeat = private.Repeat

    t.rules = {}
    t.builder = b or pass;
    
    setmetatable(t, mt)

    return t
end

--------------------------------------

function Grammar:Set(s)
    t = Symbol()
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


function Grammar:Range(s)
    t = {}
    for i=s:byte(1), s:byte(2) do
        table.insert(t, string.char(i))
    end
    return Grammar:Any(t)
end


function private.Repeat(p, Min, Max)
    local Repeat = private.Repeat
    if Max==nil and (Min==nil or Min<=0) then -- p*
        t=Symbol()
        table.insert(t.rules,{t,p}) -- t -> t p
        table.insert(t.rules,{Epsilon}) -- t -> Eps
        return t
    elseif Max==nil and Min~=nil and Min>0 then -- p{Min,}
        return Repeat(p,Min,Min) + Repeat(p,nil,nil)
    elseif Max~=nil and (Min==nil or Min<=0) then
        if Max>0 then                           -- p{,Max}
            tmp = Repeat(p,0,Max-1)
            return tmp*p + tmp
        elseif Max==0 then
            return Epsilon -- p{,0}
        elseif Max<0 then
            return Dead -- impossible
        end
    elseif Max~=nil and Min~=nil and Min>0 then
        if Max<Min then
            return Dead -- for example p{5,3}
        elseif Max>Min then -- for ex. p{3,5}
            return Repeat(p,Min,Min) * Repeat(p,nil,Max-Min)
        elseif Max==Min then
            return Repeat(p,Min-1,Min-1)*p
        end
    else assert(false)
    end
end

function mt.__add(a,b)
    return Grammar:Any({a, b})
end

function mt.__mul(a,b)
    t = Symbol(concat)
    table.insert(t.rules, {a,b})
    return t
end

Grammar.Epsilon = Symbol()
table.insert(Grammar.Epsilon.rules, {})

Grammar.Dead = Symbol()

----------------------------------
----------- testing --------------
----------------------------------


local digit = Symbol()
local number = digit:Repeat(1,nil)

