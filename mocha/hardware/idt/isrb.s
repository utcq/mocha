extern isr_exception_handler

%macro isr_err_stub 1
isr_stub_%+%1:
	push byte %1
	call isr_exception_handler
	jmp isr_common_stub
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
	push byte 0
	push byte %1
	jmp isr_common_stub
%endmacro

%macro pushaq 0
    push rax      ;save current rax
    push rbx      ;save current rbx
    push rcx      ;save current rcx
    push rdx      ;save current rdx
    push rbp      ;save current rbp
    push rdi      ;save current rdi
    push rsi      ;save current rsi
    push r8       ;save current r8
    push r9       ;save current r9
    push r10      ;save current r10
    push r11      ;save current r11
    push r12      ;save current r12
    push r13      ;save current r13
    push r14      ;save current r14
    push r15      ;save current r15
%endmacro

%macro popaq 0
    pop rax      ; pop current rax
    pop rbx      ; pop current rbx
    pop rcx      ; pop current rcx
    pop rdx      ; pop current rdx
    pop rbp      ; pop current rbp
    pop rdi      ; pop current rdi
    pop rsi      ; pop current rsi
    pop r8       ; pop current r8
    pop r9       ; pop current r9
    pop r10      ; pop current r10
    pop r11      ; pop current r11
    pop r12      ; pop current r12
    pop r13      ; pop current r13
    pop r14      ; pop current r14
    pop r15	     ; pop current r15
%endmacro

isr_common_stub:
	pushaq
	mov ax, ds

	call isr_exception_handler

	popaq

	add esp, 8
	sti
	
	iretq

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31


global isr_stub_table
isr_stub_table:
%assign i 0
%rep 32 ; entries
	dq isr_stub_%+i
%assign i i+1
%endrep

