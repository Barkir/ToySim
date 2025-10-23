require_relative "../toy_isa"

asm1 = MicroAsm.new
asm1.prog do
  subi r1, r0, 100
  subi r2, r0, 50
  subi r3, r0, 25
  subi r4, r0, 10

  add r5, r1, r2
  add r6, r1, r2
  add r7, r3, r3
  add r7, r7, r7
  add r7, r7, r4

  xor r8, r1, r2
  xor r9, r1, r3
  xor r10, r2, r3

  subi r1, r1, 1
  subi r2, r2, 2
  subi r3, r0, 1
  add r4, r4, r3
end
