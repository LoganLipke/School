function init(args)
	local needs = {}
	needs["payload"] = tostring(true)
	return needs
end

function match(args)
	-- Find URLs in DNS query payload
	a = tostring(args["payload"])
	url = a:match("[%w-]+[^.][%w-]+")
--	print(a)
	if url ~= nil then
		s,e = a:find(url)
		--last = a:sub(e+1, e+4)
		--url = url..last
		ent = calcEntropy(url)
		max = maxEntropy(url)
		if ent > 3.0 and (ent / max) * 100 > 85.0 then
--			print(url, ent, max, ent/max * 100)
			return 1
		end
	else
		return 0
	end
end

function calcEntropy(url)
	-- Uses Shannon's entropy to calculate entropy of a URL
	entVal = 0
	urlLen = #url
	count = {}
	
	for i=1, urlLen do
		if url:sub(i,i) ~= '.' then
			if count[url:sub(i,i)] ~= nil then
				count[url:sub(i,i)] = count[url:sub(i,i)] + 1
			else
				count[url:sub(i,i)] = 1
			end
		end
	end
	
	for k,v in pairs(count) do
		p_i = v  / (urlLen + .0)
		ent_i = p_i * math.log(p_i, 2)
		entVal = entVal + ent_i
	end
	return -1 * entVal
end

function maxEntropy(url)
	-- Finds the max entropy of a string with the length of url
	count = 0
	for i = 1, #url do
		if url:sub(i,i) ~= '.' then
			count = count + 1
		end	
	end
	return math.log(count, 2)
end
