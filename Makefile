#/*******************************************************************************
# * librepfunc - a collection of common functions, classes and tools.
# * See the README file for copyright information and how to reach the author.
# ******************************************************************************/




# reasonable versioning rules:
#   - MAJOR++  -> API-incompatible
#   - MINOR++  -> API-compatible, but new functionality
#   - PATCH++  -> API untouched changes
MAJOR = 1
MINOR = 1
PATCH = 2



LIBRARY = librepfunc.so
LIBRARY_MAJOR = $(LIBRARY).$(MAJOR)
LIBRARY_MINOR = $(LIBRARY_MAJOR).$(MINOR)
LIBRARY_PATCH = $(LIBRARY_MINOR).$(PATCH)
VERSION = $(MAJOR).$(MINOR).$(PATCH)
URL = https://github.com/wirbel-at-vdr-portal/librepfunc






#/******************************************************************************
# * if you prefer verbose non-coloured build messages, remove the '@' here:
# *****************************************************************************/
CXX = @g++
CXXFLAGS  = -g -O3 -fPIC -Wall -Wextra -Werror=overloaded-virtual -Wfatal-errors
DEFINES   = -D_POSIX_C_SOURCE


#/******************************************************************************
# * if you are still running a distro, not beeing able to use all valid
# * standard ASCII Characters (32-126) for package names, and prefer to modify
# * packages instead of fixing your broken distro, you may overwrite the
# * package_name here.
# *****************************************************************************/
package_name ?= $(LIBRARY_PATCH)


#/******************************************************************************
# * color definitions, RST=reset, CY=cyan, MG=magenta, BL=blue, (..)
# *****************************************************************************/
RST=\e[0m
CY=\e[1;36m
MG=\e[1;35m
BL=\e[1;34m
YE=\e[1;33m
RD=\e[1;31m
GN=\e[1;32m

#/******************************************************************************
# * programs, override if on different paths.
# *****************************************************************************/
CD              ?= cd
CP              ?= cp
CHMOD           ?= chmod
GIT             ?= git
INSTALL         ?= install
INSTALL_PROGRAM ?= $(INSTALL) -m 755
INSTALL_DATA    ?= $(INSTALL) -m 644
LN              ?= ln
LN_S            ?= $(LN) -s
LN_SF           ?= $(LN) -sf
LN_SFR          ?= $(LN) -sfr
MAKE            ?= make
MKDIR           ?= mkdir
MKDIR_P         ?= ${MKDIR} -p
PKG_CONFIG      ?= pkg-config
RM              ?= rm
SED             ?= sed
SHELL            = /bin/sh
STRIP           ?= strip
TAR             ?= tar
WGET            ?= wget


#/******************************************************************************
# * directories
# *****************************************************************************/
srcdir           = $(shell pwd)
tmpdir          ?= /tmp
prefix          ?= /usr
sysconfdir       = $(prefix)/etc
includedir       = $(prefix)/include
sharedstatedir   = $(prefix)/com
localstatedir    = $(prefix)/var
datarootdir      = $(prefix)/share
exec_prefix     ?= $(prefix)
bindir           = $(exec_prefix)/bin
sbindir          = $(exec_prefix)/sbin
libexecdir       = $(exec_prefix)/libexec
libdir           = $(exec_prefix)/lib
datadir          = $(datarootdir)
docdir           = $(datarootdir)/doc/$(package_name)
infodir          = $(datarootdir)/info
localedir        = $(datarootdir)/locale
mandir           = $(datarootdir)/man
man1dir          = $(mandir)/man1
man2dir          = $(mandir)/man2
man3dir          = $(mandir)/man3
man4dir          = $(mandir)/man4
man5dir          = $(mandir)/man5
pkgconfigdir     = /usr/lib/pkgconfig

SOURCES  := $(wildcard $(srcdir)/*.cpp)
OBJS      = $(SOURCES:.cpp=.o)
LIBS      =
INCLUDES  = -I$(srcdir)
LDFLAGS   = -shared -lpthread
DLL       = $(LIBRARY:.so=.dll)

define PKG_DATA
prefix=$(prefix)
exec_prefix=$${prefix}
includedir=$${prefix}/include
libdir=$${exec_prefix}/lib

Name: librepfunc
Description: tools library for w_scan_cpp and wirbelscan
URL: $(URL)
Version: $(VERSION)
Libs: -L$${libdir} -lrepfunc
Cflags: -I$${includedir}
endef

%.o: %.cpp
ifeq ($(CXX),@g++)
	@echo -e "${BL} CXX $@${RST}"
endif
	$(CXX) $(CXXFLAGS) -c $(DEFINES) $(INCLUDES) -o $@ $<

all: $(OBJS)
ifeq ($(CXX),@g++)
	@echo -e "${GN} LINK $(LIBRARY_PATCH)${RST}"
endif
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $(LIBRARY_PATCH)
	$(LN_SF) $(LIBRARY_PATCH) $(LIBRARY)

dll: $(OBJS)
ifeq ($(CXX),@g++)
	@echo -e "${GN} LINK $(DLL)${RST}"
endif
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -Wl,--subsystem,windows,--out-implib,$(DLL).a $(OBJS) $(LIBS) -o $(DLL) 

.PHONY: clean Version.h
clean:
	@$(RM) -f $(OBJS) $(LIBRARY) $(LIBRARY_MAJOR) $(LIBRARY_MINOR) $(LIBRARY_PATCH) $(DLL) $(DLL).a librepfunc.pc

install: all
	$(file >librepfunc.pc,$(PKG_DATA))
	$(MKDIR_P) $(DESTDIR)$(libdir)
	$(MKDIR_P) $(DESTDIR)$(includedir)
	$(MKDIR_P) $(DESTDIR)$(docdir)
	$(MKDIR_P) $(DESTDIR)$(man1dir)
	$(MKDIR_P) $(DESTDIR)$(pkgconfigdir)
	$(INSTALL_PROGRAM) $(LIBRARY_PATCH) $(DESTDIR)$(libdir)
	$(INSTALL_DATA) repfunc.h $(DESTDIR)$(includedir)
	$(LN_SFR) $(DESTDIR)$(libdir)/$(LIBRARY_PATCH) $(DESTDIR)$(libdir)/$(LIBRARY_MINOR)
	$(LN_SFR) $(DESTDIR)$(libdir)/$(LIBRARY_MINOR) $(DESTDIR)$(libdir)/$(LIBRARY_MAJOR)
	$(LN_SFR) $(DESTDIR)$(libdir)/$(LIBRARY_MAJOR) $(DESTDIR)$(libdir)/$(LIBRARY)
	$(INSTALL_DATA) COPYING README $(DESTDIR)$(docdir)
	$(INSTALL_DATA) librepfunc.pc $(DESTDIR)$(pkgconfigdir)

#	$(INSTALL_DATA) doc/librepfunc.1 $(DESTDIR)$(man1dir)

uninstall:
	$(RM) -f $(DESTDIR)$(libdir)/$(LIBRARY_PATCH)
	$(RM) -f $(DESTDIR)$(libdir)/$(LIBRARY_MINOR)
	$(RM) -f $(DESTDIR)$(libdir)/$(LIBRARY_MAJOR)
	$(RM) -f $(DESTDIR)$(libdir)/$(LIBRARY)
	$(RM) -f $(DESTDIR)$(includedir)/repfunc.h
	$(RM) -f $(DESTDIR)$(docdir)/COPYING
	$(RM) -f $(DESTDIR)$(docdir)/README
	$(RM) -rf $(DESTDIR)$(docdir)
	$(RM) -f $(DESTDIR)$(man1dir)/librepfunc.1
	$(RM) -f $(DESTDIR)$(pkgconfigdir)/librepfunc.pc



#/******************************************************************************
# * debug
# *****************************************************************************/
printvars:
	@echo "VERSION            = $(VERSION)"
	@echo "LIBRARY            = $(LIBRARY)"
	@echo "CXX                = $(CXX)"
	@echo "CXXFLAGS           = $(CXXFLAGS)"
	@echo "DEFINES            = $(DEFINES)"
	@echo "INCLUDES           = $(INCLUDES)"
	@echo "SOURCES            = $(SOURCES)"
	@echo "OBJS               = $(OBJS)"
	@echo "LIBS               = $(LIBS)"
	@echo "LDFLAGS            = $(LDFLAGS)"
