GBM = AceLibrary("AceAddon-2.0"):new("AceConsole-2.0", "AceEvent-2.0")
local GL = AceLibrary("Gratuity-2.0")
local bankAvailable = nil
local guildBankAvailable = nil
local bankSlots = { -1, 5, 6, 7, 8, 9, 10, 11 }

GBM.revision = tonumber(string.sub("$Revision: 54121 $", 12, -3))

local L = {
	["Bag"] = "Bag",
	["Could not find any more space in your Guild Bank."] = "Could not find any more space in your Guild Bank.",
	["Guild Bank not available."] = "Guild Bank not available.",
	["No more bag space."] = "No more bag space.",
	["Have patience, it takes quite a while to move ALOT of items."] = "Have patience, it takes quite a while to move ALOT of items.",
}
if GetLocale() == "frFR" then
	L = {
		["Bag"] = "Sac",
	}
end
if GetLocale() == "deDE" then
	L = {
		["Bag"] = "Beh�lter",
	}
end
if GetLocale() == "esES" then
	L = {
		["Bag"] = "Bolsa",
	}
end
if GetLocale() == "koKR" then
	L = {
		["Bag"] = "가방",
	}
end
if GetLocale() == "zhTW" then
	L = {
		["Bag"] = "容器",
	}
end
if GetLocale() == "zhCN" then
	L = {
		["Bag"] = "容器",
	}
end
if GetLocale() == "ruRU" then
    L = {
            ["Bag"] = "Сумка",
            ["Could not find any more space in your Guild Bank."] = "В гильдбанке больше нет места.",
            ["Guild Bank not available."] = "Нет доступа к гильдбанку.",
            ["Bank not available."] = "Нет доступа к банку.",
            ["No more bag space."] = "Не хватает места в сумках.",
            ["No more bank space."] = "Не хватает места в банке.",
            ["Have patience, it takes quite a while to move ALOT of items."] = "Сохраняйте спокойствие, для переноса большого количества предметов понадобится некоторое время",
            ["Both Bank and GuildBank are not available."] = "Недоступен ни банк ни гильдбанк",
            ["Done."] = "Перенос завершен.",
            ["Get"] = "Берём",
    }
end
        
function GBM:OnInitialize()
	self:RegisterChatCommand("/putall", function() self:PutAll() end)
	self:RegisterChatCommand("/getall", function() self:GetAll() end)
    self:RegisterChatCommand("/getunique", function() self:GetUnique() end)
end

function GBM:OnEnable()
	self:RegisterEvent("GUILDBANKFRAME_OPENED", function() guildBankAvailable = true end)
	self:RegisterEvent("GUILDBANKFRAME_CLOSED", function() guildBankAvailable = nil end)
	self:RegisterEvent("BANKFRAME_OPENED", function() bankAvailable = true end)
	self:RegisterEvent("BANKFRAME_CLOSED", function() bankAvailable = nil end)
end

function GBM:GetAll()
    if self:IsBankAvailable() then
        self:BankToBags()
        slotLocks = {}
        return
	end
    self:Print(L["Bank not available."])
    return
end

function GBM:GetUnique()
    if self:IsBankAvailable() then
        self:BankToBagsUnique()
        slotLocks = {}
        return
	end
    self:Print(L["Bank not available."])
    return
end

function GBM:PutAll()
    if self:IsGuildBankAvailable() then
        self:BagsToGuildBank()
        slotLocks = {}
        return
    end
    if self:IsBankAvailable() then
        self:BagsToBank()
        slotLocks = {}
        return
    end
    self:Print(L["Both Bank and GuildBank are not available."])
end

function GBM:BagsToGuildBank()
    self:Print(L["Have patience, it takes quite a while to move ALOT of items."])
	local items = {}
	for bag = NUM_BAG_FRAMES, 0, -1 do
		for slot = GetContainerNumSlots(bag), 1, -1 do
			local movable = true
			local link = GetContainerItemLink(bag, slot)
			if link then
				if self:IsMovable(bag, slot) then
					result = self:BagItemMove2GuildBank(bag, slot)
					if result ~= true then
						self:Print(result)
						return
					end
				end
			end
		end
	end
    self:Print(L["Done."])
end

function GBM:BagsToBank()
	local items = {}
	for bag = NUM_BAG_FRAMES, 0, -1 do
		for slot = GetContainerNumSlots(bag), 1, -1 do
			local movable = true
			local link = GetContainerItemLink(bag, slot)
			if link then
				if self:IsMovable(bag, slot) then
					result = self:BagItemMove2Bank(bag, slot)
					if result ~= true then
						self:Print(result)
						return
					end
				end
			end
		end
	end
    self:Print(L["Done."])
end

function GBM:BankToBags()
	for i, fromBagId in ipairs(bankSlots) do
		if self:IsBankBag(fromBagId) then
			local numSlots = GetContainerNumSlots(fromBagId)
			for fromSlotId = 1, numSlots, 1 do
				local itemLink = GetContainerItemLink(fromBagId, fromSlotId)
				if itemLink then
					if self:IsMovable(fromBagId, fromSlotId) then
						result = self:BankItemMove2Bags(fromBagId, fromSlotId)
						if result ~= true then
							self:Print(result)
							return
						end
					end
				end
			end
		end
	end
    self:Print(L["Done."])
end

function GBM:BankToBagsUnique()
    self:Print(L["Have patience, it takes quite a while to move ALOT of items."])
    local seen = {}
	for i, fromBagId in ipairs(bankSlots) do
		if self:IsBankBag(fromBagId) then
			local numSlots = GetContainerNumSlots(fromBagId)
			for fromSlotId = 1, numSlots, 1 do
				local itemLink = GetContainerItemLink(fromBagId, fromSlotId)
				if (itemLink and (not self:InBags(itemLink)) and (not seen[self:GetItemName(itemLink)])) then
					if self:IsMovable(fromBagId, fromSlotId) then
                        self:Print(L["Get"].." "..itemLink)
                        seen[self:GetItemName(itemLink)] = true
						result = self:BankItemMove2Bags(fromBagId, fromSlotId)
						if result ~= true then
							self:Print(result)
							return
						end
					end
				end
			end
		end
	end
	self:Print(L["Done."])
end

function GBM:BagItemMove2GuildBank(bag, slot)
	if CursorHasItem() then return false end
	local GBtab, GBslot = self:FindFreeGuildBankSlot()
	if not GBtab then
		return L["Could not find any more space in your Guild Bank."]
	end
	if not slotLocks then slotLocks = {} end
	if not slotLocks[GBtab] then slotLocks[GBTab] = {} end
	slotLocks[GBtab][GBslot] = true
	PickupContainerItem(bag, slot)
	PickupGuildBankItem(GBtab, GBslot)
	return true
end

function GBM:BagItemMove2Bank(bag, slot)
	if CursorHasItem() then return false end
    local toBagId, toSlotId = self:FindFreeBankSlot()
	if toBagId == nil then
		return L["No more bank space."]
	end
	if not slotLocks then slotLocks = {} end
	if not slotLocks[toBagId] then slotLocks[toBagId] = {} end
	slotLocks[toBagId][toSlotId] = true
	PickupContainerItem(bag, slot)
	PickupContainerItem(toBagId, toSlotId)
	return true
end

function GBM:BankItemMove2Bags(bag, slot)
	if CursorHasItem() then return false end
	local toBagId, toSlotId = self:FindFreeBagSlot()
	if toBagId == nil then
		return L["No more bag space."]
	end
	if not slotLocks then slotLocks = {} end
	if not slotLocks[toBagId] then slotLocks[toBagId] = {} end
	slotLocks[toBagId][toSlotId] = true
	PickupContainerItem(bag, slot)
	PickupContainerItem(toBagId, toSlotId)
	return true
end

function GBM:IsNormalBag(bagId)
	if bagId == 0 or bagId == -1 then return true end
	local link = GetInventoryItemLink("player", ContainerIDToInventoryID(bagId))
	if not link then return false end
	local linkId = select(3, link:find("item:(%d+)"))
	if not linkId then return false end
	local bagType = self:GetItemSubtype(linkId)
	if bagType and bagType == L["Bag"] then return true end
	return false
end

function GBM:IsBankBag(bagId)
	if bagId == -1 then return true end
	if bagId > 11 or (bagId < 5 and bagId ~= -1) then return false end
	local link = GetInventoryItemLink("player", ContainerIDToInventoryID(bagId))
	if not link then return false end
	local linkId = select(3, link:find("item:(%d+)"))
	if not linkId then return false end
	return true
end

function GBM:IsMovable(bag, slot)
	GL:SetBagItem(bag, slot)
	bound = GL:Find(ITEM_SOULBOUND, 2, 2)
	quest = GL:Find(ITEM_BIND_QUEST, 2, 2)
	if bound or quest then return false end
	return true
end

function GBM:IsGuildBankAvailable()
	return guildBankAvailable
end

function GBM:IsBankAvailable()
	return bankAvailable
end

function GBM:InBags(itemLink)
    if itemLink == nil then self:Print("o_O") end
    local name = self:GetItemName(itemLink)
    for theBag = NUM_BAG_FRAMES, 0, -1 do
		if self:IsNormalBag(theBag) then
			local numSlot = GetContainerNumSlots(theBag)
			for theSlot = 1, numSlot, 1 do
                local bagItemLink = GetContainerItemLink(theBag, theSlot)
                if bagItemLink then
                    local name2 = self:GetItemName(bagItemLink)
                    if name == name2 then return true end
                end
			end
		end
	end
	return false
end

function GBM:FindFreeBagSlot()
	for theBag = NUM_BAG_FRAMES, 0, -1 do
		if self:IsNormalBag(theBag) then
			if not slotLocks then slotLocks = {} end
			if not slotLocks[theBag] then slotLocks[theBag] = {} end
			local numSlot = GetContainerNumSlots(theBag)
			for theSlot = 1, numSlot, 1 do
				if not slotLocks[theBag][theSlot] then
					local texture = GetContainerItemInfo(theBag, theSlot)
					if not texture then
						return theBag, theSlot
					end
				end
			end
		end
	end
	return nil
end

function GBM:FindFreeBankSlot()
	for i, theBag in ipairs(bankSlots) do
		if self:IsBankBag(theBag) then
			if not slotLocks then slotLocks = {} end
			if not slotLocks[theBag] then slotLocks[theBag] = {} end
			local numSlot = GetContainerNumSlots(theBag)
			for theSlot = 1, numSlot, 1 do
				if not slotLocks[theBag][theSlot] then
					local texture = GetContainerItemInfo(theBag, theSlot)
					if not texture then
						return theBag, theSlot
					end
				end
			end
		end
	end
	return nil
end

function GBM:FindFreeGuildBankSlot()
	if not self:IsGuildBankAvailable() then return nil end
	for tab=1, GetNumGuildBankTabs(), 1 do
		local _, _, _, canDeposit = GetGuildBankTabInfo(tab);
		if canDeposit then
			if not slotLocks then slotLocks = {} end
			if not slotLocks[tab] then slotLocks[tab] = {} end
			for slot=1, 98, 1 do
				if not slotLocks[tab][slot] then
					local info = GetGuildBankItemInfo(tab, slot)
					if not info then
						return tab, slot
					end
				end
			end
		end
	end
	return nil
end

function GBM:GetItemSubtype(link)
	return select(7, GetItemInfo(link))
end

function GBM:GetItemName(link)
	return select(1, GetItemInfo(link))
end
