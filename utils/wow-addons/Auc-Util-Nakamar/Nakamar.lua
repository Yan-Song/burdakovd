--[[
	Auctioneer Advanced - Nakamar Utility module
--]]


-- стандартная прелюдия для модулей аукционера
local libType, libName = "Util", "Nakamar"
local lib, parent, private = AucAdvanced.NewModule(libType, libName)
if not lib then return end
lib.API = {}


-- shortcuts
local ipairs = ipairs
local pairs = pairs
local tinsert = table.insert
local max = math.max
local min = math.min
local random = math.random
local GetFaction = AucAdvanced.GetFaction


-- constants
local keepFreeBagSlots = 1
local circularLogLength = 10000

-- utils
local print = function(s)
	local frameIndex = 1
	local frameReference = _G["ChatFrame"..tostring(frameIndex)] or DEFAULT_CHAT_FRAME
	local name, fontSize, r, g, b, a, shown, locked, docked = GetChatWindowInfo(frameIndex)
	if (name == "") or not(docked or shown) then
		frameReference = DEFAULT_CHAT_FRAME
	end
	local prefix = date("[N] [%H:%M:%S] ")
	local message = prefix..tostring(s)
	Nakamar.logs = Nakamar.logs or { [0] = 1 }
	Nakamar.logs[Nakamar.logs[0]] = message
	Nakamar.logs[0] = Nakamar.logs[0] % circularLogLength + 1
	frameReference:AddMessage(message, 1.0, 1.0, 1.0)
end
private.print = print
NLog = print

function lib.FreeBagSlots()
	local free = 0
	for bag = 0, NUM_BAG_SLOTS do
		local bagFree,bagFam = GetContainerNumFreeSlots(bag)
		if bagFam == 0 then
			free = free + bagFree
		end
	end
	return free
end

-- returns all items from the bags or auctionable only
function lib.bagSlots(filter)
	local items = {}
	for bag = NUM_BAG_FRAMES, 0, -1 do
		if GBM:IsNormalBag(bag) then
			for slot = GetContainerNumSlots(bag), 1, -1 do
				local link = GetContainerItemLink(bag, slot)
				if link and filter(link,bag,slot) then
					tinsert(items,{link, bag, slot} )
				end
			end
		end
	end
	return items
end

function lib.isAuctionable(link, bag, slot)
	local sig = AucAdvanced.API.GetSigFromLink(link)
	return --[[not private.badSigs[sig] and --]] AucAdvanced.Post.IsAuctionable(bag, slot)
end

function lib.auctionableSlots()
	return lib.bagSlots(lib.isAuctionable)
end

-- количество предметов и денег в сумке
local assets = function()
	return GBM:InBagsItemCount() + GetMoney()
end

function lib.NeedPurchaseConfirmation()
	return AuctionFrame and AuctionFrame:IsVisible() and AucAdvanced.Buy.Private.Prompt:IsVisible()
end

function lib.NeedPostConfirmation()
	return AuctionFrame and AuctionFrame:IsVisible() and AucAdvanced.Post.Private.Prompt:IsVisible()
end

function lib.NeedAnyConfirmation()
	-- задержка на 100 фреймов, так как биндинги настраиваются только на сотом фрейме
    return (lib.NeedPurchaseConfirmation() or lib.NeedPostConfirmation() or private.currentState.isInitializing()) and (private.framesSinceStart > 100)
end

function lib.ConfirmPurchase()
	if private.currentState.isPaused() then
		private.resetState()
	elseif lib.NeedPostConfirmation() then
		AucAdvanced.Post.Private.Prompt.Yes:Click()
	elseif lib.NeedPurchaseConfirmation() then
		AucAdvanced.Buy.Private.Prompt.Yes:Click()
	end
end
ConfirmPurchase = lib.ConfirmPurchase

-- events
local eventHandlers = {}
local RegisterEvent = function(event, f)
	
	if eventHandlers[event] == nil then
		eventHandlers[event] = {}
		private.frame:RegisterEvent(event)
	end
	--print("Registering handler " .. tostring(f) .. " for event " .. tostring(event))
	eventHandlers[event][f] = true
end

local UnRegisterEvent = function(event, f)
	--print("Deregistering handler " .. tostring(f) .. " for event " .. tostring(event))
	eventHandlers[event][f] = nil
end

function private.OnEvent(self, event, ...)
	for handler, _ in pairs(eventHandlers[event]) do
		--print("Calling handler " .. tostring(handler) .. " to process " .. event)
		handler(...)
	end
end


-- timer events
function private.everySecond()
	NKeepAlive()
	--print(lib.NeedAnyConfirmation())
	NNeedAnyConfirmation(lib.NeedAnyConfirmation())
	--print("Tick! framesSinceStart  = "..tostring(private.framesSinceStart))
	private.currentState:tick()
end

function private.OnUpdate(me, elapsed)
	private.framesSinceStart = private.framesSinceStart + 1
	-- при старте биндинги не очень успешно инициализируются
	if private.framesSinceStart == 100 then	
		private.makeBindings()
	end
    private.elapsedSinceLastTick = private.elapsedSinceLastTick + elapsed
    if (private.elapsedSinceLastTick > 1.0) then
        private:everySecond()
        private.elapsedSinceLastTick = 0.0
    end
end


-- state machine

function private.changeState(self, newState)
	private.currentState:leave()
	--print("Смена состояния: '" .. private.currentState:getName() .. "' => '" .. newState:getName() .. "'")
	NCurrentState(newState:getName())
	private.currentState = newState
	newState.timeEntered = time()
end

-- шаблон для всех сотояний
local dumbState = function(name)
	return {
		getName = function() return name end,
		leave = function() end,
		tick = function() end,
		isPaused = function() return false end,
		isInitializing = function() return false end
	}
end

local timeoutable = function(original, limit, handler)
	local ans = original
	local originalTick = original.tick
	ans.tick = function(self) originalTick(original); if time() - self.timeEntered > limit then handler() end end
	return ans
end

local terminate = function()
	Screenshot()
	Quit()
end

local states = {}


local panicState = function(reason)
	--PlaySoundFile("Sound\\Character\\PlayerRoars\\CharacterRoarsDwarfMale.wav")
		
	local text = reason or "причина неизвестна"
	print("Ошибка: " .. text)
	--local timeLeft = random(30, 60)
	--print("Quit через "..tostring(timeLeft).." секунд")
	
	-- даём внешнему модулю знать что всё плохо
	--NDoNotRestart(text)
	
	Screenshot()
	
	--local ans = timeoutable(dumbState("panic"), timeLeft, terminate)
	-- если паника будет отменена, то сообщить об этом внешнему модулю
	--ans.leave = function(self) NDoNotRestart("") end
	--return ans
	
	return states.pauseState()
end
states.panicState = panicState

local panic = function(reason)
	private:changeState(states.panicState(reason))
end

local panicable = function(original, limit, description)
	local reason = "Прошло более " .. tostring(limit) .. " секунд, но так и не удалось выполнить '" .. description .. "'"
	return timeoutable(original, limit, function() panic(reason) end)
end

-- первые 100 фреймов ничего не делать
-- некоторая защита от лагов
local initState = function()
	local ans = dumbState("инициализация")
	ans.tick = function(self) if private.framesSinceStart > 100
	                          then resetState()
							  end
			   end
	return panicable(ans, 60, "обработать 100 кадров")
end
states.initState = initState

resetState = function()
	CloseAuctionHouse()
	CloseMail()
	private.badSigs = {}
	private.nextMailboxCheck = 0
	NSendCommand("break")
	private:changeState(states.chooseState())
end
private.resetState = resetState

setPauseState = function()
	private:changeState(states.pauseState())
end

pauseState = function()
	print("pausing")
	NSendCommand("break")
	local w = dumbState("Paused")
	w.isPaused = function() return true end
	return w
end
states.pauseState = pauseState

setInitializingState = function()
	private:changeState(states.initializingState())
end

initializingState = function()
	print("Ждём, пока внешний модуль нажмёт F9 чтобы подтвердить запуск")
	local w = states.pauseState()
	w.isInitializing = function() return true end
	return w
end
states.initializingState = initializingState

-- основная логика
local chooseState = function()
	local haveFreeBagSlots = lib.FreeBagSlots() > keepFreeBagSlots
	local possiblyHaveMail = time() >= private.nextMailboxCheck
	local haveGoodsToPost = #lib.auctionableSlots() > 0
	
	--print("[debug] freeBagSlots = " .. tostring(lib.FreeBagSlots()) .. 
	--	"; will have mail in " .. tostring(-time() + private.nextMailboxCheck) .. " seconds; have "
	--	.. tostring(#lib.auctionableSlots()) .. " slots to post oh AH.")
	
	if haveFreeBagSlots and possiblyHaveMail then
		print("Надо проверить почтовый ящик")
		return states.waitingForMailboxState()
	elseif haveGoodsToPost then
		print("Надо идти на аукцион")
		return states.waitingForAHState()
	else
		print("Нет возможности ни проверить почту (ящик пуст либо недостаточно места в сумке) ни выложить товар на аукцион (нечего выкладывать)")
		NNothingToDo(true)
		-- тут есть опасность выпасть в AFK и получить дисконнект
		-- чтобы этого не произошло, можно использовать RandomPet
		-- или внешний модуль будет делать логофф при NNothingToDo(true)
		return timeoutable(dumbState("sleep 6 seconds"), 6, function() NNothingToDo(false); private:changeState(states.chooseState()) end)
	end
end
states.chooseState = chooseState

function private.GoToAuction()
	CloseAuctionHouse()
	NGoTo("Аукцион")
end

function private.GoToMail()
	CloseMail()
	NGoTo("Почта")
end

local waitingForMailboxState = function()
	-- даём команду внешнему модулю
	private.GoToMail()
	
	local waiter = dumbState("WAITING_FOR_MAILBOX")
	
	-- обработчики
	
	-- важный, хоть и кривой момент.
	-- тут устанавливается псевдосостояние "Почта", чтобы внешний модуль
	-- смог понять, что его работа по открытию почтового ящика завершена
	waiter.onMailboxOpened = function() waiter.openedTime = time(); NCurrentState("Почта") end
	waiter.onInboxLoaded = function() waiter.loadedTime = time() end
	
	waiter.tick = function(self)
		-- собираем почту если
		--  1) почтовый ящик виден
		--  2) с момента открытия и загрузки содержимого прошло не менее 5 секунд
		--  (эта задержка даст время внешнему модулю, см. NCurrentState("Почта"))
		if InboxFrame:IsVisible() and time() - (self.openedTime or time()) > 5 and time() - (self.loadedTime or time()) > 5 then
			-- можно запускать сбор почты
			print("Начинаю собирать почту")
			Postal.modules.OpenAll:OpenAll()
			private:changeState(states.waitingForPostal())
		end
	end
	
	-- регистрируем обработчики
	RegisterEvent("MAIL_SHOW", waiter.onMailboxOpened)
	RegisterEvent("MAIL_INBOX_UPDATE", waiter.onInboxLoaded)
	
	-- удаляем обработчики по завершении
	waiter.leave = function()
		UnRegisterEvent("MAIL_SHOW", waiter.onMailboxOpened)
		UnRegisterEvent("MAIL_INBOX_UPDATE", waiter.onInboxLoaded)
	end
	
	-- ставим таймаут в 120 секунд
	return panicable(waiter, 120, "Добраться до почтового ящика")
end
states.waitingForMailboxState = waitingForMailboxState

local waitingForPostal = function()
	local waiter = dumbState("WAITING_FOR_POSTAL")
	waiter.previousAssets = -1
	waiter.lastSuccess = time()
	
	waiter.tick = function(self)
		-- проверяем, удалось ли что-то собрать с прошлого раза
		if assets() ~= self.previousAssets then
			self.previousAssets = assets()
			self.lastSuccess = time()
		end

		-- возможные сценарии завершения
		if not InboxFrame:IsVisible() then
			panic("Неожиданно закрыт почтовый ящик")		
		elseif lib.FreeBagSlots() <= keepFreeBagSlots then
			-- Postal надо настроить оставлять один слот пустым, можно 0, но НЕ БОЛЬШЕ
			print("В сумке один или менее свободный слот, прекращаю сбор почты")
			CloseMail()
			private:changeState(states.chooseState())
		elseif (not Postal:IsHooked("InboxFrame_OnClick")) or (time() - self.lastSuccess > 180) then
			print("За этот сеанс собрать больше нечего, скорее всего ящик пуст")
			CloseMail()
			-- предположим также, что в ближайшие 7..11 секунд нет смысла проверять почту
			local wait = random(7, 11)
			private.nextMailboxCheck = time() + wait
			print("Следующая проверка ящика не ранее, чем через " .. wait .. " секунд")
			private:changeState(states.chooseState())
		end
	end
	
	-- ставим таймаут в 10 минут
	return panicable(waiter, 600, "Собрать содержимое почтового ящика")
end
states.waitingForPostal = waitingForPostal

local waitingForAHState = function()
	private.GoToAuction()
	
	local waiter = dumbState("WAITING_FOR_AUCTION")
	
	waiter.tick = function(self)
		if private.auctionAvailable then
			-- важный, хоть и кривой момент.
			-- тут устанавливается псевдосостояние "Аукцион", чтобы внешний модуль
			-- смог понять, что его работа по открытию аукциона завершена
			if not self.openedTime then self.openedTime = time(); NCurrentState("Аукцион") end
		else
			if self.openedTime then panic("Неожиданно закрыт аукцион") end
		end
		
		-- Переходим к действиям с аукционом через 5 секунд после того, как он откроется
		if time() - (self.openedTime or time()) > 5 then
			-- можно работать с аукционом
			print("Начинаю работу с аукционом")
			private:changeState(states.doWorkWithAH())
		end
	end
	
	-- ставим таймаут в 120 секунд
	return panicable(waiter, 120, "Добраться до аукциона")
end
states.waitingForAHState = waitingForAHState

local doWorkWithAH = function()

	if not private.auctionAvailable then
		return states.panicState("Неожиданно закрыто окно аукциона")
	end
	
	print("Обновляю цены конкурентов")
	return panicable(states.updateStats(), 15 * 60, "обновить цены")
end
states.doWorkWithAH = doWorkWithAH

local updateStats = function()

	if not private.auctionAvailable then
		return states.panicState("Неожиданно закрыто окно аукциона")
	end

	AuctionFrameTab5:Click()
	if not AucAdvanced.Modules.Util.Appraiser.Private.frame:IsVisible() then
		return states.panicState("Appraiser оказался не в том табе?")
	end

	AucAdvanced.Modules.Util.Appraiser.Private.frame.RefreshAll()
	
	local waiter = dumbState("Обновление цен")
	waiter.tick = function(self)
		if not private.auctionAvailable then
			panic("Неожиданно закрыто окно аукциона")
			return
		end
		
		if not AucAdvanced.Scan.IsPaused() and not AucAdvanced.Scan.IsScanning()
			and AucAdvanced.Scan.GetScanCount() == 0 then
				print("Похоже цены обновились, приступаю к выставлению товара на аукцион")
				private:changeState(panicable(states.doPosting(), 30 * 60, "выставить весь товар на аукцион"))
		end
	end
	
	return waiter
end
states.updateStats = updateStats

local calculateAge = function(sig)

	local itemId, suffix, factor = strsplit(":", sig)
	itemId = tonumber(itemId)
	suffix = tonumber(suffix) or 0
	factor = tonumber(factor) or 0

	local results = AucAdvanced.API.QueryImage({
		itemId = itemId,
		suffix = suffix,
		factor = factor,
	})

	local seen = (results[1] and results[1][AucAdvanced.Const.TIME]) or 0
	
	return time() - seen
end

local doPosting = function()

	if not private.auctionAvailable then
		return states.panicState("Неожиданно закрыто окно аукциона")
	end
	
	if not AucAdvanced.Modules.Util.Appraiser.Private.frame:IsVisible() then
		return states.panicState("Appraiser не открыт?")
	end
	
	local slots = lib.auctionableSlots()
	local stage1 = {}
	local counts = {}
	for i, v in ipairs(slots) do
		local link, bag, slot = unpack(v)
		local _, itemCount = GetContainerItemInfo(bag, slot)
		local sig = AucAdvanced.API.GetSigFromLink(link)
		local postedStack = AucAdvanced.Settings.GetSetting("util.appraiser.item."..sig..".stack") or AucAdvanced.Settings.GetSetting("util.appraiser.stack")
		if postedStack == "max" then
			_, _, _, _, _, _, _, postedStack = GetItemInfo(link)
		end
		stage1[sig] = (stage1[sig] or 0)
		if itemCount <= postedStack then
			-- it is not guaranteed that auc-advanced can post this item
			-- example: have two stack of 15, and posting in stacks of 20, and other bag slots are full with something else
			stage1[sig] = stage1[sig] + 1
		end
		counts[sig] = (counts[sig] or 0) + itemCount
	end
	
	for i,v in ipairs(slots) do
		local link, bag, slot = unpack(v)
		local _, itemCount = GetContainerItemInfo(bag, slot)
		local sig = AucAdvanced.API.GetSigFromLink(link)
		local postedStack = AucAdvanced.Settings.GetSetting("util.appraiser.item."..sig..".stack") or AucAdvanced.Settings.GetSetting("util.appraiser.stack")
		if postedStack == "max" then
			_, _, _, _, _, _, _, postedStack = GetItemInfo(link)
		end
		local firstPost = counts[sig] % postedStack
		if firstPost == 0 then
			firstPost = postedStack
		end
		if itemCount <= firstPost then
			-- it is guaranteed that auc-advanced can post this item
			stage1[sig] = stage1[sig] + 1000
		end
	end
	
	local stage2 = {}
	for sig, count in pairs(stage1) do
		tinsert(stage2, {sig, stage1[sig]})
	end
	table.sort(stage2, function(x,y) return x[2]>y[2] end)
	
	if stage2[1][2] == 0 and not GBM:FindFreeBagSlot() then
		print("выложить не получится, так как во всех слотах больше чем надо итемов")
		print("а свободных ячеек, чтоб разделить - нет")
		return states.panicState("не хватает места в сумке")
	end
	
	for i, v in ipairs(stage2) do
		local sig, count = unpack(v)
		local age = calculateAge(sig)
		if age < 300 then
			AucAdvanced.Modules.Util.Appraiser.Private.frame.PostBySig(sig)
		else
			print("Не найдена информация о цене " .. AucAdvanced.API.GetLinkFromSig(sig) .. " (age = " .. tostring(age) .. ")" --[[ .. ", заносим его в черный список на этот сеанс"--]]) 
			--private.badSigs[sig] = true
		end
	end
	
	local waiter = dumbState("Выставление товара")
	waiter.tick = function(self)
		if not private.auctionAvailable then
			panic("Неожиданно закрыто окно аукциона")
			return
		end
	
		if AucAdvanced.Post.GetQueueLen() == 0 then
			print("Всё, что возможно, выложено на аукцион")
			
			-- занести всё, что осталось в сумках в черный список
			local slots = lib.auctionableSlots()
			for i, v in ipairs(slots) do
				local link, _, _ = unpack(v)
				local sig = AucAdvanced.API.GetSigFromLink(link)
				if not private.badSigs[sig] then
					print("предмет " .. link .. " по неизвестной причине остался в сумке после попытки выставления на аукцион" --[[.. ", заношу его в черный список"--]])
					--private.badSigs[sig] = true
				end
			end
			
			CloseAuctionHouse()
			private:changeState(states.chooseState())
		end
	end
	
	return waiter
end
states.doPosting = doPosting

local bindKey = function(key, action)
	if SetBinding(key, action) then
		print("Successfully binded " .. action .. " to " .. key)
	else
		print("Failed to bind " .. action .. " to " .. key)
	end
end

function private.makeBindings()
	bindKey("W", "MOVEFORWARD")
	bindKey("A", "TURNLEFT")
	bindKey("D", "TURNRIGHT")
	bindKey("SPACE", "JUMP")
	bindKey("PRINTSCREEN", "SCREENSHOT")
	bindKey("F1", "TARGETNEARESTFRIEND")
	bindKey("F2", "INTERACTTARGET")
	bindKey("F3", "INTERACTMOUSEOVER")
	bindKey("F6", "CAMERAZOOMIN")
	bindKey("F8", "SETVIEW3")
	SetBindingClick("F9", "NakamarButton")
end

-- initialization
function lib.OnLoad()

	-- settings
	Nakamar = Nakamar or {}
	AucAdvanced.Settings.SetDefault("util.nakamar.printwindow", 1)
	
	-- init
	private.framesSinceStart = 0
	private.elapsedSinceLastTick = 0.0
	private.nextMailboxCheck = 0
	private.currentState = dumbState("dumb")
	private.badSigs = {}
	
	-- создаём фрейм для обработки событий
	private.frame = CreateFrame("Frame", "NakamarFrame", UIParent)
	private.frame:SetFrameStrata("TOOLTIP")
	private.frame:SetPoint("TOPLEFT", 10, -10)
	private.frame:SetWidth(100)
	private.frame:SetHeight(100)
	private.frame:SetScript("OnEvent", private.OnEvent)
	private.frame:SetScript("OnUpdate", private.OnUpdate)
	private.frame:Show()
	private.button = CreateFrame("Button", "NakamarButton", UIParent)
	private.button:SetScript("OnClick", ConfirmPurchase)
	
	-- регистрируем обработчики
	RegisterEvent("CHAT_MSG_WHISPER", function()
		if not private.currentState.isPaused() then panic("Получено приватное сообщение") end
		end)
	
	-- ставим аддон на паузу, чтоб не мешался
	setInitializingState()
end

function lib.Processor(callbackType, ...)
	if (callbackType == "config") then
		--private.SetupConfigGui(...)
    elseif (callbackType == "auctionui") then
        --private.HookAH()
	elseif callbackType == "auctionopen" then
		private.auctionAvailable = true
	elseif callbackType == "auctionclose" then
		private.auctionAvailable = false
	end
end
