include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 1
VAR2 = 1
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2) -D DIR=$(POCETNI_DIREKTORIJ)

OBJEKTI = lab1y.o
MODUL = mod-lab1y.o

$(MODUL): $(OBJEKTI)
	$(LD) -r $^ $(LDFLAGS) -o $@ 

lab1y.o: lab1y.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<
	

# brisanje
.PHONY: brisi
brisi:
	rm -f $(OBJEKTI) $(MODUL)