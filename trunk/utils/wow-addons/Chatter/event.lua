Chatter = Chatter or {}
Chatter.Event = Chatter.Event or {}
local Event = Chatter.Event
local private = {}
local eventHandlers = { FRAME_ELAPSED = {}, SECOND_ELAPSED = {} }
local print = NLog

-- /run Chatter.Event.RegisterEventOnce("SECOND_ELAPSED", function() NLog("tick once") end)
function Event.RegisterEventOnce(event, handler)
    local holder = {}
    holder.f =
            function(...)
                Event.UnRegisterEvent(event, holder.f)
                handler(...)
            end
    Event.RegisterEvent(event, holder.f)
end

-- /run Chatter.Event.RegisterEvent("PLAYER_TARGET_CHANGED", function() NLog("Player target changed: " .. tostring(UnitName("target"))) end)
-- /run Chatter.Event.RegisterEvent("SECOND_ELAPSED", function() NLog("tick") end)
function Event.RegisterEvent(event, handler)
    if eventHandlers[event] == nil then
        eventHandlers[event] = {}
        private.frame:RegisterEvent(event)
    end
    --print("Registering handler " .. tostring(handler) .. " for event " .. tostring(event))
    eventHandlers[event][handler] = true
end

function Event.UnRegisterEvent(event, handler)
    --print("Unregistering handler " .. tostring(handler) .. " for event " .. tostring(event))
    eventHandlers[event][handler] = nil
end

function private.OnEvent(self, event, ...)
    local handlers = {}
    for handler, _ in pairs(eventHandlers[event]) do
        table.insert(handlers, handler)
    end
    for _, handler in pairs(handlers) do
        --print("Calling handler " .. tostring(handler) .. " to process " .. event)
        handler(...)
    end
end

function private.OnUpdate(me, elapsed)
    private.OnEvent(me, "FRAME_ELAPSED")
    private.elapsedSinceLastTick = (private.elapsedSinceLastTick or 0) + elapsed
    if (private.elapsedSinceLastTick > 1.0) then
        private.elapsedSinceLastTick = 0.0
        private.OnEvent(me, "SECOND_ELAPSED")
    end
end

private.frame = CreateFrame("Frame", "ChatterEventFrame", UIParent)
private.frame:SetFrameStrata("TOOLTIP")
private.frame:SetPoint("TOPLEFT", 10, -10)
private.frame:SetWidth(100)
private.frame:SetHeight(100)
private.frame:SetScript("OnEvent", private.OnEvent)
private.frame:SetScript("OnUpdate", private.OnUpdate)
private.frame:Show()
