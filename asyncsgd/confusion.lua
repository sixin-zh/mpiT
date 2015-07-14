confusion = {
}

function confusion.updateValids(c, histogram, size)
   -- scale histogram by actual size
   local h = histogram:clone():div(size/c.nclasses)
   -- scale matrix by class
   local mat = c.mat:clone()
   for t = 1,c.nclasses do
      mat:select(1, t):mul(h[t])
--      print('class ' .. t .. ' samples ' .. histogram[t] .. ' factor ' .. h[t] .. ' sum ' .. c.mat:select(1, t):sum() .. ' actual samples ' .. size/c.nclasses)
   end
   --
   local total = 0
   for t = 1,c.nclasses do
      c.valids[t] = mat[t][t] / mat:select(1,t):sum()
      c.unionvalids[t] = mat[t][t] / (mat:select(1,t):sum()+mat:select(2,t):sum()-mat[t][t])
      total = total + mat[t][t]
   end
   c.totalValid = total / mat:sum()
   c.averageValid = 0
   c.averageUnionValid = 0
   local nvalids = 0
   local nunionvalids = 0
   for t = 1,c.nclasses do
      if not sys.isNaN(c.valids[t]) then
         c.averageValid = c.averageValid + c.valids[t]
         nvalids = nvalids + 1
      end
      if not sys.isNaN(c.valids[t]) and not sys.isNaN(c.unionvalids[t]) then
         c.averageUnionValid = c.averageUnionValid + c.unionvalids[t]
         nunionvalids = nunionvalids + 1
      end
   end
   c.averageValid = c.averageValid / nvalids
   c.averageUnionValid = c.averageUnionValid / nunionvalids
   return mat:sum()
end

-- top 1 confusion
function confusion.addbatch(c, prediction, target, ids)
   local _prediction = prediction:float()
   local _target = target:float()
   local _nbatch = prediction:size(1)
   local _,_bestid = torch.max(_prediction,2)
   _bestid:resize(_nbatch)
   for i = 1,_nbatch do
      if ids == nil or ids[i] > 0 then
	 c.mat[_target[i]][_bestid[i]] = c.mat[_target[i]][_bestid[i]] + 1
      end
   end
end

-- top 5 confusion
function confusion.addbatch5(c, prediction, target, ids)
   confusion.addbatch_top(5, c, prediction, target, ids)
end

-- top n confusion
function confusion.addbatch_top(top, c, prediction, target, ids)
   local _prediction = prediction:float()
   local _target = target:float()
   local _nbatch = prediction:size(1)
   for i = 1,_nbatch do
      if ids == nil or ids[i] > 0 then
	 -- sort answers in descending order
	 local _,indices = torch.sort(_prediction:select(1, i), 1, true)
	 -- loop on top n answers
	 local correct = false
	 for j = 1,top do
	    if indices[j] == _target[i] then correct = true end
	 end
	 -- if not found, set the error to top prediction
	 local bestid = indices[1]
	 if correct then bestid = _target[i] end
	 c.mat[_target[i]][bestid] = c.mat[_target[i]][bestid] + 1
      end
   end
end

-- compute position of correct macro class in ordered results
function confusion.addbatch_macro(data, macro_conf, conf2, prediction, target, ids)
   local top = 1
   local macro_target = target:float()
   data:labels_to_macro(macro_target)
   local _prediction = prediction:float()
   local _target = target:float()
   local _nbatch = prediction:size(1)
   for i = 1,_nbatch do
      if ids == nil or ids[i] > 0 then
	 -- sort answers in descending order
	 local _,indices = torch.sort(_prediction:select(1, i), 1, true)
	 -- turn indices into macro classes
	 local macro_indices = indices:clone()
	 data:labels_to_macro(macro_indices)
	 -- pick first answer with correct macro class
	 local answer = indices[1]
	 local correct = false
	 local k = 1
	 while macro_indices[k] ~= macro_target[i]
	    and k <= macro_indices:size(1) do
	    k = k + 1
	 end
	 if k <= macro_indices:size(1) and macro_indices[k] == macro_target[i] then
	    answer = indices[k]
	 end
	 conf2.mat[_target[i]][answer] = conf2.mat[_target[i]][answer] + 1
	 -- loop on top n answers
	 local tgt = macro_target[i]
	 local macro_correct = false
	 for j = 1,top do
	    if macro_indices[j] == tgt then correct = true end
	 end
	 -- if not found, set the error to top prediction
	 local macro_bestid = macro_indices[1]
	 if macro_correct then macro_bestid = tgt end
	 macro_conf.mat[tgt][macro_bestid] = macro_conf.mat[tgt][macro_bestid] + 1
      end
   end
end

function confusion.print(c, histogram, size, is_balanced, name)
   c:updateValids()
   -- sanity check
   if size ~= c.mat:sum() then
      print('warning: expected same size in confusion matrix: '
	    .. size .. ' and ' .. c.mat:sum())
   end
   local unnormalized_correct = c.totalValid*100
   local normalized_correct = c.averageValid*100
--   print(' + average row correct:\t' .. (c.averageValid*100) .. '%')
--   print(' + average rowUcol correct (VOC measure):\t' .. (c.averageUnionValid*100) .. '%')
   local bname = 'balanced'
   if is_balanced == 0 then bname = 'unbalanced' end
   print(string.format(
	    '(%s data, class-normalized rates) %s\tcorrect %.2f%%\terror %.2f%%\ttotal %d',
	    bname, name, normalized_correct, 100-normalized_correct, size))
   print(string.format(
	    '(%s data,    un-normalized rates) %s\tcorrect %.2f%%\terror %.2f%%\ttotal %d',
	    bname, name, unnormalized_correct, 100-unnormalized_correct, size))
   return normalized_correct
end

function confusion.print_classes(c, names)
   c:updateValids()
   -- loop over confusion rows
   local m = c.mat
   local total_errors = 0
   local total_total = 0
   local total_rates = 0
   local nrates = 0
   for i = 1,m:size(1) do
      local total = m:select(1, i):sum()
      local errors = total - m[i][i]
      local rate = errors / total
      print(string.format('%s\terrors %.2f%% (%d\t/ %d)', names[i], rate*100, errors, total))
      total_errors = total_errors + errors
      total_total = total_total + total
      if not sys.isNaN(rate) then
	 total_rates = total_rates + rate
	 nrates = nrates + 1
      end
   end
end