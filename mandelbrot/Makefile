# Einstellungen für das 2. Aufgabenblatt
#    Diese Einstellungen müssen sie anpassen, wenn sie zusätzliche Dateien hinzufügen
BIN = mandelbrot
SRC = \
	bitmap.c \
	color.c \
	util.c \
	main.c \
	mandelbrot.c \
	$(null)
HDRS = \
	bitmap.h \
	color.h \
	util.h \
	mandelbrot.h \
	$(null)
EXTRA_DIST_FILES = README

# Einstellungen für den Übersetzer
#    Diese Einstellungen müssen sie ggf. an ihr System anpassen
CFLAGS  = -std=c99 -g -Wall -Wextra -O2
LDFLAGS = -lm

BZIP2  = bzip2
CC     = gcc
GDB    = gdb
RM     = rm -f
TAR    = tar
WC     = wc
ZIP    = zip

DISTFILE = techgi3-$(BIN)
DEPENDFILE = depend
OBJS = $(SRC:%.c=%.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

debug: $(BIN)
	$(GDB) ./$(BIN)

run: $(BIN)
	./$(BIN) mandelbrot.bmp

rebuild: distclean all

rerun: distclean run

$(DEPENDFILE): $(SRC)
	$(CC) -MM $^ > $@

include $(DEPENDFILE)

dist: $(DISTFILE).tar.bz2

$(DISTFILE).tar.bz2: $(SRC) $(HDRS) Makefile $(EXTRA_DIST_FILES)
	$(TAR) -cf - $^ | $(BZIP2) -c > $@

# lines of code
loc:
	$(WC) $(SRC) $(HDRS)

zip: $(DISTFILE).zip

$(DISTFILE).zip: $(SRC) $(HDRS) Makefile $(EXTRA_DIST_FILES)
	$(RM) $@
	$(ZIP) -j $@ $^

clean:
	$(RM) $(BIN) $(OBJS) $(DEPENDFILE)

distclean: clean
	$(RM) $(DISTFILE).tar.bz2 $(DISTFILE).zip *.bmp

.PHONY: clean debug dist distclean loc rerun rebuild run zip
