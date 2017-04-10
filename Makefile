.PHONY: all install

BUILDDIR=build
$(shell mkdir -p $(BUILDDIR))

CC?=cc
PREFIX?=/usr/local
INSTALL_LIB?=$(PREFIX)/lib

STLIB=$(BUILDDIR)/libfakessp.a
SHLIB=$(BUILDDIR)/libfakessp.so
STOBJ=$(BUILDDIR)/libfakessp.o
SHOBJ=$(BUILDDIR)/libfakessp.os

CFLAGS+=-std=c99

all: $(STLIB) $(SHLIB)

$(STLIB): $(STOBJ)
	rm -f $@
	ar rcs $@ $<

$(SHLIB): $(SHOBJ)
	$(CC) -shared -o $@ $<

$(STOBJ): fakessp.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(SHOBJ): fakessp.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<


install: $(STLIB) $(SHLIB)
	install -m 644 $(STLIB) $(INSTALL_LIB)
	install -m 644 $(SHLIB) $(INSTALL_LIB)
