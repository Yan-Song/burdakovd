local private = {}

local frame = CreateFrame("FRAME"); -- Need a frame to respond to events
frame:RegisterEvent("ADDON_LOADED"); -- Fired when saved variables are loaded

function frame:OnEvent(event, arg1)
    if event == "ADDON_LOADED" and arg1 == "NLogger" then
        -- Our saved variables are ready at this point.
        if DefaultLog == nil then
            DefaultLog = {}
            print("[NLogger] Default log destination has been initialized.")
        end
        private.destination = DefaultLog
    end
end

frame:SetScript("OnEvent", frame.OnEvent);


-- constants
local circularLogLength = 10000

NLog = function(s)
    local frameIndex = 1
    local frameReference = _G["ChatFrame"..tostring(frameIndex)] or DEFAULT_CHAT_FRAME
    local name, fontSize, r, g, b, a, shown, locked, docked = GetChatWindowInfo(frameIndex)
    if (name == "") or not(docked or shown) then
        frameReference = DEFAULT_CHAT_FRAME
    end
    local prefix = date("[N] [%H:%M:%S] ")
    local message = prefix .. tostring(s)
    if private.destination then
        local position = private.destination[0] or 1
        private.destination[position] = message
        private.destination[0] = position % circularLogLength + 1
    else
        message = "[Display only] " .. message
    end
    frameReference:AddMessage(message, 1.0, 1.0, 1.0)
end

NLogDestination = function(destination)
    private.destination = destination
end
