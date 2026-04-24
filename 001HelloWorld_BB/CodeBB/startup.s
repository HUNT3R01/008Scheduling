  .section .text
  .global _start

_start:
  b reset

reset:
  ldr sp, =0x80020000   @ Set up stack pointer (within RAM)
  mrs r0, cpsr
  orr r0, r0, #0xD3   @ modo SVC, IRQ y FIQ desactivados
  msr cpsr_c, r0
  bl main               @ Call the main function
loop:
  b loop                @ Infinite loop to prevent exit
