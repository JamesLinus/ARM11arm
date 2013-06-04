require 'make_preflight'
require 'ffi'

class RaspiStruct < FFI::Struct
  layout :r, [:uint8, 17],
    :sp,   :uint32,
    :lr,   :uint32,
    :pc,   :uint32,
    :cpsr, :uint32,
    :em,   :pointer,
    :dm,   :pointer
  def set_reg(i,v)
    puts self.r
  end
end

class DataProcessingStruct < FFI::Struct
  layout :cond, :uint8,
    :cpsr,      :pointer,
    :function,  :pointer,
    :op1,       :pointer,
    :op2,       :pointer,
    :shift,     :pointer,
    :_op2,      :uint32,
    :_shift,    :uint32,
    :exShift,   :pointer,
    :des,       :pointer
end

class RaspiRuby
  attr_accessor :r, :sp, :lr, :pc, :cpsr, :em

  def initialize(ptr)
    str = RaspiStruct.new ptr
    @sp, @lr, @pc, @cpsr =
      [str[:sp], str[:lr], str[:pc], str[:cpsr]]
    @r = array_from_ptr(str[:r], 12)
    memsize = (str[:dm].address - str[:em].address) / 4
    @r, @em = [
      array_from_ptr(str[:r] , 12),
      array_from_ptr(str[:em], memsize)
    ]
  end

  def array_from_ptr(ptr, size)
    res = FFI::Pointer.new(ptr)
    res.read_array_of_type(:uint32, :read_uint32, size)
  end

  def zeroed
    sum = sp + lr + pc + cpsr
    return false unless sum.zero?
    r.map  { |n| return false unless n.zero? }
    em.map { |n| return false unless n.zero? }
    return true
  end

end