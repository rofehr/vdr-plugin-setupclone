PLUGIN = setupclone

OBJS = setupclone.o menu_plugins.o menu_setup.o

LIBDIR ?= /usr/lib/vdr/plugins

PKGCFG = $(if $(VDRDIR),$(shell pkg-config --variable=$(1) $(VDRDIR)/vdr.pc),$(shell PKG_CONFIG_PATH="$$PKG_CONFIG_PATH:../../.." pkg-config --variable=$(1) vdr))
LIBDIR = $(call PKGCFG,libdir)
LOCDIR = $(call PKGCFG,locdir)
PLGCFG = $(call PKGCFG,plgcfg)
CFGDIR = $(call PKGCFG,configdir)

APIVERSION = $(call PKGCFG,apiversion)

### Allow user defined options to overwrite defaults:

-include $(PLGCFG)


CXX = g++
CXXFLAGS := -fPIC -Wall -Wextra

all: libvdr-$(PLUGIN).so

libvdr-$(PLUGIN).so: $(OBJS)
	$(CXX) -shared $(OBJS) -o $@

install: libvdr-$(PLUGIN).so
	install -D libvdr-$(PLUGIN).so $(LIBDIR)/libvdr-$(PLUGIN).so

clean:
	rm -f *.o *.so
