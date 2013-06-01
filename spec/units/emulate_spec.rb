#!/usr/bin/env ruby
require 'spec_helper'
require 'ffi'

module Emulate
  extend FFI::Library
  ffi_lib File.join(File.expand_path('bin'), 'emulate')
  attach_function :main, [:int, :pointer], :void
  attach_function :decodeInstruction, [:ulong, :pointer, :ulong], :ulong
  attach_function :malloc, [:size_t], :pointer

end

describe 'unit test for emulate.c' do

  it 'does not crash' do
    ptr = FFI::MemoryPointer.new(:string, 'spec/official_tests/add01'.size)
    Emulate.main(2, ptr)
  end

  describe 'initialization' do
    context 'file exists' do
      it 'initializes both state structs' do
      end
      it 'zeros all struct elements' do
      end
      it 'loads file at path into state memory' do
      end
    end
    context 'file does not exist' do
    end
  end

  describe 'decoding instruction' do
  end

  describe 'single data transfer tests' do
  end

  describe 'branch tests' do
  end

  describe 'multiply tests' do
  end

  describe 'data processing tests' do
  end

  describe 'memory accessing' do
  end

end