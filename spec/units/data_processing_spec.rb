describe 'data processing tests' do

  context 'COND as 1110 (always)' do

    def reg_set_rand(raspi, a, b)
      raspi.set_reg(0,a)
      raspi.set_reg(1,b)
    end

    def prime(opcode)
      i = DataInstr.new opcode
      Emulate.setmem @raspi, i.instr_val, 1 
    end

    def decode_and_run
      Emulate.runFunction \
        BaseInstrStruct.new \
          Emulate.decodeInstruction @raspi, 1
    end

    def result
      @raspi.get_reg 2
    end

    before(:all) do
      @raspi = RaspiStruct.new Emulate.makeRaspi()
      @a, @b = [[],[]]
      5000.times do
        @a << rand(2**31)
        @b << rand(2**31)
      end
    end

    context 'as register' do

      it 'AND' do
        # Find R1 (bitwise)AND R2
        prime '0000'
        @a.zip(@b).each do |a, b|
          reg_set_rand @raspi, a, b
          decode_and_run
          result.should eq(a & b)
        end
      end

      it 'EOR' do
        # Find R1 (bitwise)EOR R2
        prime '0001'
        @a.zip(@b).each do |a, b|
          reg_set_rand @raspi, a, b
          decode_and_run
          result.should eq(a ^ b)
        end
      end

      it 'SUB' do
        # Find R1 - R2
        prime '0010'
        @a.zip(@b).each do |a, b|
          reg_set_rand @raspi, a, b
          decode_and_run
          result.should eq(a - b)
        end
      end

      it 'RSB' do
        # Find R1 - R2
        prime '0011'
        @a.zip(@b).each do |a, b|
          reg_set_rand @raspi, a, b
          decode_and_run
          result.should eq(b - a)
        end
      end

      it 'ADD' do
        # Find R1 + R2
        prime '0100'
        @a.zip(@b).each do |a, b|
          reg_set_rand @raspi, a, b
          decode_and_run
          res, exp = [ result, (a + b) ]
          if exp > 2**31
            res = res.to_s(2)[1..32].to_i(2)
            exp = -(exp - 2**32)
          end
          res.should eq(exp)
        end
      end

      it 'ORR' do
        # Find R1 OR R2
        prime '1100'
        @a.zip(@b).each do |a, b|
          reg_set_rand @raspi, a, b
          decode_and_run
          result.should eq(a | b)
        end
      end

      it 'MOV' do
        # Result should be op2
        prime '1101'
        @a.zip(@b).each do |a, b|
          reg_set_rand @raspi, a, b
          decode_and_run
          result.should eq(b)
        end
      end

    end
  end
end
