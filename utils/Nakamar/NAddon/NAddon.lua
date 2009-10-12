local data = {}

local i
for i=1, 100, 1 do
	data[i] = 0
end

-- signature
data[5] = 213674
data[4] = 139443
data[3] = 371721
data[2] = 349667
data[1] = 901791

--data[6] is message
--data[7] is target name
--data[8] is DoNotRestart
--data[9] is needPurchaseConfirmation
--data[10] is CurrentState (string)

local msgcount = 0
local lastCommandTime = 0

local function NSendMessage(text)
	msgcount = msgcount + 1
	data[6] = tostring(msgcount).."|"..text
end

function NSendCommand(...)
	local ans = ""
	for n, x in ipairs({...}) do
		if n>1 then
			ans = ans .. ";"
		end
		ans = ans .. x
	end
	NSendMessage(ans)
	lastCommandTime = time()
end

function NKeepAlive()
	if(time() - lastCommandTime > 300) then
		NSendCommand("nop")
	end
end

function NDoNotRestart(text)
	text = text or ""
	data[8] = text
end

function NCurrentState(state)
	data[10] = state
end

function NGoTo(destination)
	NCurrentState("waiting for "..tostring(destination))
	NSendCommand("goto", destination)
end

function NNeedPurchaseConfirmation(need)
	if need then
		data[9] = "need"
	else
		data[9] = ""
	end
end

NSendCommand("nop")
data[7] = ""
data[8] = ""
data[9] = ""
data[10] = "init"

----------------------
local frame = CreateFrame("Frame")
frame:SetScript("OnEvent",

	function(self, event, ...)
		data[7] = UnitName("target")
	end
	
	)

frame:RegisterEvent("PLAYER_TARGET_CHANGED")