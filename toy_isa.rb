# какие команды нужно парсить?
# J
# CBIT
# SUBI
# MOVN
# BEQ
# BEXT
# LDP
# ADD
# LD
# CLS
# RORI
# ST
# XOR
# SYSCALL




class Parser
    INSTRUCTION_SET = { # constant value written in CAPITAL LETTERS (this is a hash table)
        'J'    => 0b010111,
        'CBIT' => 0b111011,
        'SUBI' => 0b001111,
        'MOVN' => 0b000101,
        'BEQ'  => 0b100110,
        'BEXT' => 0b110110,
        'LDP'  => 0b001110,
        'ADD'  => 0b000110,
        'LD'   => 0b100010,
        'CLS'  => 0b101101,
        'RORI' => 0b111111,
        'ST'   => 0b111010,
        'XOR'  => 0b011011,
        'SYSCALL' => 0b000111
    }.freeze # nobody can change me!

    INSTRUCTION_OFFSET = {
        'J'    => 2,
        'CBIT' => 3,
        'SUBI' => 3,
        'MOVN' => 3,
        'BEQ'  => 3,
        'BEXT' => 3,
        'LDP'  => 3,
        'ADD'  => 3,
        'LD'   => 2,
        'CLS'  => 2,
        'RORI' => 3,
        'ST'   => 2,
        'XOR'  => 3,
        'SYSCALL' => 1
    }.freeze # nobody can change me!


    # what's going on here? 1. for all numbers from 0 to 15 we create an array [R{i}, i].
    # then we turn it to hash_table with .to_h and then we make it constant by .freeze
    REGISTERS = (0..15).map {|i| ["R#{i}", i]}.to_h.freeze


    def get_tokens(text)
        # creating flat array of tokens from lines
        # [["XOR", "R1", "R2", "R3"], ["ADD", "R2", "R7", "R9"]] -> ["XOR", "R1", "R2", "R3", "ADD", "R2", "R7", "R9"]
        text.lines.map.flat_map do |line|
            line = line.split(";", 2).first.to_s.strip || line # fuck comments
            next [] if line.empty? # skip empty arrays
            if line.end_with?(":") && line.include?(" ")
                # raising error if wrong label format
                raise "Error: label contains spaces -> #{line}"
            end
            line = line.gsub(/[()]/, " ") # replacing brackets with space symbol
            tokens = line.split.map {|t| t.delete(",").delete("#").delete(" ")} # deleting commas (fuck commas (and #commas))
        end
    end

    def translate_tokens(tokens)
        pc = 0
        (0...tokens.size).each do |i|
            case tokens[i]
            # when "J"
            when "CBIT"
                number = translate_cbit(tokens[i+1..i+INSTRUCTION_OFFSET[tokens[i]]])
                pc += INSTRUCTION_OFFSET[tokens[i]]

            when "SUBI"
                number = translate_subi(tokens[i+1..i+INSTRUCTION_OFFSET[tokens[i]]])
                pc += INSTRUCTION_OFFSET[tokens[i]]

            when "MOVN"
                number = translate_movn(tokens[i+1..i+INSTRUCTION_OFFSET[tokens[i]]])
                pc += INSTRUCTION_OFFSET[tokens[i]]

            when "BEQ"
                number = translate_subi(tokens[i+1..i+INSTRUCTION_OFFSET[tokens[i]]])
                pc += INSTRUCTION_OFFSET[tokens[i]]

            when "XOR"
                number = translate_xor(tokens[i+1..i+INSTRUCTION_OFFSET[tokens[i]]])
                pc += INSTRUCTION_OFFSET[tokens[i]]
            end
        end
    end

# ======================================================================
# WARNING! THERE IS A PRIVATE SWAMP OF MAGIC NUMBERS DOWN HERE (｀∀´)っ🗑️
# ======================================================================
    private # <- запривачено

    def translate_xor(operands)
        rd, rs, rt = get_regs(operands)
        opcode = INSTRUCTION_SET["XOR"]
        (0 << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (0 << 6) | opcode
    end

    def translate_cbit(operands)
        rd, rs = get_regs(operands[0..1])
        imm5 = operands[2].to_i
        opcode = INSTRUCTION_SET["CBIT"]

        (opcode << 26) | (rd << 21) | (rs << 16) | (imm5 << 11) | 0
    end

    def translate_subi(operands)
        rt, rs = get_regs(operands[0..1])
        imm = operands[2].to_i
        opcode = INSTRUCTION_SET["SUBI"]

        (opcode << 26) | (rs << 21) | (rt << 21) | imm
    end

    def translate_movn(operands)
        rd, rs, rt = get_regs(operands)
        opcode = INSTRUCTION_SET["MOVN"]

        (0 << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (0 << 6) | opcode
    end

    def translate_beq(operands)
        rs, rt = get_regs(operands[0..1])
        offset = operands[2].to_i
        opcode = INSTRUCTION_SET["BEQ"]

        (opcode << 26) | (rs << 21) | (rt << 21) | offset
    end

    def translate_bext(operands)
        rd, rs1, rs2 = get_regs(operands)
        opcode = INSTRUCTION_SET["BEXT"]

        (0 << 26) | (rd << 21) | (rs1 << 16) | (rs2 << 11) | (0 << 6) | opcode
    end

    def translate_ldp(operands)
        rt1, rt2 = get_regs(operands[0..1])
        offset, base = get_offbase(operands[2..3])
        opcode = INSTRUCTION_SET["LDP"]

        (0 << opcode) | (base << 21) | (rt1 << 16) | (rt2 << 11) | offset

        # not checked !!! the lowest two bits of #offset field must be zero. else is UB.
    end

    def translate_add(operands)
        rd, rs, rt = get_regs(operands)
        opcode = INSTRUCTION_SET["ADD"]

        (0 << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (0 << 6) | opcode
    end

    def translate_ld(operands)
        rt = get_regs(operands[0..0])
        opcode = INSTRUCTION_SET["LD"]
        offset, base = get_offbase(operands[2..3])
        (opcode << 26) | (base << 21) | (rt << 16) | offset

        # not checked !!! the lowest two bits of #offset field must be zero. else is UB.
    end

    def translate_cls(operands)
        rd, rs = get_regs(operands)
        opcode = INSTRUCTION_SET["CLS"]

        (0 << 26) | (rd << 21) | (rs << 16) | (0 << 6) | opcode
    end

    def translate_rori(operands)
        rd, rs = get_regs(operands[0..1])
        imm5 = operands[2].to_i
        opcode = INSTRUCTION_SET("RORI")

        (opcode << 26) | (rd << 21) | (rs << 16) | (imm5 << 11) | 0
    end

    def translate_st(operands)
        rt = get_regs(operands[0..0])
        offset, base = get_offbase(operands[2..3])
        opcode = INSTRUCTION_SET["ST"]

        (opcode << 26) | (base << 21) | (rt << 16) | (offset)

        # not checked !!! the lowest two bits of #offset field must be zero. else is UB.
    end

    def translate_syscall()
        code = 0 # <- wtf ???
        opcode = INSTRUCTION_SET["SYSCALL"]
        (0 << 26) | (code) << 6 | opcode
    end

    def get_regs(operands)
        operands.map{|reg| REGISTERS[reg]}
    end

    def get_offbase(operands)
        [operands[0].to_i, REGISTERS[operands[1]]]
    end
end


# -------- TESTING --------
if __FILE__ == $0
    parser = Parser.new
    source = File.read("file.txt")
    tokens = parser.get_tokens(source)
    parser.translate_tokens(tokens)
end

