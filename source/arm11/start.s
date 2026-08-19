.section .text.start
.global _start
.arm

_start:
  cpsid if

  ldr sp, =0x1FFFE000

  bl arm11_main

1:
  b 1b
