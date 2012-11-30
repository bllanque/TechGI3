# Einstellungen für das 3. Aufgabenblatt
#    Diese Einstellungen müssen sie anpassen, wenn sie zusätzliche Dateien hinzufügen
BIN = scheduler
SRC = \
	tasklist.c \
	FIFO.c \
	RR.c \
	SJN.c \
	RR_MLF.c \
	main.c \
	vorgabe.c \
	sem_tests.c \
	$(null)
HDRS = \
	tasklist.h \
	FIFO.h \
	RR.h \
	SJN.h \
	RR_MLF.h \
	system.h \
	vorgabe.h \
	sem_tests.h \
	$(null)
EXTRA_DIST_FILES = README.txt

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
	./$(BIN)

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
	$(RM) $(DISTFILE).tar.bz2 $(DISTFILE).zip

.PHONY: clean debug dist distclean loc rerun rebuild run zip
