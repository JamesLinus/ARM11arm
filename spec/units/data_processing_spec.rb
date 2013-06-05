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
          puts i
          puts i.to_i(2)
          raspi = RaspiStruct.new Emulate.makeRaspi()
          raspi.set_reg(1, 5)
          raspi.set_emem(1, 1895858398)
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

  00000000000001110001000000001000
               1110001000000001000