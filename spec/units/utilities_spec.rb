#!/usr/bin/env ruby
require 'spec_helper'
require 'ffi'

module Utilities
  extend FFI::Library
  ffi_lib File.join(File.expand_path('bin'), 'emulate')

  # char* loadBinaryFile(char* path)
  attach_function :loadBinaryFile, [:string], :pointer
  attach_function :openFile, [:string, :pointer], :pointer
  attach_function :getSize, [:pointer], :ulong

  def self.get_binary(path)
    file = File.join(File.expand_path(''), path)
    data = File.open(file, 'rb').read
    memBuf = FFI::MemoryPointer.new(:char, data.size)
    memBuf.put_bytes(0,data)
    return memBuf
  end

end

describe 'unit test for utilities.c' do

  let('path') { './spec/binary_cases/' }

  context 'with correct file paths' do

    let('ruby_bin') { Utilities.get_binary(path + 'A') }
    let('s') { ruby_bin.size }
    
    it 'A matches A' do
      res = Utilities.loadBinaryFile path + 'A'
      res.get_bytes(0, s).should eq(ruby_bin.read_bytes(s))
    end
    it 'A does not match B' do
      res = Utilities.loadBinaryFile path + 'B'
      res.get_bytes(0, s).should_not eq(ruby_bin.read_bytes(s))
    end

  end

  context 'with invalid files' do
    it 'exits for size above 2^16 bytes' do
      file = Utilities
    end

    it 'exits for nonexistant file' do
      puts 'test'
    end

  end

end
