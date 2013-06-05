class DataInstr
  def initialize(cond, immd, opcode, set_cond, rn, rd, op2)
    @instr = cond + '00' + immd + opcode +
      set_cond + rn + rd + op2
  end
  def get_instr
    @instr.to_i(2)
  end
end

describe 'data processing tests' do

  let(:raspi) { RaspiStruct.new Emulate.makeRaspi() }

  context 'COND as 1110 (always)' do
    context 'as register' do

      before(:all) do
        @is = []
        150.times do
          DataInstr.new '1110', '1', '0000', '0', ''
        end
      end

      it 'AND' do
        Emulate.loadBinaryFile 'spec/official_tests/add01', raspi[:em] 
        system './spec/test_binary_wrappers/maskTests ' + raspi.get_emem(0).to_s
        Emulate.printOut raspi
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
