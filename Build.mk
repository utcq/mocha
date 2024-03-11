-include Opts.mk

CXX := clang++
CXFLAGS := \
	-c \
	-Wall \
	-Wextra \
	-ffreestanding \
	-fno-exceptions \
	-fno-lto \
	-fPIE \
	-m64 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-fno-stack-protector \
	-fno-stack-check \
	-I$(SRC) \
	-I$(LIMINE_DIR)

CC := clang
CCFLAGS := \
	-c \
	-Wall \
	-Wextra \
	-ffreestanding \
	-fno-exceptions \
	-fno-lto \
	-fPIE \
	-m64 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-fno-stack-protector \
	-fno-stack-check \
	-I$(SRC) \
	-I$(LIMINE_DIR)

AS := nasm
ASFLAGS := \
	-f elf64 \
	-g \
	-F dwarf

LD := ld
LDFLAGS := \
	-nostdlib \
	-m elf_x86_64 \
	-static \
	--no-dynamic-linker \
	-z notext \
	-z max-page-size=0x1000


XR := xorriso
XRARGS := \
	-as mkisofs \
	-b limine-bios-cd.bin \
	-no-emul-boot \
	-boot-load-size 4 \
	--boot-info-table \
	--efi-boot limine-uefi-cd.bin \
	--efi-boot-part \
	--efi-boot-image \
	--protective-msdos-label 


QEMU := qemu-system-x86_64
QEMUARGS := \
	-smp 2 \
	-m 256 \
	-bios /usr/share/OVMF/x64/OVMF.fd \
	-serial mon:stdio
