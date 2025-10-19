require_relative "constants"


class Integer
    def method_missing(name, *args)
        if name.to_s =~ /^r([1-9]|[12][0-9]|[3][01])$/ && args.empty?
            value = send(name) # calling a register method(r1 -> 1, r2 -> 2, ...)
            return {offset: self, base: value}
        end
        # reg_array
    end
end

class MicroAsm
    include Constants

    def initialize
        @labels = {}
        @pc = 0
        @commands = []
        @registers = {}

        (0..31).each do |i|
            reg_name = "r#{i}".to_sym
            self.define_singleton_method(reg_name) do
                i
            end
        end
    end

    def prog(&block)

    # ---------------------------
        @collecting_labels = true
        @pc = 0
        instance_eval(&block)
    # ---------------------------------

        @pc = 0
        @command_pc = 0
        @collecting_labels = false
        instance_eval(&block)
    end

    def write_command(value)
        @commands[@command_pc] = value

        @pc += 4
        @command_pc += 1
    end

    def jmp(label)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_j(@labels[label]))
    end

    def cbit(rd, rs, imm5)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_cbit([rd, rs, imm5]))
    end

    def subi(rt, rs, imm)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_subi([rt, rs, imm]))
    end

    def movn(rd, rs, rt)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_movn([rd, rs, rt]))
    end

    def beq(rs, rt, offset)
        if @collecting_labels
            @pc += 4
            return
        end

        if @labels[offset]
            # printf "BEQ WITH LABEL!!!\n"
            write_command(translate_beq([rs, rt, (@labels[offset] - @pc) & 0xFFFF]))
        else
            # printf "BEQ WITHOUT LABEL!!!\n"
            write_command(translate_beq([rs, rt, offset]))
        end
    end

    def bext(rd, rs1, rs2)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_bext([rd, rs1, rs2]))
    end

    def ldp(rt1, rt2, offbase)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_ldp([rt1, rt2, offbase]))
    end

    def add(rd, rs, rt)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_add([rd, rs, rt]))
    end

    def ld(rt, offbase)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_ld([rt, offbase]))
    end

    def cls(rd, rs)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_cls([rd, rs]))
    end

    def rori(rd, rs, imm5)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_rori([rd, rs, imm5]))
    end

    def st(rt, offbase)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_st([rt, offbase]))
    end

    def xor(rd, rs, rt)
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_xor([rd, rs, rt]))
    end

    def syscall()
        if @collecting_labels
            @pc += 4
            return
        end

        write_command(translate_syscall())
    end

    def hlt()
        if @collecting_labels
            @pc += 4
            return
        end

        @commands.each_with_index do |cmd, idx|
            printf "0x%04X: %08X %b\n", idx, cmd, cmd
        end

        # printf "Writing to file result.bin...\n"
        File.open("result.bin", "wb") do |file|
            @commands.each do |elem|
                file.write([elem].pack("L<")) ## little endian
            end
            absolute_path = File.expand_path("result.bin")
            file.close()
            system(TOY_SIM + "ToySim " + absolute_path)

        end
    end

    def label(label_str)
        raise  "Expected symbol, got #{label_str.class}" unless label_str.is_a?(Symbol)
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
        (opcode << 26) | ((label_pc - @pc) & 0x3FFFFFF) # count jmp from the next pc after jmp (from label)
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

        (opcode << 26) | (rs << 21) | (rt << 16) | imm
    end

    def translate_movn(operands)
        rd, rs, rt = operands
        opcode = INSTRUCTION_SET["MOVN"]

        (0 << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (0 << 6) | opcode
    end

    def translate_beq(operands)
        rs, rt, offset = operands
        opcode = INSTRUCTION_SET["BEQ"]

        (opcode << 26) | (rs << 21) | (rt << 16) | offset
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

        (opcode << 26) | (base << 21) | (rt1 << 16) | (rt2 << 11) | offset

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
            [operand[:offset], operand[:base]] ## use method
        end
    end
end

