--[[
	Auctioneer Advanced - Kreved Utility module

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


local libType, libName = "Util", "Kreved"

local lib,parent,private = AucAdvanced.NewModule(libType, libName)
if not lib then return end
private.items = {}
lib.API = {}

function private.AutoScan(cmd)
    AucAdvanced.Settings.SetSetting('util.kreved.autoscan',not AucAdvanced.Settings.GetSetting('util.kreved.autoscan'))
    if(AucAdvanced.Settings.GetSetting('util.kreved.autoscan')) then
        print("Автоскан теперь включён")
    else
        print("Автоскан теперь отключён")
    end
end

function private.AutoPurchase(cmd)
    if not(AuctionFrame and AuctionFrame:IsVisible()) then return end --если мы не на аукционе
    if(not AucAdvanced.Settings.GetSetting('util.kreved.autopurchase')) then return end
    if (AucAdvanced.Buy.Private.Prompt:IsVisible()) then
            AucAdvanced.Buy.Private.Prompt.Yes:Click()
    end
end

function private.everySecond()
    if not(AuctionFrame and AuctionFrame:IsVisible()) then return end --если мы не на аукционе
    
    if(AucAdvanced.Settings.GetSetting('util.kreved.autoscan')) then
        if not(AucAdvanced.Scan.IsScanning() or AucAdvanced.Scan.IsPaused()) and (AucAdvanced.Scan.scanStack==nil or #AucAdvanced.Scan.scanStack==0) then
            print("[Auc-Util-Kreved] Перезапускаем скан")
            AucAdvanced.Scan.StartScan("", "", "", nil, nil, nil, nil, nil)
        end
    end
end

local time=0.0

function private.OnUpdate(me,elapsed)
    time = time+elapsed
    if(time>1.0) then
        private:everySecond()
        time = 0.0
    end
end

function lib.OnLoad()
    AucAdvanced.Settings.SetDefault("util.kreved.autoscan", false)
    AucAdvanced.Settings.SetDefault("util.kreved.autopurchase", false)
    
    SLASH_AUTOSCAN1 = "/autoscan";
    SLASH_AUTOSCAN2 = "/ascan";
    SlashCmdList["AUTOSCAN"] = private.AutoScan;
    
    SLASH_AUTOPURCHASE1 = "/autopurchase";
    SLASH_AUTOPURCHASE2 = "/apurchase";
    SlashCmdList["AUTOPURCHASE"] = private.AutoPurchase;
end

function private.HookAH()
    private.button = CreateFrame("Frame", nil, AuctionFrame)
    private.button:SetPoint("TOPLEFT", AuctionFrame, "TOPLEFT", 75, -15)
	private.button:SetWidth(20)
	private.button:SetHeight(20)
    
    private.button:SetScript("OnUpdate", private.OnUpdate)
    
	private.button:SetScript("OnEnter", function()
			GameTooltip:SetOwner(private.button.control, "ANCHOR_TOPRIGHT")
			GameTooltip:SetText("Эту кнопку пришлось добавить из-за особенностей хитровыебанного lua&&blizzard, нажимать на неё не нужно")
		end)
	private.button:SetScript("OnLeave", function()
			GameTooltip:Hide()
		end)
end

function lib.Processor(callbackType, ...)
	if (callbackType == "config") then
		private.SetupConfigGui(...)
    elseif (callbackType == "auctionui") then
        private.HookAH()
	end
end

function private.SetupConfigGui(gui)
	local id = gui:AddTab(lib.libName, lib.libType.." Modules")

	gui:AddHelp(id, "Предполагаемая тактика использования",
		"Предполагаемая тактика использования",
		"Заходим на аукцион, включаем realtime search (ПРЕДВАРИТЕЛЬНО ЕГО НАСТРОИТЬ),\
        включаем галочку, ставим /autopurchase на макрос, его на автокаст и идём спать/в магазин/пить кофе etc.")
    
    gui:AddHelp(id, "Это аддон чтоб на халяву получить голд?","Это аддон чтоб на халяву получить голд?",
		"Никогда ни разу! если не настроите нормально realtime search - ничего не заработаете, только просрёте голд.")
    
    gui:AddHelp(id, "Консольные команды","Консольные команды",
		"/autoscan; /autopurchase")

    gui:AddHelp(id, "Это читерство?","Это читерство?",
		"Я так не считаю, но на всякий случай нигде этот аддон не публикую и не афиширую его использование.\
        Вообще здесь вопрос спорный...")
    
	gui:AddControl(id, "Checkbox", 0, 1, "util.kreved.autoscan", "Автоскан")
	gui:AddTip(id, "Если галочка стоит - скан будет автоматически запускаться всё время (Циклично)")
    
	gui:AddControl(id, "Checkbox", 0, 1, "util.kreved.autopurchase", "Автопокупка" )
	gui:AddTip(id, "Если галочка стоит - то при нажатии /autopurchase на вопрос аукционера типа \
    'ВЫ действительно хотите купить..?' аддон будет отвечать 'YES'.")
    
end
