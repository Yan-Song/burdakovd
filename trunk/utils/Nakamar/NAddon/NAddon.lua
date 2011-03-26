
local data = {}

local i
for i=1, 100, 1 do
	data[i] = 0
end

-- signature
-- некие случайные числа, известные также внешнему модулю
data[5] = 213674
data[4] = 139443
data[3] = 371721
data[2] = 349667
data[1] = 901791

--data[6] is message - команда внешнему модулю (goto AH, goto mailbox, etc)
--data[7] is target name - имя текущей цели персонажа
--data[8] is DoNotRestart - причина паники ("" если всё нормально)
--data[9] is needPurchaseConfirmation (нужно ли нажать кнопку подтверждения покупки)
--data[10] is CurrentState (string) - текущее состояние, его внешний модуль может показывать пользователю
--data[11] is NothingToDo (yes/no) - в ближайшее достаточно долгое время (часы) этому аккаунту нечего делать
--data[12] is time():guild balance - количество денег в гильдбанке, и время последней проверки

local msgcount = 0
local lastCommandTime = 0


-- функции для взаимодействия с внешним модулем

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
		return true
	end
	return false
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

function NNeedAnyConfirmation(need)
	if need then
		data[9] = "need"
	else
		data[9] = ""
	end
end

function NNothingToDo(yes)
    if yes then
        data[11] = "yes"
    else
        data[11] = "no"
    end
end

function NGuildBalance(balance)
	local faction = UnitFactionGroup("player")
	data[12] = GetRealmName() .. ":" .. faction .. ":" .. tostring(time()) .. ":"	.. tostring(balance)
end

-- инициализация

NSendCommand("nop")
data[7] = ""
data[8] = ""
data[9] = ""
data[10] = "init"
data[11] = "no"
data[12] = ""

----------------------
local frame = CreateFrame("Frame")
frame:SetScript("OnEvent",

	function(self, event, ...)
		data[7] = UnitName("target")
	end
	
	)

frame:RegisterEvent("PLAYER_TARGET_CHANGED")
