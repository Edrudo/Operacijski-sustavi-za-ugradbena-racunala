# Prvi, korjenski Makefile

POCETNI_DIREKTORIJ = $(shell pwd)
export POCETNI_DIREKTORIJ # vidljivo u pozvanim Makefile-ovima!

include $(POCETNI_DIREKTORIJ)/config.ini

# glavni cilj prevoÄ‘enja (da bude prvi)
all: $(PROGRAM)

CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2) -D DIR=\"$(POCETNI_DIREKTORIJ)\"

OBJEKTI = main.o # objekti koji se ovdje stvaraju
MODULI = eduard/mod-eduard.o  # srednje/mod-srednje.o veliko/mod-srednje.o # objekti iz modula

$(PROGRAM): $(OBJEKTI) $(MODULI)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
# i ovdje je koriĹˇten CC umjesto LD - ima nekih problema...

main.o: main.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: $(MODULI)
$(MODULI):
	$(MAKE) -C $(dir $@)

# brisanje
.PHONY: brisi
brisi:
	$(MAKE) -C eduard brisi
	rm -f $(OBJEKTI) $(PROGRAM)

.PHONY: pokreni
pokreni:
		./primjer