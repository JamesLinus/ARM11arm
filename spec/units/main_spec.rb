#!/usr/bin/env ruby
require 'spec_helper'
require 'ffi'

module Emulate
  extend FFI::Library
  ffi_lib File.join(File.expand_path('bin'), 'emulate')
  attach_function :main, [:string], :void
  attach_function :decodeInstruction, [:ulong, :pointer, :ulong], :ulong

end

describe 'unit test for main.c' do
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