#!/usr/bin/env ruby
require 'assemble_helper'

describe 'unit test for functionAssemble.c' do

  let(:assembly_src)   { './spec/assembly_cases/' }

  context 'data processing' do

    it 'and' do
      Assemble.main 0, assembly_src + 'add01.s'
    end

  end

end