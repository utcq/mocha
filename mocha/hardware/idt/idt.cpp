#include <libc/stdio.h>
#include <hardware/idt.h>
#include <hardware/gdt.h>
#include <stdint.h>

__attribute__ ((aligned(0x10))) // Performance
static idt_entry_t idt[IDT_ENTRIES];

extern void *isr_stub_table[];

static idtr_t idtr;

extern "C" {
	void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
}
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
	idt_entry_t *descriptor = &idt[vector];

	descriptor->isr_low    = (uint64_t)isr & 0xFFFF;
	descriptor->kernel_cs  = GDT_OFFSET_KERNEL_CODE;
	descriptor->ist        = 0;
	descriptor->attributes = flags;
	descriptor->isr_mid    = ((uint64_t)isr >> 16) & 0xFFFF;
	descriptor->isr_high   = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
	descriptor->reserved   = 0;
	dbprintf("\033[32;49;3m[IDT] \033[36;49;3mEntry %d created\n\033[0m", vector);
}


extern "C" {
	void init_idt(void);
	void init_idt() {
		idtr.base = (uintptr_t)&idt[0]; // Init IDT register
		idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_ENTRIES - 1;
		for (uint8_t vector=0; vector<ISR_ENTRIES;vector++) { // Set ISR exceptions
			idt_set_descriptor(vector, isr_stub_table[vector], INT_GATE);
		}

		__asm__ volatile("lidt %0" : : "m"(idtr)); // Set idt register
		__asm__ volatile("sti");  // Enable interrupts
	}
}
