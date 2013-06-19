require 'spec_helper'
require 'ffi'

module Assemble extend FFI::Library
  ffi_lib File.join(File.expand_path('bin'), 'assemble')

  #### assemble.c ############################################

  #### utilites/functionAssemble.c #############################
  attach_function :assembleDataProcessing, [:uint32, :pointer], :uint32

  #### standard C libraries #################################
  attach_function :malloc, [:size_t], :pointer
  attach_function :calloc, [:size_t], :pointer

  def self.pointer_from_string(str)
    ptr = Assemble.malloc str.size
    ptr.write_string str
  end

end