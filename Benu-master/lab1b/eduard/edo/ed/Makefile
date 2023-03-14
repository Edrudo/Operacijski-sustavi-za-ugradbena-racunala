include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 111
VAR2 = 3
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2) -D DIR=$(POCETNI_DIREKTORIJ)

OBJEKTI = ed.o e.o
MODUL = mod-ed.o mod-e.o

$(MODUL): $(OBJEKTI)
	$(LD) -r $^ $(LDFLAGS) -o $@

ed.o: ed.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<
e.o: e.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

# brisanje
.PHONY: brisi
brisi:
	rm -f $(OBJEKTI) $(MODUL)