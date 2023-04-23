bits 32

MBOOT_PAGE_ALIGN       equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO         equ 1<<1    ; Provide your kernel with memory info
MBOOT_AOUT_KLUDGE      equ 0x00010000;
MBOOT_HEADER_MAGIC     equ 0x1BADB002 ; Multiboot Magic value
MBOOT_HEADER_FLAGS     equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO ;| MBOOT_VIDEO_MODE_BIT
MBOOT_CHECKSUM         equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

; Stack configuration. The size of our stack (16KB).
KERNEL_STACK_SIZE equ 0x4000

section .multiboot
multiboot:
align 4
    dd  MBOOT_HEADER_MAGIC      ; GRUB will search for this value on each 4-byte boundary in your kernel file
    dd  MBOOT_HEADER_FLAGS      ; How GRUB should load your file / settings
    dd  MBOOT_CHECKSUM          ; To ensure that the above values are correct

		dd 0
		dd 0
		dd 0 
		dd 0 
		dd 0 
    ; Graphic field
    dd 0
    dd 640
    dd 480
    dd 32

section .bss
align 16
stack_bottom:
resb KERNEL_STACK_SIZE ; 16 KiB
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	extern init_multiboot
	push ebx ; multiboot_info struct
	push eax ; magic number
	call init_multiboot

	
	mov esp, stack_top

	
    ;extern init_constructors
    ;call init_constructors
    ;extern init_gdt
    ;call init_gdt
    
    mov eax, 1 
    mov ebx, 0
   
    ; Initialize the Interrupt Descriptor Table
    ;extern init_idt
    ;call init_idt

    ; Initialize the Interrupt Service Routine
    ;extern init_isr
    ;call init_isr

	
	extern kernel_main
	call kernel_main  

	
	cli
.hang:	hlt
	jmp .hang
.end: