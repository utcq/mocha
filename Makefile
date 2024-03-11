-include Build.mk
-include Opts.mk

CXFILES := $(shell find $(SRC) -name "*.cpp")
CFILES := $(shell find $(SRC) -name "*.c")
ASFILES := $(shell find $(SRC) -name "*.s")
CXOBJECTS := $(patsubst $(SRC)/%.cpp,$(OBJDIR)/%.o,$(CXFILES))
COBJECTS := $(patsubst $(SRC)/%.c,$(OBJDIR)/%.o,$(CFILES))
AOBJECTS := $(patsubst $(SRC)/%.s,$(OBJDIR)/%.o,$(ASFILES))

all: build

.PHONY: clear

clear:
	@rm -rf $(OBJDIR)/*
	@rm -f $(IMAGE)

build: $(COBJECTS) $(CXOBJECTS) $(AOBJECTS) link image

$(OBJDIR)/%.o: $(SRC)/%.cpp
	@mkdir -p $(basename $@)
	@echo [CXX] Building $(notdir $<)
	@$(CXX) $(CXFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRC)/%.c
	@mkdir -p $(basename $@)
	@echo [CC] Building $(notdir $<)
	@$(CC) $(CCFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRC)/%.s
	@mkdir -p $(basename $@)
	@echo [AS] Building $(notdir $<)
	@$(AS) $(ASFLAGS) $< -o $@

link:
	@mkdir -p $(OBJDIR)
	@echo [LD] Linking objects
	@$(LD) $(LDFLAGS) -T $(LDSCRIPT) $(COBJECTS) $(CXOBJECTS) $(AOBJECTS) -o $(KERNEL)

image:
	@echo [CMD] Copying limine files
	@mkdir -p $(ISODIR)
	@cp $(KERNEL) $(LIMINE_CFG) $(LIMINE_DIR)/limine-bios.sys \
		 $(LIMINE_DIR)/limine-bios-cd.bin $(LIMINE_DIR)/limine-uefi-cd.bin \
		 $(ISODIR)
	@mkdir -p $(ISODIR)/EFI/BOOT/
	@cp $(LIMINE_DIR)/BOOTX64.EFI $(LIMINE_DIR)/BOOTIA32.EFI $(ISODIR)/EFI/BOOT/
	@echo [XORRISO] Creating image
	@$(XR) $(XRARGS) $(ISODIR) -o $(IMAGE) >/dev/null 2>&1 || true
	@echo [LIMINE] Installing bootloader
	@limine bios-install $(IMAGE)

run:
	$(QEMU) $(QEMUARGS) -cdrom $(IMAGE)
