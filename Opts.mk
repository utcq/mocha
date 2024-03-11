NAME := mocha
SRC := mocha
OBJDIR := bin
LIMINE_DIR := limine
KERNEL := $(OBJDIR)/$(NAME).bin
ISODIR := isoroot
IMAGE := $(NAME).iso

LDSCRIPT := $(SRC)/linker.ld
LIMINE_CFG := $(SRC)/limine.cfg
