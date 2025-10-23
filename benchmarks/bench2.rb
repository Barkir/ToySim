require_relative "../toy_isa"


asm2 = MicroAsm.new
asm2.prog do
  subi r1, r0, 0xAA
  subi r2, r0, 0xBB
  subi r3, r0, 0xCC
  subi r4, r0, 0xDD
  
  movn r5, r1, r1
  movn r6, r2, r2
  movn r7, r3, r3
  movn r8, r4, r4
  
  movn r9, r1, r1
  movn r1, r2, r2
  movn r2, r3, r3
  movn r3, r4, r4
  movn r4, r9, r9
  
  movn r10, r1, r1
  movn r11, r2, r2
  movn r12, r3, r3
  movn r13, r4, r4
end