# Glorious GMMK 3 Pro 75% ISO (WB32) - Makefile
# Convenience wrapper around setup_and_flash.sh and qmk

.PHONY: all build flash udev clean help

all: build

build:
	@./setup_and_flash.sh --build

flash:
	@./setup_and_flash.sh --flash

udev:
	@./setup_and_flash.sh --udev

clean:
	@./setup_and_flash.sh --clean

help:
	@./setup_and_flash.sh --help
