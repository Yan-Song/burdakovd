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
local lib,parent,private = AucAdvanced.NewModule(libType, libName)
if not lib then return end
lib.API = {}



private.state = "INITIALIZING"
private.last_change = 0
private.bankSlots = true
private.bankTime = -10000.0
private.lastToBank = -1000.0
private.nextMailTime = 0.0 -- когда в следующий раз можно будет зайти на почту
private.lastscan = 0

local ipairs = ipairs
local pairs = pairs
local _time=0.0
private.gtime=0.0
local bankAvailable = nil
local mailboxAvailable = nil
local mailboxOpened = false
local auctionAvailable = nil
local handlers = {}
local lastnotification = -1000.0
local mailboxOpenedTime = 0
local oldItemsCount = 0
local prevItemsCount = 0
local prevICTime = 0
local freshnessforposting = 7200 -- 2h

local RegisterEvent = function(event, f)
	private.frame:RegisterEvent(event)
	if handlers[event] == nil then
		handlers[event] = {}
	end
	table.insert(handlers[event], f)
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
	table.insert(Nakamar.logs, {time(), tostring(s)})
end
private.print = print

function lib.isBankAvailable()
	return bankAvailable
end

function private.updateBankStats()
	if not bankAvailable then return end -- return if bank window is not open
	local old = private.bankSlots
	private.bankSlots = not not GBM:FindFreeBankSlot() -- convert to boolean
	private.bankTime = private.gtime
	if private.bankSlots ~= old then
		if private.bankSlots then print("Обнаружено что в банке ещё есть место.")
		else print("Обнаружено что в банке нет места.")
		end
	end
end

function private.ERROR()
	private.playSound("ERROR")
	print("что-то не так..")
	if(AucAdvanced.Settings.GetSetting("util.nakamar.quit_on_error")) then
		print("Quit через "..tostring(private.waitbeforequitseconds).." секунд")
		private.changeState("QUIT")
		NDoNotRestart("что-то не так...")
	else
		private.changeState("ERROR")
		private.changeState("THINKING")
	end
	Screenshot()
end

local updateNextMailTime = function()
	local wait
	local cur = GBM:InBagsItemCount() + GetMoney()
	if cur == oldItemsCount then
		print("В этот раз ничего с почты собрать не удалось, так что вернусь сюда не скоро")
		wait = random(5000,10000)
	else
		print("что-то с почты собрано, так что скоро можно будет проверить её ещё раз")
		wait = random(60,100)
	end
	private.nextMailTime = private.gtime + wait
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

function private.GoToAuction()
	CloseAuctionHouse()
	NGoTo("Аукцион")
end

function private.GoToMail()
	CloseMail()
	NGoTo("Почта")
end

function private.GoToBank()
	CloseBankFrame()
	NGoTo("Банк")
end

local saidBank = false
function private.everySecond()
	NKeepAlive()
	
	NNeedPurchaseConfirmation(lib.NeedPurchaseConfirmation())
	
	private.updateBankStats()
	
	if private.state == "QUIT" and private.stateTime()>private.waitbeforequitseconds then
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
	
	-------- THINKING
    if private.state == "THINKING" and #lib.nonbatchItems()>0 then
		if private.bankSlots or private.bankTime<private.gtime-3600 then
			print(string.format("В сумках есть %d итемов, которые не выставляются на аукцион, надо отнести их в банк", #lib.nonbatchItems()))
			private.GoToBank()
			private.changeState("WAITING_FOR_BANK")
			return
		else
			if not saidBank then
				print(string.format("В сумках есть %d итемов, которые не выставляются на аукцион, но в банке места уже нет.", #lib.nonbatchItems()))
				saidBank = true
			end
		end
	end
	
	if private.state ~= "THINKING" then
		saidBank = false
	end
	
	if private.state=="WAITING_FOR_BANK" and (#lib.nonbatchItems()==0 or not (private.bankSlots or private.bankTime<private.gtime-3600)) then
		CloseBankFrame()
		private.changeState("THINKING")
	return end
	
	local needWaitForMail = (private.nextMailTime - private.gtime < 120) and GBM:FindFreeBagSlot()
	
	if private.state == "THINKING" and not needWaitForMail and #lib.batchItems()>0 then
		print(string.format("В сумках есть %d итемов на продажу, надо идти на аукцион", #lib.batchItems()))
		private.GoToAuction()
		private.changeState("WAITING_FOR_AUCTION")
		return
	end
	
	if (private.state == "THINKING" or private.state == "SCANNING") and private.gtime > private.nextMailTime and GBM:FindFreeBagSlot() then
		-- пора идти на почту
		if AucAdvanced.Settings.GetSetting('util.nakamar.close_ah_when_scanning') then
			CloseAuctionHouse()
		end
		print("Надо проверить почтовый ящик")
		private.GoToMail()
		private.changeState("WAITING_FOR_MAILBOX")		
		return
	end
	if private.state=="WAITING_FOR_MAILBOX" and not GBM:FindFreeBagSlot() then private.changeState("THINKING"); return end
	
	if private.state == "THINKING" and needWaitForMail then
		return
	end
	
	if private.state == "THINKING" then
		print("Делать пока нечего, но можно пойти посканировать аукцион")
		private.GoToAuction()
		private.changeState("WAITING_FOR_AUCTION")
		return
	end
	
	-------- по ситуации
	if bankAvailable and private.state ~= "WAITING_FOR_BAGS2BANK" and #lib.nonbatchItems()>0 
		and private.bankSlots and private.lastToBank<private.gtime-10 then
			private.lastToBank = private.gtime
			private.changeState("WAITING_FOR_BAGS2BANK")
			local t = lib.nonbatchItems()
			for i,v in ipairs(t) do
				table.remove(v,1)
			end
			GBM:SomeItemsToBank(t)
			return
	end
	
	if private.state == "WAITING_FOR_BAGS2BANK" then
		if #lib.nonbatchItems()==0 then
			print("Все итемы которые нельзя продать сложены в банк")
			CloseBankFrame()
			private.changeState("THINKING")
			return
		elseif not private.bankSlots then
			print("Закончилось место в банке")
			CloseBankFrame()
			private.changeState("THINKING")
			return
		elseif not bankAvailable then
			print("Неожиданно закрыто окно банка")
			private.ERROR()
			return
		elseif private.stateTime()>30 then
			print("что-то с банком пошло не так")
			private.ERROR()
			CloseBankFrame()
			return
		else
			return
		end
	end
	
	if mailboxAvailable and InboxFrame:IsVisible() and private.gtime-mailboxOpenedTime>3 and private.state~="WAITING_FOR_POSTAL" then
		print("Начинаю собирать почту")
		private.changeState("WAITING_FOR_POSTAL")
		oldItemsCount = GBM:InBagsItemCount() + GetMoney()
		prevItemsCount = oldItemsCount
		prevICTime = private.gtime
		Postal.modules.OpenAll:OpenAll()
	end
	
	if private.state == "WAITING_FOR_POSTAL" then
		if not GBM:FindFreeBagSlot() then
			print("Закончилось место в сумке")
			CloseMail()
			updateNextMailTime()
			private.changeState("THINKING")		
			return
		elseif not mailboxAvailable then
			print("Неожиданно закрыто окно почты")
			private.ERROR()
			updateNextMailTime()
			return
		elseif private.gtime - prevICTime > 5 then
			prevICTime = private.gtime
			local cur = GBM:InBagsItemCount() + GetMoney()
			if cur == prevItemsCount then
				print("Похоже больше с почты собрать нечего")
				CloseMail()
				updateNextMailTime()
				private.changeState("THINKING")		
			else
				prevItemsCount = cur
			end
			return
		else
			return
		end
	end
	
	if auctionAvailable and AucAdvanced.Modules.Util.SearchUI.Private.SearcherRealTime 
			and not AucAdvanced.Modules.Util.SearchUI.Private.SearcherRealTime.IsScanning then
		-- чтоб это работало нужен патч в SearchMain.lua: lib.NewSearcher()
		--  	private["Searcher"..searcherName] = {}
		--		return searcher, lib, private["Searcher"..searcherName]
		print("Включаю realtime search")
		AucAdvanced.Modules.Util.SearchUI.Private.SearcherRealTime.ButtonPressed(nil, "LeftButton")
	end
	
	if auctionAvailable and private.allowedScan() then
		print("Похоже сейчас ничего не запущено.. Запускаю полный скан")
		AucAdvanced.Scan.StartScan()
	end
	
	if (private.state == "SCANNING" or private.state == "SCAN_BEFORE_POSTING" or private.state == "POSTING") and not auctionAvailable then
		print("Неожиданно закрыто окно аукциона")
		private.ERROR()
		return
	end
	
	if auctionAvailable then

		if private.state == "SCANNING" then
			return
			
		elseif private.state == "SCAN_BEFORE_POSTING" then
			private.lastscan = private.lastscan or 0
			if time() - private.lastscan < freshnessforposting then
				private.doPosting()
			elseif private.stateTime()>7200 then
				print("сканирую уже больше двух часов, но до сих пор нет свежего скана")
				private.ERROR()
			end
			return
			
		elseif private.state == "POSTING" then
			local left = #AucAdvanced.Post.Private.postRequests	
			if left==0 then
				local postable = #lib.batchItems()
				if postable == 0 then
					print("весь товар выложен на аукцион")
					private.doScanning()
				else
					print("часть товара не удалось выложить на аукцион")
					private.ERROR()
				end
			elseif private.gtime - prevICTime > 60 then
				prevICTime = private.gtime
				local cur = GBM:InBagsItemCount()
				if cur == prevItemsCount then
					print("за 60 секунд ни один предмет не исчез из сумок")
					private.ERROR()
				else
					prevItemsCount = cur
				end
			elseif private.stateTime()>3600 then
				print("прошёл уже час, а всё ещё не весь товар выложен")
				private.ERROR()
			end
			return
		
		else -- state ~= "POSTING" | "SCAN_BEFORE_POSTING" | "SCANNING" and auctionframe opened
			local postable = #lib.batchItems()
			local fresh = (time() - private.lastscan < freshnessforposting)
			if postable>0 then
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


	if AucAdvanced.Settings.GetSetting("util.nakamar.allow_long_scans") and auctionAvailable and private.state=="WAITING_FOR_MAILBOX" then
		private.last_change = private.gtime
		return
	end
	
	if private.state == "WAITING_FOR_AUCTION" or private.state == "WAITING_FOR_MAILBOX" or private.state == "WAITING_FOR_BANK" then
		local msgs = { WAITING_FOR_AUCTION="жду аукциона уже %d секунд", 
			WAITING_FOR_MAILBOX="жду почтовый ящик уже %d секунд", WAITING_FOR_BANK="жду банк уже %d секунд" }
		if private.last_change>lastnotification	then lastnotification = private.last_change end
		local delta = private.stateTime()
		if private.gtime - lastnotification > 60 then
			print(msgs[private.state]:format(private.stateTime()))
			lastnotification = private.gtime
			if delta>300 then
				print("Прошло более пяти минут")
				private.ERROR()
			end
		end
		return
	end
	
	print(string.format("я хз чо делать (%s)",private.state))
	private.ERROR()
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
	prevICTime = private.gtime
	prevItemsCount = GBM:InBagsItemCount()
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
			-- example: have two stack of 15, and posting in stacks of 20, and other bag slots are  full with something else
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
		if firstPost==0 then
			firstPost = postedStack
		end
		if itemCount <= firstPost then
			-- it is guaranteed that auc-advanced can post this item
			stage1[sig] = stage1[sig] + 1000
		end
	end
	local stage2 = {}
	for sig, count in pairs(stage1) do
		table.insert(stage2, {sig, stage1[sig]})
	end
	table.sort(stage2, function(x,y) return x[2]>y[2] end)
	if stage2[1][2]==0 and not GBM:FindFreeBagSlot() then
		-- выложить не получится, так как во всех слотах больше чем надо итемов
		-- а свободных ячеек, чтоб разделить - нет
		return
	end
	for i, v in ipairs(stage2) do
		local sig, count = unpack(v)
		AucAdvanced.Modules.Util.Appraiser.Private.frame.PostBySig(sig)
	end
end

function private.OnUpdate(me,elapsed)
    _time = _time+elapsed
	private.gtime = private.gtime+elapsed
    if(_time>1.0) then
        private:everySecond()
        _time = 0.0
    end
end

function private.OnEvent(self, event, ...)
	for i, f in ipairs(handlers[event]) do
		f(...)
	end
end

function private.stateTime()
	return private.gtime - private.last_change
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
	private.last_change = private.gtime
end

function lib.OnLoad()
	if not Nakamar then Nakamar = {} end

	private.waitbeforequitseconds = random(30,60)
	private.changeState("THINKING")
	private.frame = CreateFrame("Frame", "NakamarFrame", UIParent)
	private.frame:SetFrameStrata("TOOLTIP")
	private.frame:SetPoint("TOPLEFT", 10, -10)
	private.frame:SetWidth(100)
	private.frame:SetHeight(100)
	private.frame:SetScript("OnUpdate", private.OnUpdate)
	private.frame:SetScript("OnEvent", private.OnEvent)
	private.frame:Show()
	RegisterEvent("BANKFRAME_OPENED", function() bankAvailable = true; private.updateBankStats() end)
	RegisterEvent("BANKFRAME_CLOSED", function() bankAvailable = nil end)
	RegisterEvent("MAIL_INBOX_UPDATE", function() if mailboxOpened then mailboxAvailable = true end end)
	RegisterEvent("MAIL_SHOW", function() mailboxOpenedTime = private.gtime; mailboxOpened = true end)
	RegisterEvent("MAIL_CLOSED", function() mailboxAvailable = false; mailboxOpened = false end)
	AucAdvanced.Settings.SetDefault("util.nakamar.printwindow", 1)
	RegisterEvent("CHAT_MSG_WHISPER", private.Chat)
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

-- возвращает true если НИ ОДИН скан не запущен, не стоит на паузе, очередь сканов пуста, 
-- то есть если аукционер вообще ничего не делает
function private.allowedScan()
	return not AucAdvanced.Scan.IsPaused() and not AucAdvanced.Scan.IsScanning() and
		AucAdvanced.Scan.GetScanCount()==0
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
			private.lastscan = time()
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
	elseif callbackType == "auctionclose" then
		auctionAvailable=false
	elseif callbackType == "scanstats" then
		private.processScan(...)
	end
end

function private.SetupConfigGui(gui)
    local id = gui:AddTab(lib.libName, lib.libType.." Modules")
	gui:AddControl(id, "Checkbox", 0, 1, "util.nakamar.enabled", "Включить")
	gui:AddControl(id, "Checkbox", 0, 1, "util.nakamar.close_ah_when_scanning", "Закрывать аукцион во время скана")
	gui:AddTip(id, [[Если включено, то когда аддон сканирует аукцион, но понадобилось сделать что-нибудь более важное,
					 к примеру проверить почту - то он автоматически закроет окно аукциона. Но такое поведение может иногда мешать.]])
	gui:AddControl(id, "Subhead",     0,	"Окно чата")
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
		for slot = GetContainerNumSlots(bag), 1, -1 do
			local link = GetContainerItemLink(bag, slot)
			if link and filter(link,bag,slot) then
				table.insert(items,{link, bag, slot} )
			end
		end
	end
	return items
end

function lib.map(f, t)
	local ans = {}
	for i,v in ipairs(t) do
		table.insert(ans, f(v))
	end
	return ans
end

function lib.filter(f, t)
	local ans = {}
	for i,v in ipairs(t) do
		if f(v) then
			table.insert(ans,v)
		end
	end
	return ans
end

function lib.isBatch(link,bag,slot)
	local sig = AucAdvanced.API.GetSigFromLink(link)
	return AucAdvanced.Post.IsAuctionable(bag, slot) and AucAdvanced.Settings.GetSetting('util.appraiser.item.'..sig..'.bulk')
end

function lib.batchItems()
	return lib.bagItems(lib.isBatch)
end

function lib.nonbatchItems()
	return lib.bagItems(function(...) return not lib.isBatch(...) end)
end

function private.Chat()
	if not AucAdvanced.Settings.GetSetting('util.nakamar.enabled') then return end
	print("получен whisper")
	private.ERROR()
end

function lib.NeedPurchaseConfirmation()
	return AuctionFrame and AuctionFrame:IsVisible() and AucAdvanced.Buy.Private.Prompt:IsVisible()
end

function lib.ConfirmPurchase()
	if lib.NeedPurchaseConfirmation() then
		AucAdvanced.Buy.Private.Prompt.Yes:Click()
	end
end
