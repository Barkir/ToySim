require_relative "constants"

class Parser
    include Constants

    def get_tokens(text)
        # creating flat array of tokens from lines
        # [["XOR", "R1", "R2", "R3"], ["ADD", "R2", "R7", "R9"]] -> ["XOR", "R1", "R2", "R3", "ADD", "R2", "R7", "R9"]
        text.lines.map.flat_map do |line|
            line = line.split(";", 2).first.to_s.strip || line # fuck comments
            next [] if line.empty? # skip empty arrays
            if line.end_with?(":")
                # raising error if wrong label format
                j_instr = line.split
                if j_instr[0] == "J" && j_instr[1].include?(" ")
                    raise "Error: label contains spaces -> #{line}"
                end
            end
            line = line.gsub(/[()]/, " ") # replacing brackets with space symbol
            tokens = line.split.map {|t| t.delete(",").delete("#").delete(" ")} # deleting commas (fuck commas (and #commas))
        end
    end


    def fill_labels(tokens)
        labels_dict = {}
        pc = 0
        (0..tokens.size - 1).each do |i|
            token = tokens[i]
            if is_label(token)
                pc += 1
                labels_dict[token] = pc
            else
                pc += 1
            end

        end
        return labels_dict
    end


    def translate_tokens(tokens, labels_dict)
        pc = 0
        (0...tokens.size).each do |i|
            instr = tokens[i]
            if INSTRUCTION_SET.key?(instr) && instr != "J"
                offset = INSTRUCTION_OFFSET[instr]
                instruction = send("translate_#{instr.downcase}", tokens[i+1..i+offset]) # sends a message (works like eval in python)
                pc += offset
            elsif INSTRUCTION_SET.key?(instr) && instr == "J"
                offset = INSTRUCTION_OFFSET[instr]

                label = tokens[i+1]
                label_pc = labels_dict[label]

                instruction = translate_j(label_pc, pc)
                pc += offset
            end
        end
    end

# ======================================================================
# WARNING! THERE IS A PRIVATE SWAMP OF MAGIC NUMBERS DOWN HERE (｀∀´)っ🗑️
# ======================================================================
    private # <- запривачено

    def is_label(token)
        token.end_with?(":")
    end

    def translate_j(label_pc, pc)
        opcode = INSTRUCTION_SET["J"]
        (opcode << 26) | (label_pc - (pc + 1)) # count jmp from the next pc after jmp (from label)
    end


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
    lab_dict = parser.fill_labels(tokens)
    parser.translate_tokens(tokens, lab_dict)
end

