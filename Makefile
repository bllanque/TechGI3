
BIN = stripstring
SRC = $(wildcard *.c)
HDRS = $(filter-out main.h, $(patsubst %.c, %.h, $(SRC)))
	
EXTRA_DIST_FILES = 

# Einstellungen für den Übersetzer
#    Diese Einstellungen müssen Sie ggf. an ihr System anpassen
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
