local data = {}

local i
for i=1, 100, 1 do
    data[i] = 0
end

local initialized = false;
local frames = 0;

-- signature
-- некие случайные числа, известные также внешнему модулю
local initialize = function()
    data[5] = 56512;
    data[4] = 72134;
    data[3] = 61231;
    data[2] = 53121;
    data[1] = 71246;
    initialized = true;
end

-- запускаем инициализацию спустя 50 кадров
local frame = CreateFrame("Frame")
frame:SetScript("OnUpdate", function(...) frames = frames + 1; if ((not initialized) and (frames > 50)) then initialize() end end)
