require_relative "constants"

class Integer
    def method_missing(name, *args)
        if name.to_s =~ /^r([1-9]|[12][0-9]|[3][01])$/ && args.empty?
            return {offset: self, base: name}
        end
    end
end

class MicroAsm
    include Constants

    def initialize
        @labels = {}
        @pc = 0
        @commands = []
        @registers = {}

        (1..31).each do |i|
            reg_name = "r#{i}".to_sym
            self.define_singleton_method(reg_name) do
                i
            end
        end
    end

    def prog(&block)
        @collecting_labels = true
        @pc = 0
        instance_eval(&block)

        @pc = 0
        @collecting_labels = false
        instance_eval(&block)
    end

    def jmp(label)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_j(@labels[label])
        @pc += 1
    end

    def cbit(rd, rs, imm5)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_cbit([rd, rs, imm5])
        @pc += 1
    end

    def subi(rt, rs, imm)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_subi([rt, rs, imm])
        @pc += 1
    end

    def movn(rd, rs, rt)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_movn([rd, rs, rt])
        @pc += 1
    end

    def beq(rs, rt, offset)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_beq([rs, rt, offset])
        @pc += 1
    end

    def bext(rd, rs1, rs2)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_bext([rd, rs1, rs2])
        @pc += 1
    end

    def ldp(rt1, rt2, offbase)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_ldp([rt1, rt2, offbase])
        @pc += 1
    end

    def add(rd, rs, rt)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = tranlsate_add([rd, rs, rt])
        @pc += 1
    end

    def ld(rt, offbase)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_ld([rt, offbase])
        @pc += 1
    end

    def cls(rd, rs)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_cls([rd, rs])
        @pc += 1
    end

    def rori(rd, rs, imm5)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_rori([rd, rs, imm5])
        @pc += 1
    end

    def st(rt, offbase)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_st([rt, offbase])
        @pc += 1
    end

    def xor(rd, rs, rt)
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_xor([rd, rs, rt])
        @pc += 1
    end

    def syscall()
        if @collecting_labels
            @pc += 1
            return
        end

        @commands[@pc] = translate_syscall()
        @pc += 1
    end

    def hlt()
        if @collecting_labels
            @pc += 1
            return
        end

        @commands.each_with_index do |cmd, idx|
            printf "0x%04X: %08X\n", idx, cmd
        end

        puts "Writing to file result.bin..."
        File.open("result.bin", "wb") do |file|
            @commands.each do |elem|
                file.write([elem].pack("N"))
            end
        end
    end

    def label(label_str)
        if @collecting_labels
            printf "PRECOMP: got label %s with pc %d\n", label_str, @pc
            @labels[label_str] = @pc
        end
    end



# ======================================================================
# WARNING! THERE IS A PRIVATE SWAMP OF MAGIC NUMBERS DOWN HERE (｀∀´)っ🗑️
# ======================================================================
    private # <- запривачено

    def translate_j(label_pc)
        opcode = INSTRUCTION_SET["J"]
        printf "JMP: label_pc %d, pc %d, offset %d\n", label_pc, @pc, (label_pc - @pc)
        (opcode << 26) | (label_pc - @pc & 0x3FFFFFF) # count jmp from the next pc after jmp (from label)
    end


    def translate_xor(operands)
        rd, rs, rt = operands
        opcode = INSTRUCTION_SET["XOR"]

        (0 << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (0 << 6) | opcode
    end

    def translate_cbit(operands)
        rd, rs, imm5 = operands
        opcode = INSTRUCTION_SET["CBIT"]

        (opcode << 26) | (rd << 21) | (rs << 16) | (imm5 << 11) | 0
    end

    def translate_subi(operands)
        rt, rs, imm = operands
        opcode = INSTRUCTION_SET["SUBI"]

        (opcode << 26) | (rs << 21) | (rt << 21) | imm
    end

    def translate_movn(operands)
        rd, rs, rt = operands
        opcode = INSTRUCTION_SET["MOVN"]

        (0 << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (0 << 6) | opcode
    end

    def translate_beq(operands)
        rs, rt, offset = operands
        opcode = INSTRUCTION_SET["BEQ"]

        (opcode << 26) | (rs << 21) | (rt << 21) | offset
    end

    def translate_bext(operands)
        rd, rs1, rs2 = operands
        opcode = INSTRUCTION_SET["BEXT"]

        (0 << 26) | (rd << 21) | (rs1 << 16) | (rs2 << 11) | (0 << 6) | opcode
    end

    def translate_ldp(operands)
        rt1, rt2 = operands[0..1]
        offset, base = extract_adr(operands[2])
        opcode = INSTRUCTION_SET["LDP"]

        (0 << opcode) | (base << 21) | (rt1 << 16) | (rt2 << 11) | offset

        # not checked !!! the lowest two bits of #offset field must be zero. else is UB.
    end

    def translate_add(operands)
        rd, rs, rt = operands
        opcode = INSTRUCTION_SET["ADD"]

        (0 << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (0 << 6) | opcode
    end

    def translate_ld(operands)
        rt = operands[0]
        offset, base = extract_adr(operands[1])
        opcode = INSTRUCTION_SET["LD"]
        (opcode << 26) | (base << 21) | (rt << 16) | offset

        # not checked !!! the lowest two bits of #offset field must be zero. else is UB.
    end

    def translate_cls(operands)
        rd, rs = operands
        opcode = INSTRUCTION_SET["CLS"]

        (0 << 26) | (rd << 21) | (rs << 16) | (0 << 6) | opcode
    end

    def translate_rori(operands)
        rd, rs, imm5 = operands
        opcode = INSTRUCTION_SET["RORI"]

        (opcode << 26) | (rd << 21) | (rs << 16) | (imm5 << 11) | 0
    end

    def translate_st(operands)
        rt = operands[0]
        offset, base = extract_adr(operands[1])
        opcode = INSTRUCTION_SET["ST"]

        (opcode << 26) | (base << 21) | (rt << 16) | (offset)

        # not checked !!! the lowest two bits of #offset field must be zero. else is UB.
    end

    def translate_syscall()
        code = 0 # <- wtf ???
        opcode = INSTRUCTION_SET["SYSCALL"]

        (0 << 26) | (code) << 6 | opcode
    end

    def extract_adr(operand)
        if operand.is_a?(Hash) && operand[:offset] && operand[:base]
            [operand[:offset], operand[:base].to_s.delete(":r").to_i]
        end
    end
end

