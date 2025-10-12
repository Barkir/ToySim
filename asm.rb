require_relative "toy_isa"

asm = MicroAsm.new

asm.prog do
    movn r1, r2, 48
    hlt
end
