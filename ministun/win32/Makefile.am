if OS_WIN
res_obj = $(PACKAGE)-res.o $(PACKAGE)d-res.o
noinst_DATA = $(res_obj)
CLEANFILES = $(res_obj);
endif OS_WIN

.rc.o:
	$(WINDRES) $< $@

SUFFIXES = .rc .o

MAINTAINERCLEANFILES = $(srcdir)/Makefile.in
