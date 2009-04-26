#!/usr/bin/lua5.1

require "peg"

-- options
--peg.debug = true
peg.profile = true
peg.cache = {}

local dot, eof, cc, epsilon, P, S, C, Ct = peg.dot, peg.eof, peg.Cc, peg.epsilon, peg.P ,peg.S, peg.C, peg.Ct
local init = cc({false})

local function save(name,value)
    local t = {}
    t[name] = value
    return t
end

local function groupstats(stats, value, units)
    local t = {}
    for i, stat in ipairs(stats) do
        if units == nil then t[stat] = value
        else t[stat.."_PERCENT"] = value
        end
    end
    return t
end

local function accumulate(_acc, delta)
    local acc = _acc or {}
    for k,v in pairs(delta) do
        if acc[k] == nil then acc[k] = v
        else
            if type(k)=="number" then
                table.insert(acc,v)
            elseif type(acc[k])=="number" and type(v)=="number"
                and k~="required_level" then
                acc[k] = acc[k] + v
            else
                error("don't know how to accumulate, key is <"..k..">, type(value) is "..type(value))
            end
        end
    end
    return acc
end

function debugPrint(t,prefix)
    local p = prefix or " "

    io.stderr:write(tostring(t).."\n")
    if type(t)=="table" then
        for i,j in pairs(t) do
            io.stderr:write(p..tostring(i)..": ")
            debugPrint(j,p.."  ")
        end
    end
end

----------------
junk = P" "
space = (junk + S" \t"):star()
digit = peg.R"09"
sign = S"+-"
unsigned = digit:plus()
number = (sign^{0,1}*unsigned*("."*unsigned)^{0,1}):C() / tonumber * space
linebreak = P"\n" * space

itemname = cc"name" * (-linebreak * dot):star():C() / save * space

BOP = cc({"BOP", true}) * peg.P"Становится персональным при получении" / save * space

required = "Требуется" * space
level = "уровень" * space
colon = ":" * space
comma = "," * space
real_dot = "." * space
delimiter = (comma + "и") * space
required_level = cc"required_level" * required * level * colon * number / save

faction = "|3-7(" * (-P")"*dot):star():C() * ")" * space

revered = cc("revered") * "Превознесение" * space
honored = cc("honored") * "Почтение" * space
friendly = cc("friendly") * "Уважение" * space
reputation = revered + honored + friendly
reputation_with = reputation * "со стороны" * space * faction / save
required_reputation = cc"required_reputation" * required * colon * reputation_with / save

use = "Использование" * space
doesnt_sum = "Действие не суммируется с другими постоянными эффектами, наложенными на тот же предмет." * space
item = (cc"shoulders" * "наплечники") * space
increase = "увеличивающих" * space
decrease = "??" * space
stat = (cc"spell_damage" * "силу заклинаний") * space
stats = (stat * (delimiter * stat):star()):Ct()
by = "на" * space
units = (C"%" + "ед" + "ед." + epsilon) * space
value = number * units
modify = increase + decrease
modify_description = stats * by * value / groupstats
enhancement = modify * modify_description * (delimiter * modify_description):star()
enhancements = cc"enhancements" * (init * enhancement * (delimiter * enhancement):star()):Cf(accumulate) / save
enchant = "Наложение на" * space * (cc"items" * item:Ct() / save) * "чар" * space * comma * enhancements
use_effect = (enchant)
on_use = use * colon * use_effect * real_dot * doesnt_sum^{0,1}

sentence = BOP + required_level + required_reputation + on_use

description = (init * sentence * (linebreak * sentence):star()):Cf(accumulate)

expression = (init * itemname * linebreak * description):Cf(accumulate) * linebreak^{0,1} * peg.eof
