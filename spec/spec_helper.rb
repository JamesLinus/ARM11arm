require 'make_preflight'
require 'ffi'

class Raspi < FFI::Struct
  layout :r, :pointer,
    :sp,   :ulong,
    :lr,   :ulong,
    :pc,   :ulong,
    :cpsr, :ulong,
    :em,   :pointer,
    :dm,   :pointer
end

