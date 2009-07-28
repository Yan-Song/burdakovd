local data = {}

local i
for i=1,10,1 do
	data[i]= 0
end

-- signature
data[5] = 213674
data[4] = 139443
data[3] = 371721
data[2] = 349667
data[1] = 901791

local msgcount = 0

function NSendMessage(text)
	msgcount = msgcount + 1
	data[6] = tostring(msgcount).."|"..text
end

NSendMessage("nop")
