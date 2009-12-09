--[[
	Auctioneer Advanced - Nakamar Utility module

	License:
		This program is free software; you can redistribute it and/or
		modify it under the terms of the GNU General Public License
		as published by the Free Software Foundation; either version 2
		of the License, or (at your option) any later version.

		This program is distributed in the hope that it will be useful,
		but WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
		GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
		along with this program(see GPL.txt); if not, write to the Free Software
		Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA	02110-1301, USA.

	Note:
		This AddOn's source code is specifically designed to work with
		World of Warcraft's interpreted AddOn system.
		You have an implicit licence to use this AddOn with these facilities
		since that is its designated purpose as per:
		http://www.fsf.org/licensing/licenses/gpl-faq.html#InterpreterIncompat
--]]


local libType, libName = "Util", "Nakamar"
local lib, parent, private = AucAdvanced.NewModule(libType, libName)
if not lib then return end
lib.API = {}

local frames = 0
local ipairs = ipairs
local pairs = pairs
local tinsert = table.insert
local GetFaction = AucAdvanced.GetFaction

private.state = "LOADING"
private.lastStateChangeTime = 0
private.hasFreeBankSlots = true
private.lastBankInfoUpdateTime = -10000.0
private.nextMailTime = 0.0 -- когда в следующий раз можно будет зайти на почту

local everySecondTimer = 0.0
-- уже не помню, зачем он нужен, если есть GetTime()
-- возможно я тогда не знал про GetTime(), но сейчас исправлять не могу
-- кроме того gtime не совсем совпадает с GetTime() но кажется разницы нет
private.GameTime = 0.0
-- открыто ли окно банка
local bankAvailable = nil
-- открыта ли почта
local mailboxOpened = false
-- можно ли уже работать с почтой (загрузилась ли)
local mailboxAvailable = nil
-- открыто ли уже окно аукциона
local auctionAvailable = nil
local eventHandlers = {}
local lastMovementRequest = -1000.0
local mailboxOpenedTime = 0
-- количество предметов и голда в сумке перед каким-либо действием
-- используется чтобы сравнить с текущим, узнать, удалось ли что-то собрать
local oldAssets = 0
-- количество --/-- несколько секунд назад
-- используется чтобы сравнить с текущим и узнать,
-- удалось ли что-то собрать за последние несколько секунд
local prevAssets = 0
-- время последнего обновления prevAssets
local prevAssetsTime = 0
-- на сколько секунд скан может устареть, чтобы его ещё можно было считать действительным
local maxScanAge = 7200 -- 2h
local keepFreeBagSlots = 1

local max = function(x, y)
	if x > y then
		return x
	else
		return y
	end
end

-- количество предметов и денег в сумке
local assets = function()
	return GBM:InBagsItemCount() + GetMoney()
end

local RegisterEvent = function(event, f)
	private.frame:RegisterEvent(event)
	if eventHandlers[event] == nil then
		eventHandlers[event] = {}
	end
	tinsert(eventHandlers[event], f)
end

local print = function(s)
	local frameIndex = AucAdvanced.Settings.GetSetting("util.nakamar.printwindow") or 1
	local frameReference = _G["ChatFrame"..tostring(frameIndex)] or DEFAULT_CHAT_FRAME
	local name, fontSize, r, g, b, a, shown, locked, docked = GetChatWindowInfo(frameIndex)
	if (name == "") or not(docked or shown) then
		frameReference = DEFAULT_CHAT_FRAME
	end
	local prefix = date("[%H:%M:%S] ")
	frameReference:AddMessage(prefix..tostring(s), 1.0, 1.0, 1.0)
	if not Nakamar.logs then Nakamar.logs = {} end
	tinsert(Nakamar.logs, {time(), tostring(s)})
end
private.print = print

function lib.isBankAvailable()
	return bankAvailable
end

function private.updateFreeBankSlots()
	-- проверка на наличие пустых слотов в банке
	local old = private.hasFreeBankSlots
	private.hasFreeBankSlots = not not GBM:FindFreeBankSlot() -- convert to boolean
	
	if private.hasFreeBankSlots ~= old then
		if private.hasFreeBankSlots then
			print("Оказывается в банке ещё есть свободные ячейки... Буду иметь в виду")
		else
			print("В банке закончилось место... Печаль")
		end
	end
end

function private.updateAuctionableBankItems()
	-- проверка на наличие Auctionable вещей в банке
	local old = private.hasAuctionableBankItems
	private.hasAuctionableBankItems = #(lib.batchBankItems()) > 0
	
	if private.hasAuctionableBankItems ~= old then
		if private.hasAuctionableBankItems then
			print("В банке есть товары на продажу")
		else
			print("В банке нет товаров на продажу")
		end
	end
end

function private.updateBankStats()
	if not bankAvailable then return end -- return if bank window is not open
	private.lastBankInfoUpdateTime = private.GameTime
	
	private.updateFreeBankSlots()
	private.updateAuctionableBankItems()
end

function private.ERROR(reason)
	local text = reason or "причина неизвестна"
	private.playSound("ERROR")
	print("Ошибка: "..text)
	if(AucAdvanced.Settings.GetSetting("util.nakamar.quit_on_error")) then
		print("Quit через "..tostring(private.waitbeforequitseconds).." секунд")
		private.changeState("QUIT")
		NDoNotRestart(text)
	else
		-- странный код...
		private.changeState("ERROR")
		private.changeState("THINKING")
	end
	Screenshot()
end

local updateNextMailTime = function()
	local wait
	
	if oldAssets == assets() then
		wait = random(5000, 10000)
		local minutes = ceil(wait / 60)
		print("Похоже я собрал всю почту, следующая проверка через "..tostring(minutes).." минут")
	else
		print("Жду минуту пока обновится ящик")
		wait = random(60, 100)
	end
	private.nextMailTime = private.GameTime + wait
end

function lib.CancelQuit()
	if private.state == "QUIT" then
		NDoNotRestart("") -- отменить donotrestart
		private.changeState("THINKING")
		print("Quit отменён")
	else
		print("а Quit делать никто и не собирался...")
	end
end

function private.GoTo(destination)
	lastMovementRequest = private.GameTime
	private.destination = destination
	NGoTo(destination)
end

function private.GoToAuction()
	CloseAuctionHouse()
	private.GoTo("Аукцион")
end

function private.GoToMail()
	CloseMail()
	private.GoTo("Почта")
end

function private.GoToBank()
	CloseBankFrame()
	private.GoTo("Банк")
end

local freshBankInfo = function()
	return private.lastBankInfoUpdateTime > private.GameTime - 3600
end

local saidAboutFullBank = false
function private.everySecond()
	NKeepAlive()
	
	-- первые 100 фреймов ничего не делаем,
	-- в надежде что за это время wow успеет нормально запуститься
	-- и перестанет лагать
	if private.state == "LOADING" then
		if frames > 100 then
			private.state = "THINKING"
		else
			return
		end
	end
	
	NNeedPurchaseConfirmation(lib.NeedPurchaseConfirmation())
	private.updateBankStats()
	
	local allowedResume = private.allowedResume()
	
	if private.state == "QUIT" and private.stateTime() > private.waitbeforequitseconds then
		print("QUIT NOW")
		Screenshot()
		private.changeState("QUITED")
		Quit()
	elseif private.state == "QUIT" then
		return
	end
	if private.state == "QUITED" then
		print("Quiting...")
		return
	end
	
	if not AucAdvanced.Settings.GetSetting('util.nakamar.enabled') then return end
	
	-- строки ниже этой будут выполнены только если аддон включён
	
	-- будем ли в ближайшие две минуты проверять почту
	local needWaitForMail = (private.nextMailTime - private.GameTime < 120) and 
		lib.FreeBagSlots() > keepFreeBagSlots
	
	local hasNonAuctionableItems = #lib.nonbatchItems() > 0
	local possiblyHasFreeBankSlots = not freshBankInfo() or private.hasFreeBankSlots
	
	local hasFreeBagSlots = lib.FreeBagSlots() > 0
	local possiblyHasAuctionableBankItems = not(freshBankInfo()) or private.hasAuctionableBankItems
	
	-------- THINKING
    if private.state == "THINKING" then
		
		-- если есть что положить в банк
		if hasNonAuctionableItems then
			if possiblyHasFreeBankSlots then
				print(string.format(
					"В сумках есть %d итемов, которые не выставляются на аукцион, надо отнести их в банк",
					#lib.nonbatchItems()))
				private.GoToBank()
				private.changeState("WAITING_FOR_BANK")
				return
			else
				if not saidAboutFullBank then
					print(string.format(
						"В сумках есть %d итемов, которые не выставляются на аукцион, но в банке нет места.",
						#lib.nonbatchItems()))
					saidAboutFullBank = true
				end
			end
		end
		
		-- если есть что взять из банка
		if hasFreeBagSlots and possiblyHasAuctionableBankItems then
			print("Надо забрать в банке товар на продажу")
			private.GoToBank()
			private.changeState("WAITING_FOR_BANK")
			return
		end
		
		-- если не будем и есть что выложить - идти на аук выкладывать
		local hasAuctionableItems = #lib.batchItems() > 0
		if not needWaitForMail and hasAuctionableItems then
			print(string.format("В сумках есть %d итемов на продажу, надо идти на аукцион", #lib.batchItems()))
			private.GoToAuction()
			private.changeState("WAITING_FOR_AUCTION")
			return
		end
	end
	
	if private.state ~= "THINKING" then
		saidAboutFullBank = false
	end
	
	local busy = private.state ~= "THINKING" and private.state ~= "SCANNING"
	local needCheckMail = private.GameTime > private.nextMailTime and
		lib.FreeBagSlots() > keepFreeBagSlots
	
	if not busy and needCheckMail then
		-- пора идти на почту
		if AucAdvanced.Settings.GetSetting('util.nakamar.close_ah_when_scanning') then
			CloseAuctionHouse()
		end
		print("Надо проверить почтовый ящик")
		private.GoToMail()
		private.changeState("WAITING_FOR_MAILBOX")
		return
	end
	
	-- если в ближайшее время надо будет проверить почту то просто ждём
	if private.state == "THINKING" and needWaitForMail then
		return
	end
	
	-- иначе
	if private.state == "THINKING" then
		print("Делать пока нечего, пойду сканировать аукцион")
		private.GoToAuction()
		private.changeState("WAITING_FOR_AUCTION")
		return
	end
	
	-- Если пришли в банк
	if bankAvailable and private.state == "WAITING_FOR_BANK" then
		
		-- если хотим положить что-то в банк
		if hasNonAuctionableItems and possiblyHasFreeBankSlots then
			print("Складываю в банк всё что нельзя продать")
			private.changeState("WAITING_FOR_BAGS2BANK")
			local t = lib.nonbatchItems()
			for i,v in ipairs(t) do
				table.remove(v,1)
			end
			GBM:SomeItemsToBank(t)
			return
		end
		
		-- если хотим взять что-то из банка
		if hasFreeBagSlots and possiblyHasAuctionableBankItems then
			print("Забираю из банка всё что можно продать")
			private.changeState("WAITING_FOR_BANK2BAGS")
			local t = lib.batchBankItems()
			for i,v in ipairs(t) do
				table.remove(v,1)
			end
			GBM:SomeItemsFromBank(t)
			return
		end
		
		-- если в банке делать нечего...
		print("Хм... а зачем я в пришёл в банк?")
		CloseBankFrame()
		private.changeState("THINKING")
		return
	end
	
	-- процесс складывания хлама в банк
	if private.state == "WAITING_FOR_BAGS2BANK" then
		if not hasNonAuctionableItems then
			print("Все итемы которые нельзя продать сложены в банк")
			CloseBankFrame()
			private.changeState("THINKING")
			return
			
		elseif not private.hasFreeBankSlots then
			print("Закончилось место в банке")
			CloseBankFrame()
			private.changeState("THINKING")
			return
			
		elseif not bankAvailable then
			local msg = "Неожиданно закрыто окно банка"
			private.ERROR(msg)
			return
			
		elseif private.stateTime() > 30 then
			local msg = "Что-то с банком пошло не так"
			private.ERROR(msg)
			CloseBankFrame()
			return
			
		else
			return
			
		end
	end
	
	-- процесс сбора хлама из банка
	if private.state == "WAITING_FOR_BANK2BAGS" then
		if not possiblyHasAuctionableBankItems then
			print("Все итемы которые можно продать собраны из банка")
			CloseBankFrame()
			private.changeState("THINKING")
			return
			
		elseif not hasFreeBagSlots then
			print("Закончилось место в сумке")
			CloseBankFrame()
			private.changeState("THINKING")
			return
			
		elseif not bankAvailable then
			local msg = "Неожиданно закрыто окно банка"
			private.ERROR(msg)
			return
			
		elseif private.stateTime() > 30 then
			local msg = "Что-то с банком пошло не так"
			private.ERROR(msg)
			CloseBankFrame()
			return
			
		else
			return
			
		end
	end
	
	local mayGatherMail = mailboxAvailable and
		InboxFrame:IsVisible() and private.GameTime - mailboxOpenedTime > 5
		and private.state == "WAITING_FOR_MAILBOX"
	
	if mayGatherMail then
		print("Начинаю собирать почту")
		private.changeState("WAITING_FOR_POSTAL")
		oldAssets = assets()
		prevAssets = assets()
		prevAssetsTime = private.GameTime
		Postal.modules.OpenAll:OpenAll()
	end
	
	-- процесс сбора почты
	if private.state == "WAITING_FOR_POSTAL" then
		if lib.FreeBagSlots() <= 1 then
			-- Postal надо настроить оставлять один слот пустым, можно 0, но не больше
			print("В сумке один или менее свободный слот, прекращаю сбор почты")
			CloseMail()
			updateNextMailTime()
			private.changeState("THINKING")
			return
			
		elseif not mailboxAvailable then
			private.ERROR("Неожиданно закрыто окно почты")
			updateNextMailTime()
			return
			
		elseif private.GameTime - prevAssetsTime > 15 then
			prevAssetsTime = private.GameTime
			local cur = assets()
			if cur == prevAssets then
				print("Похоже за этот сеанс собрать больше нечего")
				CloseMail()
				updateNextMailTime()
				private.changeState("THINKING")
			else
				prevAssets = cur
			end
			return
			
		else
			return
			
		end
	end
	
	-- включить RealTime search если не включен
	if auctionAvailable and AucAdvanced.Modules.Util.SearchUI.Private.SearcherRealTime 
			and not AucAdvanced.Modules.Util.SearchUI.Private.SearcherRealTime.IsScanning then
		-- чтоб это работало нужен патч в SearchMain.lua: lib.NewSearcher()
		--  	private["Searcher"..searcherName] = {}
		--		return searcher, lib, private["Searcher"..searcherName]
		print("Включаю realtime search")
		AucAdvanced.Modules.Util.SearchUI.Private.SearcherRealTime.ButtonPressed(nil, "LeftButton")
	end
	
	-- запустить скан если не запущен
	if auctionAvailable then
		if private.allowedScan() then
			print("Похоже сейчас ничего не запущено.. Запускаю полный скан")
			AucAdvanced.Scan.StartScan("", "", "", nil, nil, nil, nil, nil)
		elseif allowedResume then
			print("Скан почему-то не запущен хотя стек сканов не пуст, нажимаю кнопку play")
			AucAdvanced.Modules.Util.ScanButton.Private.play()
		end
	end
	
	-- проверить что аукцион не закрыт
	if (private.state == "SCANNING" or private.state == "SCAN_BEFORE_POSTING" or private.state == "POSTING") and not auctionAvailable then
		private.ERROR("Неожиданно закрыто окно аукциона")
		return
	end
	
	if auctionAvailable then

		if private.state == "SCANNING" then
			return
			
		elseif private.state == "SCAN_BEFORE_POSTING" then
			if time() - Nakamar.ScanCompletedTime[GetFaction()] < maxScanAge then
				private.doPosting()
			elseif private.stateTime() > 7200 then
				private.ERROR("сканирую уже больше двух часов, но до сих пор нет свежего скана")
			end
			return
			
		elseif private.state == "POSTING" then
			local left = #AucAdvanced.Post.Private.postRequests	

			if left == 0 then
				local postable = #lib.batchItems()
				if postable == 0 then
					print("весь товар выложен на аукцион")
					private.doScanning()
				else
					private.ERROR("часть товара не удалось выложить на аукцион")
				end

			elseif private.GameTime - prevAssetsTime > 300 then
				prevAssetsTime = private.GameTime
				local cur = assets()
				if cur == prevAssets then
					private.ERROR("за 5 минут ни один предмет не исчез из сумок")
				else
					prevAssets = cur
				end
				
			elseif private.stateTime() > 3 * 3600 then
				private.ERROR("прошло уже три часа, а всё ещё не весь товар выложен")
			end
			return
		
		else -- state ~= "POSTING" | "SCAN_BEFORE_POSTING" | "SCANNING" and auctionframe opened
			local postable = #lib.batchItems()
			local fresh = time() - Nakamar.ScanCompletedTime[GetFaction()] < maxScanAge
			if postable > 0 then
				if fresh then
					private.doPosting()
				else
					private.doScanBeforePosting()
				end
				return
			elseif private.state == "WAITING_FOR_AUCTION" then
				private.doScanning()
				return
			end
		end
		
	end

	if AucAdvanced.Settings.GetSetting("util.nakamar.allow_long_scans") and
			auctionAvailable and private.state == "WAITING_FOR_MAILBOX" then
		private.lastStateChangeTime = private.GameTime
		return
	end
	
	if private.state == "WAITING_FOR_AUCTION" or
			private.state == "WAITING_FOR_MAILBOX" or
			private.state == "WAITING_FOR_BANK" then
		
		local destination = private.destination
		
		local delta = private.stateTime()
		if private.GameTime - lastMovementRequest > 300 then
			print(("Жду %s уже %d минут, повторяю запрос"):format(destination, private.stateTime() / 60))
			private.GoTo(destination)
			if delta > 3600 then
				print("Прошло более часа")
				private.ERROR("проблемы с движением")
			end
		end
		return
	end
	
	private.ERROR(string.format("я хз чо делать, текущее состояние: %s", private.state))
end

function private.doScanBeforePosting()
	print("Ждём пока обновится скан прежде чем выкладывать товар")
	private.changeState("SCAN_BEFORE_POSTING")
end

function private.doScanning()
	print("Сканирую аукцион")
	private.changeState("SCANNING")
end

function private.doPosting()
	if #AucAdvanced.Post.Private.postRequests > 0 then
		print("что-то уже выкладывается, отменяю")
		AucAdvanced.Post.Private.postRequests = {}
		return
	end
	private.changeState("POSTING")
	prevAssetsTime = private.GameTime
	prevAssets = assets()
	print("Выкладываю всё из сумок на аукцион")
	local items = lib.batchItems();
	local stage1 = {}
	local counts = {}
	for i,v in ipairs(items) do
		local link, bag, slot = unpack(v)
		local _, itemCount = GetContainerItemInfo(bag, slot)
		local sig = AucAdvanced.API.GetSigFromLink(link)
		local postedStack = AucAdvanced.Settings.GetSetting("util.appraiser.item."..sig..".stack") or AucAdvanced.Settings.GetSetting("util.appraiser.stack")
		if postedStack == "max" then
			_, _, _, _, _, _, _, postedStack = GetItemInfo(hyperlink)
		end
		stage1[sig] = (stage1[sig] or 0)
		if itemCount <= postedStack then
			-- it is not guaranteed that auc-advanced can post this item
			-- example: have two stack of 15, and posting in stacks of 20, and other bag slots are full with something else
			stage1[sig] = stage1[sig] + 1
		end
		counts[sig] = (counts[sig] or 0) + itemCount
	end
	for i,v in ipairs(items) do
		local link, bag, slot = unpack(v)
		local _, itemCount = GetContainerItemInfo(bag, slot)
		local sig = AucAdvanced.API.GetSigFromLink(link)
		local postedStack = AucAdvanced.Settings.GetSetting("util.appraiser.item."..sig..".stack") or AucAdvanced.Settings.GetSetting("util.appraiser.stack")
		if postedStack == "max" then
			_, _, _, _, _, _, _, postedStack = GetItemInfo(hyperlink)
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
		-- выложить не получится, так как во всех слотах больше чем надо итемов
		-- а свободных ячеек, чтоб разделить - нет
		return
	end
	for i, v in ipairs(stage2) do
		local sig, count = unpack(v)
		AucAdvanced.Modules.Util.Appraiser.Private.frame.PostBySig(sig)
	end
end

function private.OnUpdate(me, elapsed)
	frames = frames + 1
    everySecondTimer = everySecondTimer + elapsed
	private.GameTime = private.GameTime + elapsed
    if (everySecondTimer > 1.0) then
        private:everySecond()
        everySecondTimer = 0.0
    end
end

function private.OnEvent(self, event, ...)
	for i, f in ipairs(eventHandlers[event]) do
		f(...)
	end
end

function private.stateTime()
	return private.GameTime - private.lastStateChangeTime
end

function private.playSound(s)
	if Nakamar.sounds and Nakamar.sounds[s] then
		PlaySoundFile(Nakamar.sounds[s])
	end
end

function private.changeState(s)
	if private.state == s then return end
	if s ~= "ERROR" then
		private.playSound("after"..private.state)
	end
	private.playSound(s)
	private.state = s
	private.lastStateChangeTime = private.GameTime
end

function lib.OnLoad()
	Nakamar = Nakamar or {}

	private.waitbeforequitseconds = random(30,60)
	private.changeState("LOADING")
	private.frame = CreateFrame("Frame", "NakamarFrame", UIParent)
	private.frame:SetFrameStrata("TOOLTIP")
	private.frame:SetPoint("TOPLEFT", 10, -10)
	private.frame:SetWidth(100)
	private.frame:SetHeight(100)
	private.frame:SetScript("OnUpdate", private.OnUpdate)
	private.frame:SetScript("OnEvent", private.OnEvent)
	private.frame:Show()
	RegisterEvent("BANKFRAME_OPENED",
		function() bankAvailable = true; private.updateBankStats(); NCurrentState("Банк") end)
	RegisterEvent("BANKFRAME_CLOSED",
		function() bankAvailable = nil; NCurrentState("хз"); end)
	RegisterEvent("MAIL_INBOX_UPDATE",
		function() if mailboxOpened then mailboxAvailable = true end end)
	RegisterEvent("MAIL_SHOW",
		function() mailboxOpenedTime = private.GameTime; mailboxOpened = true; NCurrentState("Почта") end)
	RegisterEvent("MAIL_CLOSED",
		function() mailboxAvailable = false; mailboxOpened = false; NCurrentState("хз") end)
	AucAdvanced.Settings.SetDefault("util.nakamar.printwindow", 1)
	RegisterEvent("CHAT_MSG_WHISPER", private.Chat)
	
	Nakamar.ScanCompletedTime = Nakamar.ScanCompletedTime or {}
	Nakamar.ScanCompletedTime[GetFaction()] = Nakamar.ScanCompletedTime[GetFaction()] or 0
end

function private.HookAH()
    
end

function private.table2string(t)
	if type(t)=="string" then return '"'..t..'"'
	elseif type(t)=="table" then
		local ans = "{ "
		local cnt=0
		for k,v in pairs(t) do
			if cnt>0 then ans = ans..", " end
			cnt = cnt + 1
			ans = ans .. private.table2string(k) .. ": " .. private.table2string(v)
		end
		return ans .. " }"
	else return tostring(t)
	end
end

-- возвращает true если НИ ОДИН скан не запущен, не стоит на паузе
-- то есть если аукционер вообще ничего не делает
function private.allowedScan()
	return not AucAdvanced.Scan.IsPaused() and not AucAdvanced.Scan.IsScanning()
		and AucAdvanced.Scan.GetScanCount() == 0
end

local lastScanningTime = time()
-- возвращает true если в течение последних была аукцион был открыт 
-- но ничего не сканировал и не стоял на паузе
-- нужно запускать эту функцию каждый фрейм даже если аукцион закрыт
function private.allowedResume()
	if not auctionAvailable or AucAdvanced.Scan.IsPaused() or AucAdvanced.Scan.IsScanning() or AucAdvanced.Buy.Private.Prompt:IsVisible() then
		lastScanningTime = time()
	end
	if time() - lastScanningTime > 60 then
		lastScanningTime = time()
		return true
	end
	return false
end

function private.processScan(stats)
	if not stats.wasIncomplete then
		local matched = 0
		local scandata = AucAdvanced.Scan.GetScanData()
		
		for pos, data in ipairs(scandata.image) do
			if AucAdvanced.Scan.Private.IsInQuery(stats.query, data) then
				matched = matched + 1
			end
		end
				
		--print(string.format("%d из %d лотов соответствует запросу", matched, #scandata.image))
		if matched == #scandata.image then
			print("Завершен полный скан")
			Nakamar.ScanCompletedTime[GetFaction()] = time()
		else
			--print("Это был неполный скан")
		end
	end
end

function lib.Processor(callbackType, ...)
	if (callbackType == "config") then
		private.SetupConfigGui(...)
    elseif (callbackType == "auctionui") then
        private.HookAH()
	elseif callbackType == "auctionopen" then
		auctionAvailable=true
		NCurrentState("Аукцион")
	elseif callbackType == "auctionclose" then
		auctionAvailable=false
		NCurrentState("хз")
	elseif callbackType == "scanstats" then
		private.processScan(...)
	end
end

function private.SetupConfigGui(gui)
    local id = gui:AddTab(lib.libName, lib.libType.." Modules")
	gui:AddControl(id, "Checkbox", 0, 1, "util.nakamar.enabled", "Включить")
	gui:AddControl(id, "Checkbox", 0, 1, "util.nakamar.close_ah_when_scanning", "Закрывать аукцион во время скана")
	gui:AddTip(id, [[Если включено, то когда аддон сканирует аукцион,
		но понадобилось сделать что-нибудь более важное,
		к примеру проверить почту - то он автоматически закроет окно аукциона.
		Но такое поведение может иногда мешать.]])
	gui:AddControl(id, "Subhead",     0, "Окно чата")
	gui:AddControl(id, "Selectbox", 0, 1, AucAdvanced.configFramesList, "util.nakamar.printwindow")
	gui:AddTip(id, "выберите, куда Накамар будет выводить свои сообщения")
	gui:AddControl(id, "Checkbox", 0, 1, "util.nakamar.quit_on_error", "Закрывать WoW если что-нибудь идёт не так")
	gui:AddControl(id, "Checkbox", 0, 1, "util.nakamar.allow_long_scans", "разрешить долие сканы")
	gui:AddTip(id, "не выдавать ошибку если нужно идти на почту, но мы не двигаемся с места а продолжаем сканировать")
end

-- returns all items from the bags or auctionable only
function lib.bagItems(filter)
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

function lib.bankItems(filter)
	local bankSlots = { -1, 5, 6, 7, 8, 9, 10, 11 } -- from BankMover.lua
	local items = {}
	for i, bag in ipairs(bankSlots) do
		if GBM:IsBankBag(bag) then
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

function lib.map(f, t)
	local ans = {}
	for i,v in ipairs(t) do
		tinsert(ans, f(v))
	end
	return ans
end

function lib.filter(f, t)
	local ans = {}
	for i,v in ipairs(t) do
		if f(v) then
			tinsert(ans,v)
		end
	end
	return ans
end

function lib.tryBatch(link)
	local name, link, _, _, _, _, _, stack = GetItemInfo(link)
	local sig = AucAdvanced.API.GetSigFromLink(link)
	
	if stack == 1 then
		print(
			string.format("Новый предмет: %s, не стекается, поэтому автоматически выкладываем по одному", 
			link))
		AucAdvanced.Settings.SetSetting('util.appraiser.item.'..sig..'.bulk', true)
	end
end

local isBatch = function(link)
	local sig = AucAdvanced.API.GetSigFromLink(link)
	
	return AucAdvanced.Settings.GetSetting('util.appraiser.item.'..sig..'.bulk')
end

function lib.isBatch(link, bag, slot)
	if AucAdvanced.Post.IsAuctionable(bag, slot) then
		if isBatch(link) then
			return true
		end
		lib.tryBatch(link)
		return isBatch(link)
	else
		return false
	end
end

function lib.batchItems()
	return lib.bagItems(lib.isBatch)
end

function lib.batchBankItems()
	return lib.bankItems(lib.isBatch)
end

function lib.nonbatchItems()
	return lib.bagItems(function(...) return not lib.isBatch(...) end)
end

function private.Chat()
	if not AucAdvanced.Settings.GetSetting('util.nakamar.enabled') then return end
	private.ERROR("получен whisper")
end

function lib.NeedPurchaseConfirmation()
	return AuctionFrame and AuctionFrame:IsVisible() and AucAdvanced.Buy.Private.Prompt:IsVisible()
end

function lib.ConfirmPurchase()
	if lib.NeedPurchaseConfirmation() then
		AucAdvanced.Buy.Private.Prompt.Yes:Click()
	end
end

function lib.FreeBagSlots()
	local free=0
	for bag=0,NUM_BAG_SLOTS do
		local bagFree,bagFam = GetContainerNumFreeSlots(bag)
		if bagFam == 0 then
			free = free + bagFree
		end
	end
	return free
end

