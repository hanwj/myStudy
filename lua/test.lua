
local moduleName = ...

for i=1,select('#',...) do
	print (select(i,...))
end

local M = {}
_G[moduleName] = M
complex = M

function M.new(i)
	print("init complex "..tostring(i))
end

function M.add()

end

function M.sub()

end

return complex	