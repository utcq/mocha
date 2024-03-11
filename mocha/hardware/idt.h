#include <stdint.h>

#ifndef _HW_IDT_H
#define _HW_IDT_H

#define IDT_ENTRIES 256
#define ISR_ENTRIES 32

#define INT_GATE   0x8E
#define TRAP_GATE  0x8F

typedef struct {
	uint16_t isr_low; // isr lower 16 bits
	uint16_t kernel_cs; // GDT Kernel code Segment
	uint8_t ist;
	uint8_t attributes; // Attrs
	uint16_t isr_mid; // isr higher 16 bits
	uint32_t isr_high; // isr higher 32 bits
	uint32_t reserved;
} __attribute__ ((packed)) idt_entry_t;


typedef struct {
	uint16_t limit;
	uint64_t base;
} __attribute__ ((packed)) idtr_t;

typedef struct registers {
	uint64_t r15,r14,r13,r12,r11,r10,r8,r9,rsi,rdi,rbp,rdx,rcx,rbx,rax;
	uint64_t int_no, err_code;
} registers_t;

extern "C" {
	void init_idt(void);
}

#endif
