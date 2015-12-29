--  Layer for metric 
-- Author: Minwei Feng (mfeng@us.ibm.com)

local DivideConstant, parent = torch.class('nn.DivideConstant', 'nn.Module')

function DivideConstant:__init(constant_scalar)
  parent.__init(self)
  assert(type(constant_scalar) == 'number', 'input is not scalar!')
  self.constant_scalar = constant_scalar
  self.numerator = constant_scalar 
end

function DivideConstant:updateOutput(input)
  self.output = self.output or input.new()
  self.output:resizeAs(input):fill(self.numerator)
  self.output:cdiv(input)
  return self.output
end

function DivideConstant:updateGradInput(input, gradOutput)
  self.gradInput = self.gradInput or input.new()
  self.gradInput:resizeAs(input)
  self.gradInput:copy(gradOutput):cdiv(input):cdiv(input):mul(-self.numerator)
  return self.gradInput
end
