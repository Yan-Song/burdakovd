--[[
	Auctioneer Advanced - Custom filter module

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


local lib, parent, private = AucAdvanced.Modules.Util.SearchUI.NewFilter("CustomFilter")
if not lib then return end
local get,set,default,Const = AucAdvanced.Modules.Util.SearchUI.GetSearchLocals()
lib.tabname = "Custom Filter"

private.items = {}
--lib.API = {}

default("filter.custom.enabled", false)

-- This function is automatically called when we need to create our search parameters
function lib:MakeGuiConfig(gui)
	-- Get our tab and populate it with our controls
	local id = gui:AddTab(lib.tabname, "Filters")
	gui:MakeScrollable(id)
    gui:AddHelp(id, "Инфо",
		"Инфо",
		"Этот фильтр отбрасывает итемы, для которых:\
        sold+purchased<10 - чтобы быть уверенным, что мы знаем всё об этом предмете\
		а также если market >= 2*simple или market*simple==0")

	gui:AddControl(id, "Header",     0,      "Custom(Kreved) Filter Criteria")
	
	gui:AddControl(id, "Checkbox",    0, 1,  "filter.custom.enabled", "Enable custom filter")
	
	gui:AddControl(id, "Subhead",     .5, "Filter for:")
	for name, searcher in pairs(AucAdvanced.Modules.Util.SearchUI.Searchers) do
		if searcher and searcher.Search then
			gui:AddControl(id, "Checkbox", 0.5, 1, "filter.custom.searchers."..name, name)
			gui:AddTip(id, "Use custom filter when searching with "..name)
			default("filter.custom.searchers."..name, false)
		end
	end
end

--lib.Filter(item, searcher)
--This function will return true if the item is to be filtered
function lib.Filter(item, searcher)

	if not get("filter.custom.enabled") or not searcher
        or not get("filter.custom.searchers."..searcher) then
            return
	end
    
    local link = item[Const.LINK]
    
    local sold
	if AucAdvanced.Modules.Stat.Sales.GetPriceArray(link) then
        sold = AucAdvanced.Modules.Stat.Sales.GetPriceArray(link).soldqty
    else
        sold = 0
    end
    
    local purchased
    if AucAdvanced.Modules.Stat.Purchased.GetPriceArray(link) then
        purchased = AucAdvanced.Modules.Stat.Purchased.GetPriceArray(link).seen
    else
        purchased = 0
    end
    
	local sig = AucAdvanced.API.GetSigFromLink(link)
    local postedStack = AucAdvanced.Settings.GetSetting("util.appraiser.item."..sig..".stack") or AucAdvanced.Settings.GetSetting("util.appraiser.stack")
	if postedStack == "max" then
		_, _, _, _, _, _, _, postedStack = GetItemInfo(link)
	end
	
	postedStack = postedStack or 1
	
	local simple = AucAdvanced.Modules.Stat.Simple.GetPriceArray(link).price or 0
	local market = AucAdvanced.API.GetMarketValue(link) or 0
	
	if market*simple == 0 then return true end

	if market >= 2*simple then
		return true
	end
	
    if (sold+purchased<10) then return true end
    
    
    
    return false
end
