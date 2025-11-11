require_relative "../toy_isa"

asm8 = MicroAsm.new
asm8.prog do
    xor r1, r1, r1
    cbit r1, r2, 50
end
