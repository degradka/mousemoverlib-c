CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -O3
INCLUDE = -I./

MOUSEMOVER_INSTALL_PATH ?= /usr/local/lib
MOUSEMOVER_H_INSTALL_PATH ?= /usr/local/include

ROOT = $(shell whoami)

libmousemoverlib.a : mousemover.o
	ar rcs $@ $^

mousemover.o : mousemover.c mousemover.h
	$(CC) $(CFLAGS) -c $< $(INCLUDE)

.PHONY : install
install : libmousemoverlib.a
ifeq ($(ROOT),root)
	@echo "Installing mousemoverlib to $(MOUSEMOVER_INSTALL_PATH)..."
	mkdir -p $(MOUSEMOVER_INSTALL_PATH)
	cp libmousemoverlib.* $(MOUSEMOVER_INSTALL_PATH)
	@echo "Installing mousemover.h to $(MOUSEMOVER_H_INSTALL_PATH)..."
	mkdir -p $(MOUSEMOVER_H_INSTALL_PATH)
	cp mousemover.h $(MOUSEMOVER_H_INSTALL_PATH)
	@echo "mousemoverlib installed!"
else
	@echo "Error: Root permissions needed for installation. Try sudo make install"
endif

.PHONY : uninstall
uninstall :
ifeq ($(ROOT),root)
	@echo "removing mousemoverlib from $(MOUSEMOVER_INSTALL_PATH) and $(MOUSEMOVER_H_INSTALL_PATH)..."
	rm --force --interactive --verbose $(MOUSEMOVER_INSTALL_PATH)/libmousemoverlib.*
	rm --force --interactive --verbose $(MOUSEMOVER_H_INSTALL_PATH)/mousemover.h
	@echo "mousemoverlib removed!"
else
	@echo "Error: Root permissions needed for installation. Try sudo make install"
endif

.PHONY : clean
clean :
	@echo "removed all generated files!"
	rm -fv *.o libmousemoverlib.*
