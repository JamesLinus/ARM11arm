require 'make_preflight'
require 'ffi'

MEMSIZE = 65536

class RaspiStruct < FFI::Struct
  layout :r, :pointer,
    :sp,   :uint32,
    :lr,   :uint32,
    :pc,   :uint32,
    :cpsr, :uint32,
    :em,   :pointer,
    :dm,   :pointer
    def regs
      regs = FFI::Pointer.new self[:r]
      regs.read_array_of_type(:uint32, :read_uint32, 12)
    end
    def encoded_mem
      em = FFI::Pointer.new self[:em]
      em.read_array_of_type(:uint32, :read_uint32, MEMSIZE)
    end
    def zeroed
      r = self.regs
      em = self.encoded_mem
      sum = (self[:sp] + self[:pc] + self[:cpsr] + self[:lr])
      return false unless sum.zero?
      r.map  { |n| return false unless n.zero? }
      em.map { |n| return false unless n.zero? }
      return true
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