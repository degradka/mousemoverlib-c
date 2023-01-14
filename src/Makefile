CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -O3
LDFLAGS = -lX11 -lXtst -lXinerama
INCLUDE = -I./

MOUSEMOVER_INSTALL_PATH ?= /usr/local/lib
MOUSEMOVER_H_INSTALL_PATH ?= /usr/local/include

LIBNAME ?= mousemover
LIBTYPE ?= STATIC

ROOT = $(shell whoami)

ifeq ($(LIBTYPE),SHARED)
lib$(LIBNAME)lib.so : $(LIBNAME).o
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ $(LDFLAGS)
else
lib$(LIBNAME)lib.a : $(LIBNAME).o
	ar rcs $@ $^
endif

$(LIBNAME).o : $(LIBNAME).c $(LIBNAME).h
	$(CC) $(CFLAGS) -c $< $(INCLUDE)

.PHONY : install
install :
ifeq ($(ROOT),root)
	@echo "Installing $(LIBNAME)lib to $(MOUSEMOVER_INSTALL_PATH)..."
	mkdir -p $(MOUSEMOVER_INSTALL_PATH)
	cp lib$(LIBNAME)lib.* $(MOUSEMOVER_INSTALL_PATH)
	@echo "Installing $(LIBNAME).h to $(MOUSEMOVER_H_INSTALL_PATH)..."
	mkdir -p $(MOUSEMOVER_H_INSTALL_PATH)
	cp $(LIBNAME).h $(MOUSEMOVER_H_INSTALL_PATH)
	@echo "$(LIBNAME)lib installed!"
else
	@echo "Error: Root permissions needed for installation. Try sudo make install"
endif

.PHONY : uninstall
uninstall :
ifeq ($(ROOT),root)
	@echo "removing lib$(LIBNAME) from $(MOUSEMOVER_INSTALL_PATH) and $(MOUSEMOVER_H_INSTALL_PATH)..."
	rm --force --interactive --verbose $(MOUSEMOVER_INSTALL_PATH)/lib$(LIBNAME)lib.*
	rm --force --interactive --verbose $(MOUSEMOVER_H_INSTALL_PATH)/$(LIBNAME).h
	@echo "lib$(LIBNAME) removed!"
else
	@echo "Error: Root permissions needed for uninstallation. Try sudo make uninstall"
endif

.PHONY : clean
clean :
	@echo "removing all generated files!"
	rm -fv *.o lib$(LIBNAME)lib.*
