require 'image' -- for string.split

-- sleeps for n seconds
function sleep(n)
   os.execute("sleep " .. tonumber(n))
end

-- sleeps for n milliseconds
function millisleep(n)
   os.execute("sleep " .. tonumber(n/1000))
end

-- returns a timestamp string
function tstamp(time)
   if time then t = os.date("*t", time)
   else t=os.date("*t") end
   return string.format('%d%.2d%.2d.%.2d%.2d%.2d', t.year, t.month, t.day, t.hour, t.min, t.sec)
end

function tsize(t)
   local dims = ''
   if t == nil then
      dims = '(no tensor)'
   else
      if #t == 1 then dims = string.format('%d', t[1])
      elseif #t == 2 then dims = string.format('%dx%d', t[1], t[2])
      elseif #t == 3 then dims = string.format('%dx%dx%d', t[1], t[2], t[3])
      elseif #t == 4 then dims = string.format('%dx%dx%dx%d', t[1], t[2], t[3], t[4])
      elseif #t == 5 then dims = string.format('%dx%dx%dx%dx%d', t[1], t[2], t[3], t[4], t[5])
      elseif #t == 6 then dims = string.format('%dx%dx%dx%dx%dx%d', t[1], t[2], t[3], t[4], t[5], t[6])
      else error('not implemented') end
   end
   return dims
end

-- returns a string describing the sizes of tensor t
function tdims(t)
   local dims = ''
   if t == nil then dims = '(no tensor)'
   else dims = tsize(t:size()) end
   return dims
end

-- returns a string with information about a tensor t
function tinfo(t)
   if t == nil then return "(no tensor)" end
   if t.type == nil then return tostring(t) end
   if t:dim() == 0 then return '(empty tensor)' end
   local mean
   if t:type() == 'torch.ByteTensor' then mean = t:float():mean()
   elseif t:type() == 'torch.LongTensor' then mean = t:float():mean()
   else mean = t:mean() end
   return string.format('(%s min: %f mean: %f max: %f type: %s)',
			tdims(t), t:min(), mean, t:max(), t:type())
end

-- TODO
function tdinfo(t)
    if t == nil then return "(no tensor)" end
    for _,w in ipairs(weights) do
       if w:nDimension() == 4 then
         -- conv layer
         if cap_conv > 0 then
            local d = conv_dim -- dimension in which output features reside
            local nfeats = w:size(d)
            for i = 1,nfeats do
               local l2 = w:select(d,i):norm()
               if l2 > cap_conv then
                  w:select(d,i):div(l2):mul(cap_conv)
               end
            end
         end
      elseif w:nDimension() == 2 then
         -- linear layer
         if cap_linear > 0 then
            local d = lin_dim -- dimension in which output features reside
            local nfeats = w:size(d)
            for i = 1,nfeats do
               local l2 = w:select(d,i):norm()
               if l2 > cap_linear then
                  w:select(d,i):div(l2):mul(cap_linear)
               end
            end
         end
      elseif w:nDimension() == 1 then
         -- biases
         if cap_bias > 0 then
            local nbiases = w:size(1)
            for i = 1,nbiases do
               w[i] = math.max(-cap_bias, math.min(cap_bias, w[i]))
            end
         end
      end
   end
end

-- prints a tensor in a flat compact manner
function tflat(t)
   if t == nil then
      io.write("(no tensor)")
   else
      for i = 1,t:size(1) do
	 io.write(t[i] .. ' ')
      end
   end
   io.write('\n')
end

-- narrows a list to size s starting at offset o
function lnarrow(l, s, o)
   local l2 = {}
   local k = 1
   for i = o,o+s do
      l2[k] = l[i]
      k = k + 1
   end
   return l2
end

function conv_size(w, h, kw, kh, sw, sh, feat1, feat2)
   local w1,h1 = (w - (kw - sw)) / sw, (h - (kh - sh)) / sh
   print('convolution\t' .. feat1 .. 'x' .. w .. 'x' .. h .. '\t* ' .. kw .. 'x' .. kh
	 .. ' (stride ' .. sw .. 'x' .. sh .. ')\t-> ' .. feat2 .. 'x' .. w1 .. 'x' .. h1)
   -- check for integers
   if w1%math.floor(w1) ~= 0 or h1%math.floor(h1) ~= 0 then
      print('warning: expected integers in ' .. w1 .. 'x' .. h1)
   end
   return w1,h1
end

function pool_size(w, h, kw, kh, sw, sh)
--   local w1,h1 = math.floor((w - (kw - sw)) / sw), math.floor((h - (kh - sh)) / sh)
   local w1,h1 = (w - (kw - sw)) / sw, (h - (kh - sh)) / sh
   print('pooling   \t' .. w .. 'x' .. h .. '   \t/ ' .. kw .. 'x' .. kh
	 .. ' (stride ' .. sw .. 'x' .. sh .. ')\t-> ' .. w1 .. 'x' .. h1)
   -- check for integers
   if w1%math.floor(w1) ~= 0 or h1%math.floor(h1) ~= 0 then
      print('warning: expected integers in ' .. w1 .. 'x' .. h1)
   end
   return w1,h1
end

function pad_size(w, h, pw, ph)
   local w1,h1 = w + pw * 2, h + ph * 2
   print('padding   \t' .. w .. 'x' .. h .. '      \t* ' .. pw .. 'x' .. ph .. 'x' .. pw .. 'x' .. ph
	 .. '         \t-> ' ..  w1 .. 'x' .. h1)
   return w1,h1
end

-- counts number of elements in a list
function count_list(l)
   local n = 0
   for k,v in pairs(l) do n = n + 1 end
   return n
end

-- returns the sorted keys of a table
function sorted_keys(t)
   local sorted = {}
   for k,v in pairs(t) do table.insert(sorted, k) end
   table.sort(sorted)
   return sorted
end

-- accumulate table t2 into table t1
function table_acc(t1, t2)
   for k,v in pairs(t2) do
      if t1[k] and type(t1[k]) == 'number' then
	 t1[k] = t1[k] + v
      else
	 t1[k] = v
      end
   end
end

-- returns a string describing a table with numerical values multiplied by factor
-- and formatted using format
function table_string(tab, factor, format)
   local keys = sorted_keys(tab)
   local s = ''
   for i = 1,#keys do
      local k = keys[i]
      local p = tab[k]
      if p then
	 if type(p) == 'table' then
	    s = s .. ' ' .. k .. ' {' .. table_string(p, factor, format) .. ' }'
	 else
	    s = s .. string.format(format, k, p * factor)
	 end
      end
   end
   return s
end

-- clone a table and its tensors with type type
function clone_table(table, type, target)
   if not table then error('trying to clone an nil table') end
   local default = torch.getdefaulttensortype()
   if type then torch.setdefaulttensortype(type) end
   if not target then target = {} end
   -- find all tensors and convert them
   for key,param in pairs(table) do
      if torch.typename(param) and torch.typename(param):find('torch%..+Tensor') then
	 target[key] = torch.Tensor(param:size())
	 if param:dim() > 0 then target[key]:copy(param) end
      elseif torch.typename(param) == 'table' then
	 target[key] = clone_table(param, type, target)
      else -- add non-tensor params
	 target[key] = param
      end
   end
   torch.setdefaulttensortype(default)
   return target
end

function clone_module(module, type, exclude)
   local default = torch.getdefaulttensortype()
   torch.setdefaulttensortype(type)
   local module_class = torch.getconstructortable(torch.typename(module))
   local clone = nn.Module() --module_class()
   -- find all tensors and convert them
   for key,param in pairs(module) do
      if torch.typename(param) and torch.typename(param):find('torch%..+Tensor') then
	 local x = false
	 -- check if excluded
	 if exclude then
	    for i=1,#exclude do if exclude[i] == key then x = true end end
	 end
	 if not x then
	    clone[key] = torch.Tensor(param:size())
	    if param:dim() > 0 then clone[key]:copy(param) end
	 end
      else -- add non-tensor params
	 clone[key] = param
      end
   end
   -- find submodules in classic containers 'modules'
   if module.modules then
      clone.modules = {}
      for i,m in ipairs(module.modules) do
	 clone.modules[i] = clone_module(m, type, exclude)
      end
   end
   torch.setdefaulttensortype(default)
   return clone
end

function clone_object(o)
   local class_name = torch.typename(o)
   local object_class = torch.getconstructortable(class_name)
   local c = object_class()
   clone_table(o, nil, c)
   return c
end
