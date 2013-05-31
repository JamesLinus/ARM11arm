#!/usr/bin/env ruby
require 'spec_helper'
require 'ffi'

module Arm
  extend FFI::Library
  ffi_lib File.join(File.expand_path('bin'), 'emulate')

end

describe 'unit test for arm.c' do

end
