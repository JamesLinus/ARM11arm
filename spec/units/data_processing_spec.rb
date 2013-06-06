class DataInstr
  def initialize(cond, immd, opcode, set_cond, rn, rd, op2)
    @instr = (cond + '00' + immd + opcode +
      set_cond + rn + rd + op2)
  end
  def set_operand(op)
    @instr = @instr[-12] + op
  end
  def str_instr
    @instr
  end
end

describe 'data processing tests' do

  context 'COND as 1110 (always)' do

    before(:all) do
      @raspi = RaspiStruct.new Emulate.makeRaspi()
      @raspi.set_reg(1, 4)
      @raspi.set_reg(2, 5)
      @a, @b = [[],[]]
      1.times do
        @a << rand(2**31)
        @b << rand(2**31)
      end
    end

    context 'as register' do
      it 'AND' do
        # create instruction to AND contents of mem
        # addr at reg 1 with mem addr at reg 2 and
        # stores the result in register 3
        i = DataInstr.new('1110', '0', '0000',
          '10', '0100', '0101', '00000000' + '0110')
        Emulate.setmem @raspi, i.str_instr, 1 
        @a.zip(@b).each do |a, b|
          @raspi.set_emem(4, a)
          @raspi.set_emem(5, b)
          base = BaseInstrStruct.new Emulate.decodeInstruction @raspi, 1
          # Emulate.printOut @raspi
          Emulate.runFunction base
        end
        # system './spec/test_binary_wrappers/maskTests ' + @raspi.get_emem(0).to_s
      end
      context 'EOR' do
      end
      context 'SUB' do
      end
      context 'RSB' do
      end
      context 'ADD' do
      end
      context 'TST' do
      end
      context 'TEQ' do
      end
      context 'CMP' do
      end
      context 'ORR' do
      end
      context 'MOV' do
      end
    end
    context 'as register' do
    end
  end
end
