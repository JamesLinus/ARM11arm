#!/usr/bin/env ruby
require 'spec_helper'
require 'ffi'
require 'base64'

module Utilities
  extend FFI::Library
  ffi_lib File.join(File.expand_path('bin'), 'emulate')

  # char* loadBinaryFile(char* path)
  attach_function :loadBinaryFile, [:string], :pointer
  attach_function :openFile, [:string], :pointer
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
      ruby_hex = ruby_bin.read_bytes(8).unpack('H*')
      c_hex = res.read_bytes(8).unpack('H*')
      c_hex.should eq ruby_hex
    end
    it 'A does not match B' do
      res = Utilities.loadBinaryFile path + 'B'
      res.get_bytes(0, s).should_not eq(ruby_bin.read_bytes(s))
    end

  end

  context 'with invalid files' do
    it 'detects size above 2^16 bytes' do
      file = Utilities.openFile path + 'C_large'
      size = Utilities.getSize file
      # invalid file, should exceed limit
      size.should_not be < 65536
    end

    it 'exits for nonexistant file' do
      file = Utilities.openFile path + 'Ghost'
      # invalid should point to it's initialized value- 0
      file.address.should eq(0)
    end

  end

end
