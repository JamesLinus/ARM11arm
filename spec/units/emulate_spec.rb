#!/usr/bin/env ruby
require 'emulate_helper'

describe 'unit test for emulate.c' do

  it 'does not crash' do
    path = Emulate.pointer_from_string './spec/official_tests/add01'
    Emulate.main(0, path)
  end

  describe 'initialization' do
    context 'file exists' do
      it 'initializes both state structs'
      it 'zeros all struct elements'
      it 'loads file at path into state memory'
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