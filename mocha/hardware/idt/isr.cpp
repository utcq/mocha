#include <hardware/idt.h>
#include <stdint.h>
#include <libc/stdio.h>

const char *exception_table[] = {
	"Division Error",
	"Debug",
	"Non-maskable interrupt",
	"Breakpoint",
	"Overflow",
	"Bound Range Exceeded",
	"Invalid Opcode",
	"Device Not Avaiable",
	"Double Fault",
	"Coprocessor Error",
	"Invalid TSS",
	"Segment Not Present",
	"Stack-Segment fault",
	"General Protection Fault",
	"Page Fault",
	"Reserved",
	"x87 Floating-Point Exception",
	"Alignment Check",
	"Machine Check",
	"SIMD Floating-Point Exception",
	"Virtualizzation Exception",
	"Control Protection Exception",
	"Reserved",
	"Hypervisor Injection Exception",
	"VMM Communication Exception",
	"Security Exception",
	"Triple Fault",
	"FPU Error"
};

void isr_info_dump(registers_t *regs) {
	dbprintf("\033[33;49m RAX: \033[37;49;3m%x\n\033[0m", regs->rax);
	dbprintf("\033[33;49m RBX: \033[37;49;3m%x\n\033[0m", regs->rbx);
	dbprintf("\033[33;49m RCX: \033[37;49;3m%x\n\033[0m", regs->rcx);
	dbprintf("\033[33;49m RDX: \033[37;49;3m%x\n\033[0m", regs->rdx);
	dbprintf("\033[33;49m RBP: \033[37;49;3m%x\n\033[0m", regs->rbp);
	dbprintf("\033[33;49m RDI: \033[37;49;3m%x\n\033[0m", regs->rdi);
	dbprintf("\033[33;49m RSI: \033[37;49;3m%x\n\033[0m", regs->rsi);
}

extern "C" {
	void isr_exception_handler(registers_t regs);
}
void isr_exception_handler(registers_t regs) {
	dbprintf("\033[31;49;3m[EXCEPTION] %s {ERR: %d}\n\033[0m", exception_table[regs.int_no], regs.err_code);
	isr_info_dump(&regs);
	__asm__ volatile("cli; hlt");
}
