-- https://github.com/sharpobject/panel-attack/blob/master/queue.lua

local Queue = torch.class('Queue')

function Queue:__init()
   self.first = 0
   self.last = -1
   self.q = {}
end

function Queue:push(value)
   local last = self.last + 1
   self.last = last
   self.q[last] = value
end

function Queue:empty()
   return self.first > self.last
end

function Queue:pop()
   if self:empty() then
      return nil
   end
   local first = self.first
   local ret = self.q[first]
   self.q[first] = nil
   if self.first == self.last then
      self.first = 0
      self.last = -1
   else
      self.first = first + 1
   end
   return ret
end

function Queue:len()
   return self.last - self.first + 1
end

function Queue:clear()
   for i=self.first,self.last do
      self.q[i] = nil
   end
   self.first = 0
   self.last = -1
end