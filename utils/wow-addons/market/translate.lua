#!/usr/bin/lua5.1

-- this script translates Lua's tables into Python's dictionaries

local function escape(s)
    local s = tostring(s)
    s = s:gsub('\\', '\\\\')
    s = s:gsub('"', '\\"')
    s = 'u"'..s..'"'
    return s
end

local function tprint(t, prefix)
    local prefix = prefix or 1
    
    local function write(...)
        for i=1, prefix do
            io.write("  ")
        end
        print(...)
    end
    
    if type(t)=="table" then
        write("{")
        prefix = prefix + 1
        for k, v in pairs(t) do
            write(escape(k)..":")
            tprint(v, prefix+1)
            write(",")
        end
        prefix = prefix - 1
        write("}")
    else
        write(escape(t))
    end
end

require "BeanCounter"

print("# -*- coding: utf8 -*-")
print("data = \\")
tprint(BeanCounterDB)