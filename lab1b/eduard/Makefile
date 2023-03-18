include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 1
VAR2 = 1
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2) -D DIR=$(POCETNI_DIREKTORIJ)

OBJEKTI = eduard.o
MODULI = edo/mod-edo.o
MODUL = mod-eduard.o

$(MODUL): $(OBJEKTI) $(MODULI)
	$(LD) -r $^ $(LDFLAGS) -o $@ 

eduard.o: eduard.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<
	

.PHONY: $(MODULI)
$(MODULI):
	$(MAKE) -C $(dir $@)

# brisanje
.PHONY: brisi
brisi:
	$(MAKE) -C edo brisi
	rm -f $(OBJEKTI) $(MODUL)