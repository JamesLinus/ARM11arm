#!/usr/bin/env ruby
require 'spec_helper'
require 'ffi'

module Utilities
  extend FFI::Library
  ffi_lib File.join(File.expand_path('bin'), 'emulate')

  # char* loadBinaryFile(char* path)
  attach_function :loadBinaryFile, [:string], :pointer

  def self.get_binary(path)
    file = File.join(File.expand_path(''), path)
    data = File.open(file, 'rb').read
    memBuf = FFI::MemoryPointer.new(:char, data.size)
    memBuf.put_bytes(0,data)
    return memBuf
  end

end

describe 'unit test for utilities.c' do

  it 'returns contents of binary file' do
    path = './spec/binary_cases/A'
    res = Utilities.loadBinaryFile path
    ruby_bin = Utilities.get_binary(path)
    res.read_string.should eq(ruby_bin.read_string)
  end

end