#!/usr/bin/env ruby
require 'ffi'

module Emulate
  extend FFI::Library

  ffi_lib File.absolute_path(
    File.join(File.dirname(__FILE__), '../bin', 'emulate'))

  # char* loadBinaryFile(char* path)
  attach_function :loadBinaryFile, [:string], :string

end

describe 'unit test for utilities.c from emulate' do

  it 'returns contents of binary file' do
    out = FFI::MemoryPointer.new :pointer
    res = Emulate.loadBinaryFile('./cases/A.bin', out)
    puts out.read_string_to_null
  end

end