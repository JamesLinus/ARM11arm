#!/usr/bin/env ruby
require 'emulate_helper'

describe 'official test suite' do

  let(:raspi) { RaspiStruct.new Emulate.makeRaspi }
  let(:bin)   { './spec/binary_cases/'    }
  let(:exp)   { './spec/binary_outcomes/' }

  context 'addition' do
    it 'add01'
    it 'add02'
    it 'add03'
    it 'add04'
  end

  context 'and' do
    it 'and01'
    it 'and02'
  end

  context 'branch' do
    it 'b01'
    it 'beq01'
    it 'beq02'
    it 'bne01'
    it 'bne02'
  end

  context 'exclusive or' do
    it 'eor01'
    it 'eor02'
  end

  context 'factorial' do
    it 'factorial'
  end

  context 'gpio' do
    it 'gpio_0'
    it 'gpio_1'
    it 'gpio_2'
  end

  context 'load register' do
    it 'ldr01'
    it 'ldr02'
    it 'ldr03'
    it 'ldr05'
    it 'ldr06'
    it 'ldr07'
    it 'ldr08'
    it 'ldr09'
    it 'ldr14'
  end

  context 'loops' do
    it 'loop01'
    it 'loop03'
  end

  context 'left shift' do
    it 'lsl01'
    it 'lsl02'
  end

  context 'move assignment' do
    it 'mov01'
    it 'mov02'
    it 'mov03'
    it 'mov04'
    it 'mov05'
    it 'mov06'
    it 'mov07'
  end

  context 'multiplication' do
    it 'mul01'
  end

  context 'or' do
    it 'or01'
    it 'or02'
  end

  context 'right subtract' do
    it 'rsb01'
    it 'rsb02'
    it 'rsb03'
  end

  context 'store register' do
    it 'str01'
    it 'str02'
    it 'str03'
  end

  context 'substract' do
    it 'sub01'
    it 'sub02'
    it 'sub03'
  end

  context 'test bits' do
    it 'tst01'
    it 'tst02'
    it 'tst03'
    it 'tst04'
  end

end
