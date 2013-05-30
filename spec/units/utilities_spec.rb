#!/usr/bin/env ruby
require 'spec_helper'
require 'ffi'

module Emulate
  extend FFI::Library
  ffi_lib File.join(File.expand_path('bin'), 'emulate')

  # char* loadBinaryFile(char* path)
  attach_function :loadBinaryFile, [:string], :string

end

describe 'unit test for utilities.c from emulate' do

  it 'returns contents of binary file' do
    res = Emulate.loadBinaryFile('./spec/binary_cases/A')
    puts res
  end

end