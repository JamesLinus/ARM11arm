describe 'data processing tests' do
  context 'COND as 1110 (always)' do
    context 'as immediate' do
      it 'AND' do
        I = '1'
        S = '0'
        Rn = '0001'
        Rd = '0002'
        Operand2 = '0000' + '11011110'
        i = '1110' + '00' + I + '0000' + S + Rn + Rd + Operand2
        raspi = RaspiStruct.new Emulate.makeRaspi()
        Emulate.loadBinaryFile 'spec/official_tests/add01', raspi[:em] 
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
