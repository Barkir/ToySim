require_relative "../toy_isa"

asm3 = MicroAsm.new
asm3.prog do
  subi r1, r0, 50000
  subi r2, r0, 1
  subi r3, r0, 3
  xor r1, r1, r2
  xor r1, r1, r2

  label :loop1
  add r2, r2, r2
  add r4, r4, r3
  xor r5, r2, r4

  movn r6, r2, r2
  movn r7, r4, r4
  movn r8, r5, r5

  subi r1, r1, 1
  beq r1, r0, :end1
  jmp :loop1
  label :end1
end
