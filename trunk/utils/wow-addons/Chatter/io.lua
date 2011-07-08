Chatter = Chatter or {}
Chatter.IO = Chatter.IO or {}

local IO = Chatter.IO
local Event = Chatter.Event
local private = {}

-- async IO operations
-- op1.asyncRun(cb) - execute op1, and call cb(op1_result) after op1 completion

-- op1 * g - new async operation which will execute op1.asyncRun(), then execute g(op1_result).asyncRun() and return op2_result
-- op1 .. op2 - the same, but ignore result of op1. Will execute op1.asyncRun(), then op2.asyncRun() and return op2_result
private.binder = {
__mul =
        function(op1, g)
            local op = {
                asyncRun =
                    function(cb)
                        op1.asyncRun(
                            function(op1_result)
                                g(op1_result).asyncRun(cb)
                            end
                        )
                    end
            }
            setmetatable(op, private.binder)
            return op
        end,

__concat =
        function(op1, op2)
             return op1 * function(op1_result) return op2 end
        end,

__metatable = 1
}

-- instant operation
function IO.Return(result)
    local op = {
        asyncRun = function(cb) cb(result) end
    }
    setmetatable(op, private.binder)
    return op
end

-- /run (Chatter.IO.Log("tic") .. Chatter.IO.Log("tac") .. Chatter.IO.Log("toe")).asyncRun(function() end)
-- /run (Chatter.IO.Log("hello") * Chatter.IO.Log * Chatter.IO.Log).asyncRun(function() end)
-- /run (Chatter.IO.Return("hello") * Chatter.IO.Log * Chatter.IO.Log).asyncRun(function() end)
function IO.Log(result)
    local op = {
        asyncRun = function(cb) NLog(tostring(result)); cb(result) end
    }
    setmetatable(op, private.binder)
    return op
end

-- /run (Chatter.IO.Log("tic") .. Chatter.IO.SleepUntil(GetTime() + 1) .. Chatter.IO.Log("tac") .. Chatter.IO.SleepUntil(GetTime() + 2) .. Chatter.IO.Log("toe")).asyncRun(function() end)
function IO.SleepUntil(goal)
    local op = {
        asyncRun =
                function(cb)
                    local holder = {}
                    holder.f =
                            function()
                                if GetTime() >= goal then
                                    Event.UnRegisterEvent("FRAME_ELAPSED", holder.f)
                                    cb()
                                end
                            end
                    Event.RegisterEvent("FRAME_ELAPSED", holder.f)
                end
    }
    setmetatable(op, private.binder)
    return op
end

-- /run (Chatter.IO.GetTime * Chatter.IO.Log).asyncRun(function() end)
IO.GetTime = {
    asyncRun =
            function(cb)
                cb(GetTime())
            end
}
setmetatable(IO.GetTime, private.binder)

-- /run (Chatter.IO.Log("tic") .. Chatter.IO.Sleep(1000) .. Chatter.IO.Log("tac") .. Chatter.IO.Sleep(1000) .. Chatter.IO.Log("toe")).asyncRun(function() end)
-- /run (Chatter.IO.GetTime * Chatter.IO.Log .. Chatter.IO.Sleep(1000) .. Chatter.IO.GetTime * Chatter.IO.Log).asyncRun(function() end)
function IO.Sleep(milliseconds)
    return IO.GetTime * function(t) return IO.SleepUntil(t + milliseconds / 1000) end
end

-- /run (function() local t =  end)()
function IO.Parallel(operations)
    local holder = { results = {}, left = #operations }
    local op = {
        asyncRun =
                function(cb)
                    for index, operation = ipairs(operations)
                        local collector =
                                function(result)
                                    holder.results[index] = result
                                    holder.left -= 1
                                    if holder.left == 0 then
                                        cb(holder.results)
                                    end
                                end
                        operation.asyncRun(collector)
                    end
                end
    }
    setmetatable(op, private.binder)
    return op
end
