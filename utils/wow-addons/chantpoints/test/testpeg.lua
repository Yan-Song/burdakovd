#!/usr/bin/lua5.1

local start = os.clock()
require "peg"

-- options
--peg.debug = true
peg.profile = true
peg.cache = {}

--- калькулятор
local function accum(u,op,v)
    if op=="+" then return u+v
    elseif op=="-" then return u-v
    elseif op=="*" then return u*v
    elseif op=="/" then return u/v
    end
end

local space = peg.S" \n\t":star()
local digit = peg.R"09"
local sign = peg.S"+-"
local unsigned = digit:plus()
local number = (sign^{0,1}*unsigned*("."*unsigned)^{0,1}):C()/tonumber*space
local Open = "(" * space
local Close = ")" * space
local mulop = peg.S"/*":C() * space
local sumop = peg.S"-+":C() * space

-- необходимо сделать Fake(), т.к. тут рекурсия value -> sum -> mul -> value
-- реальная формула для value доопределяется тремя строками ниже
local value = peg.Fake()
local mul = (value * (mulop*value):Cg():star()):Cf(accum)
local sum = (mul * (sumop*mul):Cg():star()):Cf(accum)
--local sum = (number * (sumop*number):Cg():star()):Cf(accum)

value:define(Open*sum*Close + number)

local expression = sum * peg.eof
--local expression = peg.S("2+"):star()

--print("expression built in "..os.clock()-start.." sec.")

-- benchmarking
local cases = {100,200,500,750,1000,1500,2000,3000,4000}
local lengths = {}
local times = {}
local calls = {}
local real_calls = {}

for x,y in ipairs(cases) do
    local tmp="2"
    for i=1, y do tmp = tmp.."+2" end
    --print("\nCase #"..x..", string length is "..#tmp)

    local start = os.clock()
    local startcalls = peg.calls
    local startreal_calls = peg.real_calls

    local pp,g=expression.match(tmp,1)
    --print"matched"
    --print(g)
    --local r=g()


    table.insert(calls,peg.calls-startcalls)
    table.insert(real_calls,peg.real_calls-startreal_calls)
    table.insert(times,os.clock()-start)
    table.insert(lengths,#tmp)
    --print("total fuction calls: "..peg.calls-startcalls)
    --print("total time spent: "..os.clock()-start.." sec.")
end

print("lengths,calls,times")
for i=1, #cases do
    print(lengths[i]..","..calls[i]..","..real_calls[i]..","..times[i])
end

