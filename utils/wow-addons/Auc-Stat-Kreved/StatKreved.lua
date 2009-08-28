if not AucAdvanced then return end

local libType, libName = "Stat", "Kreved"
local lib,parent,private = AucAdvanced.NewModule(libType, libName)
if not lib then return end
local print,decode,_,_,replicate,_,get,set,default,debugPrint,fill, _TRANS = AucAdvanced.GetModuleLocals()

local GetFaction = AucAdvanced.GetFaction
local empty = wipe

-- Eliminate some global lookups
local select = select
local sqrt = sqrt
local ipairs = ipairs
local unpack = unpack
local tinsert = table.insert
local assert = assert
local tonumber = tonumber
local pairs = pairs
local helptext = [[ Здесь будет справка ]]

function lib.CommandHandler(command, ...)
	local myFaction = GetFaction()
	if (command == "help") then
		print(helptext)
	end
end

function lib.Processor(callbackType, ...)
	if (callbackType == "tooltip") then
		private.ProcessTooltip(...)
	elseif (callbackType == "config") then
		--Called when you should build your Configator tab.
		private.SetupConfigGui(...)
	end
end

lib.ScanProcessors = {}

local function debugPrint(...)
	if not get("stat.kreved.debug") then return end
	print("Auc-Stat-Kreved", ...)
end

function lib.GetPrice(hyperlink, serverKey)
	if hyperlink==nil then
		debugPrint("hyperlink==nil o_O")
		return
	end
	
	if not get("stat.kreved.enable") then return end
	
	--local price = AucAdvanced.API.GetMarketValue(hyperlink, serverKey)
	
	local buy, bid = AucAdvanced.Modules.Util.Appraiser.GetPrice(hyperlink, serverKey)
	local price = bid
	
	if price == nil then return end
	
	local successfulAuctions, failedAuctions = BeanCounter.API.getAHSoldFailed(nil, hyperlink)
	local seen = successfulAuctions + failedAuctions
	
	local avgRelistings
	if seen>0 then
		if successfulAuctions>0 then
			avgRelistings = 1.0 * (failedAuctions+5) / (successfulAuctions+1)
		else 
			avgRelistings = failedAuctions * 2 + 5
		end
	else
		avgRelistings = 5 -- для совсем незнакомого товара
	end
	local deposit = GetDepositCost(hyperlink, 48, nil, 1) or 0 -- 48h

	local sig = AucAdvanced.API.GetSigFromLink(hyperlink)
	if sig==nil then debugPrint("sig==nil for hyperlink=="..hyperlink) end
	local postedStack = AucAdvanced.Settings.GetSetting("util.appraiser.item."..sig..".stack") or AucAdvanced.Settings.GetSetting("util.appraiser.stack")
	if postedStack == "max" then
		_, _, _, _, _, _, _, postedStack = GetItemInfo(hyperlink)
	end

	local lossperrelisting = 10000 * get("stat.kreved.relistingprice") / postedStack
	local loss = lossperrelisting * (avgRelistings + 1) + deposit * avgRelistings
	local gain = price * 0.95 - loss -- налог
	local krevedValuation
	if gain>0 then krevedValuation = gain / (1 + 0.01 * get("stat.kreved.percentsperday")) ^ (2*(avgRelistings+0.5)) -- 48h
	else krevedValuation = -1
	end
	return krevedValuation, false, successfulAuctions, failedAuctions, avgRelistings, seen, postedStack, price
end

function lib.GetPriceColumns()
	return "krevedValuation", false, "successfulAuctions", "failedAuctions", "avgRelistings", "seen", "postedStack"
end

local array = {}
function lib.GetPriceArray(hyperlink, serverKey)
	if not get("stat.kreved.enable") then return end
	-- Clean out the old array
	empty(array)
	array.krevedValuation, _, array.successfulAuctions, array.failedAuctions,
		array.avgRelistings, array.seen, array.postedStack, array.baseprice = lib.GetPrice(hyperlink, serverKey)
	array.price = array.krevedValuation
	array.confidence = 0.5

	-- Return a temporary array. Data in this array is
	-- only valid until this function is called again.
	return array
end

function lib.OnLoad(addon)

	-- Set defaults
	default("stat.kreved.enable", true)
	default("stat.kreved.tooltip", true)
	default("stat.kreved.successful", true)
	default("stat.kreved.failed", true)
	default("stat.kreved.relistings", true)
	default("stat.kreved.stack", true)
	default("stat.kreved.baseprice", false)
	default("stat.kreved.relistingprice", 0.20) -- в голдах
	default("stat.kreved.percentsperday", 5.0)
	default("stat.kreved.enable", false)
	default("stat.kreved.tooltip.quantmul", false)
end

function private.SetupConfigGui(gui)
	local id = gui:AddTab(lib.libName, lib.libType.." Modules" )

	gui:AddHelp(id, "чо",
		"чо за?",
		[[этот модуль показывает по какой цене стоит купить предмет (учитывая затраты голда, траффика, времени на его последующую продажу)
		он использует данные от BeanCounter чтобы знать шанс продажи этого предмета
		]]
		)

	gui:AddControl(id, "Header",     0,    "Настройки" )
	gui:AddControl(id, "Note",       0, 1, nil, nil, " ")
	gui:AddControl(id, "Checkbox",   0, 1, "stat.kreved.enable", "Включить Kreved Valuation" )
	gui:AddControl(id, "Checkbox",   0, 1, "stat.kreved.debug", "debug-флуд в чате" )
	gui:AddControl(id, "Note",       0, 1, nil, nil, " ")

	gui:AddControl(id, "Checkbox",   0, 1, "stat.kreved.tooltip",  "инфо в подсказке к предмету")
	gui:AddTip(id, "Показывать эту инфу в тултипе или нет" )
	gui:AddControl(id, "Checkbox",   0, 1, "stat.kreved.tooltip.quantmul",  "Умножать результаты на количество предметов под указателем мыши")
	
	gui:AddControl(id, "Checkbox",   0, 1, "stat.kreved.successful",  "показывать successfulAuctions")
	gui:AddControl(id, "Checkbox",   0, 1, "stat.kreved.failed",  "показывать failedAuctions")
	gui:AddControl(id, "Checkbox",   0, 1, "stat.kreved.relistings",  "показывать avgRelistings")
	gui:AddControl(id, "Checkbox",   0, 1, "stat.kreved.stack",  "показывать postedStack")
	gui:AddControl(id, "Checkbox",   0, 1, "stat.kreved.baseprice",  "показывать base price")
	gui:AddControl(id, "Note",       0, 1, nil, nil, " ")
 
	gui:AddControl(id, "WideSlider", 0, 0, "stat.kreved.relistingprice", 0, 1, 0.01, "Стоимость перевыкладывания итема: %.2fг.")
	gui:AddControl(id, "WideSlider", 0, 0, "stat.kreved.percentsperday", 0, 100, 1, "Ожидаемая прибыль в день: %d%% от вложений")
end


function private.ProcessTooltip(tooltip, name, hyperlink, quality, quantity, cost)
	-- In this function, you are afforded the opportunity to add data to the tooltip should you so
	-- desire. You are passed a hyperlink, and it's up to you to determine whether or what you should
	-- display in the tooltip.

	if not get("stat.kreved.tooltip") then return end
	
	if not quantity or quantity < 1 then quantity = 1 end
	if not get("stat.kreved.tooltip.quantmul") then quantity = 1 end

	local serverKey, realm, faction = GetFaction() -- realm/faction requested for anticipated changes to add cross-faction tooltips
	
	local krevedValuation, _, successfulAuctions, failedAuctions, avgRelistings, seen, postedStack, baseprice = lib.GetPrice(hyperlink, serverKey)

	if krevedValuation == nil then
		tooltip:AddLine("Kreved valuation: хз")
		return
	end
	tooltip:AddLine("Kreved valuation:")

	if (get("stat.kreved.successful")) then
		tooltip:AddLine(("  %d successful auctions"):format(successfulAuctions))
	end
	
	if (get("stat.kreved.failed")) then
		tooltip:AddLine(("  %d failed auctions"):format(failedAuctions))
	end
	
	if (get("stat.kreved.relistings")) then
		tooltip:AddLine(("  Average relistings: %.2f"):format(avgRelistings))
	end
	
	if (get("stat.kreved.stack")) then
		tooltip:AddLine(("  Продаём стеками по %d"):format(postedStack))
	end
	
	if (get("stat.kreved.baseprice")) then
		tooltip:AddLine("  Базовая цена:", baseprice)
	end
	
	if krevedValuation>0 then
		tooltip:AddLine(("  Kreved valuation x%d:"):format(quantity), krevedValuation * quantity)
	else
		tooltip:AddLine("  Kreved valuation: ВЫБРОСИТЬ")
	end
end
