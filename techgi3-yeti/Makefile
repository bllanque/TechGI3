# Einstellungen für das 4. Aufgabenblatt
#    Diese Einstellungen müssen sie anpassen, wenn sie zusätzliche Dateien hinzufügen
BIN = yeti
SRC = \
	buffer.c \
	util.c \
	main.c \
	$(null)
HDR = \
	buffer.h \
	util.h \
	$(null)
EXTRA_DIST_FILES = README

# Einstellungen für den Übersetzer
#    Diese Einstellungen müssen sie ggf. an ihr System anpassen
CFLAGS  = -std=c99 -g -Wall -Wextra -O1
LDFLAGS = -lpthread

BZIP2  = bzip2
CC     = gcc
DEPEND = makedepend
GDB    = gdb
RM     = rm -f
TAR    = tar
WC     = wc
ZIP    = zip

DEPENDFILE = depend
DISTFILE = techgi3-$(BIN)
OBJS = $(SRC:%.c=%.o)
CPU_COUNT = $(shell if which mpstat > /dev/null 2>&1; then mpstat | tail +2 | wc -l; else cat /proc/cpuinfo | grep processor | wc -l; fi)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

debug: $(BIN)
	$(GDB) ./$(BIN)

run: $(BIN)
	./$(BIN) yeti.4M.txt 4

rebuild: distclean all

rerun: distclean run

$(DEPENDFILE): $(SRC)
	$(CC) -MM $^ > $@

include $(DEPENDFILE)

stat: $(BIN)
	> stat.csv
	for file in $(wildcard *.txt); do \
		i=1; \
		while test $$i -lt 65; do \
			./$(BIN) $$file $$i -stat 2>> stat.csv; \
			i=`expr $$i + 1`; \
		done; \
	done; \
	echo "Die Statistikdaten wurden in Datei 'stat.csv' geschrieben."


info:
	@echo "Die Maschine hat $(CPU_COUNT) Prozessoren/Kerne."

dist: $(DISTFILE).tar.bz2

$(DISTFILE).tar.bz2: $(SRC) $(HDR) Makefile $(EXTRA_DIST_FILES)
	$(TAR) -cf - $^ | $(BZIP2) -c > $@

# lines of code
loc:
	$(WC) $(SRC) $(HDR)

zip: $(DISTFILE).zip

$(DISTFILE).zip: $(SRC) $(HDR) Makefile $(EXTRA_DIST_FILES)
	$(RM) $@
	$(ZIP) -j $@ $^

clean:
	$(RM) $(BIN) $(OBJS) $(DEPENDFILE) *.csv

distclean: clean
	$(RM) $(DISTFILE).tar.bz2 $(DISTFILE).zip

.PHONY: clean debug dist distclean info loc rerun rebuild run stat zip
