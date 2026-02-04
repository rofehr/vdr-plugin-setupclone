PLUGIN = setupclone

OBJS = setupclone.o menu_plugins.o menu_setup.o

VDRDIR ?= /usr/include/vdr
LIBDIR ?= /usr/lib/vdr/plugins

CXX = g++
CXXFLAGS := -fPIC -Wall -Wextra
INCLUDES += -I$(VDRDIR)

all: libvdr-$(PLUGIN).so

libvdr-$(PLUGIN).so: $(OBJS)
	$(CXX) -shared $(OBJS) -o $@

install: libvdr-$(PLUGIN).so
	install -D libvdr-$(PLUGIN).so $(LIBDIR)/libvdr-$(PLUGIN).so

clean:
	rm -f *.o *.so
