#!/usr/bin/env ruby
require 'emulate_helper'

describe 'unit test for emulate.c' do
  let(:add01) { './spec/official_tests/add01' }
  let(:memsize) { 65536 }
  let(:raspi_ptr) { Emulate.makeRaspi }
  let(:mem_buff) { FFI::MemoryPointer.new(:uint32, 65536) }

  it 'does not crash for normal file' do
    Emulate.main(0, add01)
  end

  describe 'initialization' do

    context 'file exists' do
      it 'zeros all struct elements' do
        raspi = RaspiRuby.new raspi_ptr
        raspi.zeroed.should eq(true)
      end
      it 'loads file at path into state memory' do
        struct = RaspiStruct.new raspi_ptr
        Emulate.loadBinaryFile add01, struct[:em]
        ruby_bin = Emulate.get_binary(add01)
        s, c_bin = [ruby_bin.size, struct[:em]]
        # the bytes from the first section of the memory
        # should equal the ruby bytes of the whole file
        c_bin.read_bytes(s).should eq(ruby_bin.read_bytes(s))
        elems = c_bin
          .read_array_of_type(:uint32, :read_uint32, memsize / 2)
        total = elems[s..memsize].reduce { |a, b| a + b }
        # all bytes after the loaded mem should be 0
        total.should eq(0)
      end
    end
    context 'file does not exist' do
      it 'detects incorrect nonexistant files' do
        res = Emulate.fileExists('./bogus')
        res.should eq(1)
        res = Emulate.fileExists('./spec/binary_cases/A')
        res.should eq(0)
      end
    end
  end

  describe 'decoding instruction' do

    describe 'masking checks' do

      it 'verifies data opcode'
    #    Emulate.isMul '3ffffff'.to_i(16)
    #    250.times do
    #      test = ((rand(16)*2**28) + rand('3ffffff'.to_i(16)))
    #      if res != 1
    #        puts (sprintf "%320b", mask)
    #        puts (sprintf "%320b", test)
    #      end
    #      res.should eq(1)
    #    end
    #  end

      it 'verifies multiply opcode'

      it 'verifies single data transfer opcode'

      it 'verifies branch opcode'

    end

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