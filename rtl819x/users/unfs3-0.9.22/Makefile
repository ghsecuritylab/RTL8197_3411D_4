#CC = gcc
#CFLAGS += -g -O2 -Wall -W -D_GNU_SOURCE 
CFLAGS = -Os -pipe -mno-branch-likely -mips32 -mtune=mips32 -fno-caller-saves   -msoft-float   -Wall -W -D_GNU_SOURCE

#INSTALL = /usr/bin/install -c
#INSTALL_DATA = ${INSTALL} -m 644
VERSION = 0.9.22
RM = rm -f
MAKE = make

SOURCES = attr.c daemon.c error.c fd_cache.c fh.c fh_cache.c locate.c \
          md5.c mount.c nfs.c password.c readdir.c user.c xdr.c winsupport.c
OBJS = attr.o daemon.o error.o fd_cache.o fh.o fh_cache.o locate.o \
       md5.o mount.o nfs.o password.o readdir.o user.o xdr.o winsupport.o
CONFOBJ = Config/lib.a
EXTRAOBJ = 
#LDFLAGS =   -lfl
EXEEXT = 
LIBRPC = ../librpc-0.9.32-rc2/librpc.so
#prefix = /usr/local
#exec_prefix = ${prefix}
#sbindir = ${exec_prefix}/sbin
#mandir = ${datarootdir}/man
#datarootdir = ${prefix}/share

SUBDIRS = Config 

DESTDIR =

all: subdirs unfsd$(EXEEXT)

unfsd$(EXEEXT): $(OBJS) $(CONFOBJ) $(EXTRAOBJ)
	$(CC) -o $@ $(OBJS) $(CONFOBJ) $(EXTRAOBJ) $(LDFLAGS) $(LIBRPC)

subdirs:
	for i in $(SUBDIRS); do cd $$i; $(MAKE) all; cd ..; done

#install: unfsd$(EXEEXT)
#	$(INSTALL) -d $(DESTDIR)$(sbindir)
#	$(INSTALL) -d $(DESTDIR)$(mandir)/man7
#	$(INSTALL) -d $(DESTDIR)$(mandir)/man8
#	$(INSTALL) unfsd$(EXEEXT) $(DESTDIR)$(sbindir)/unfsd$(EXEEXT)
#	$(INSTALL_DATA) Extras/tags.7 $(DESTDIR)$(mandir)/man7/tags.7
#	$(INSTALL_DATA) unfsd.8       $(DESTDIR)$(mandir)/man8/unfsd.8

# Not installed by default, since it installs files outside prefix
#install-init: unfsd.init
#	$(INSTALL) -d $(DESTDIR)/etc/init.d
#	$(INSTALL) unfsd.init $(DESTDIR)/etc/init.d/unfsd

#install-strip: install
#	strip $(DESTDIR)$(sbindir)/unfsd$(EXEEXT)

#uninstall:
#	$(RM) $(DESTDIR)$(sbindir)/unfsd$(EXEEXT)
#	$(RM) $(DESTDIR)$(mandir)/man7/tags.7
#	$(RM) $(DESTDIR)$(mandir)/man8/unfsd.8

clean:
	for i in $(SUBDIRS); do cd $$i; $(MAKE) clean; cd ..; done
	$(RM) $(OBJS)
	$(RM) unfsd$(EXEEXT)
	$(RM) $(LIBRPC)
	$(RM) unfs3-$(VERSION).tar.gz

distclean: clean
	for i in $(SUBDIRS); do cd $$i; $(MAKE) distclean; cd ..; done
	$(RM) Makefile config.h
	$(RM) config.log config.status

#maintainer-clean: distclean
#	$(RM) config.h.in configure
#	$(RM) -rf autom4te.cache

dep: $(SOURCES)
	for i in $(SUBDIRS); do cd $$i; $(MAKE) dep; cd ..; done
	$(CC) $(CFLAGS) -MM $(SOURCES) >> Makefile

.PHONY: dist unfs3-$(VERSION).tar.gz

dist: unfs3-$(VERSION).tar.gz

romfs:
	$(ROMFSINST) /bin/unfsd$(EXEEXT)
	@cp ./exports $(DIR_ROMFS)/etc/
	@cp $(LIBRPC) $(DIR_ROMFS)/lib/

unfs3-$(VERSION).tar.gz:
	rm -rf /tmp/unfs3-make-dist-dir
	mkdir /tmp/unfs3-make-dist-dir
	ln -sf `pwd` /tmp/unfs3-make-dist-dir/unfs3-$(VERSION)
	(cd /tmp/unfs3-make-dist-dir; \
	 tar zcf unfs3-$(VERSION)/unfs3-$(VERSION).tar.gz \
	 unfs3-$(VERSION)/fd_cache.c \
	 unfs3-$(VERSION)/md5.h \
	 unfs3-$(VERSION)/xdr.h \
	 unfs3-$(VERSION)/attr.c \
	 unfs3-$(VERSION)/README \
	 unfs3-$(VERSION)/backend.h \
	 unfs3-$(VERSION)/password.c \
	 unfs3-$(VERSION)/README.nfsroot \
	 unfs3-$(VERSION)/error.c \
	 unfs3-$(VERSION)/winsupport.c \
	 unfs3-$(VERSION)/fh_cache.h \
	 unfs3-$(VERSION)/user.c \
	 unfs3-$(VERSION)/unfs3.spec \
	 unfs3-$(VERSION)/winsupport.h \
	 unfs3-$(VERSION)/readdir.h \
	 unfs3-$(VERSION)/nfs.c \
	 unfs3-$(VERSION)/configure \
	 unfs3-$(VERSION)/xdr.c \
	 unfs3-$(VERSION)/install-sh \
	 unfs3-$(VERSION)/mount.c \
	 unfs3-$(VERSION)/password.h \
	 unfs3-$(VERSION)/Extras/Makefile.in \
	 unfs3-$(VERSION)/Extras/cluster.c \
	 unfs3-$(VERSION)/Extras/tags.7 \
	 unfs3-$(VERSION)/Extras/cluster.h \
	 unfs3-$(VERSION)/NEWS \
	 unfs3-$(VERSION)/CREDITS \
	 unfs3-$(VERSION)/aclocal.m4 \
	 unfs3-$(VERSION)/daemon.h \
	 unfs3-$(VERSION)/doc/TODO \
	 unfs3-$(VERSION)/doc/README.win \
	 unfs3-$(VERSION)/doc/kirch1.txt \
	 unfs3-$(VERSION)/doc/passwords.txt \
	 unfs3-$(VERSION)/unfsd.8 \
	 unfs3-$(VERSION)/Makefile.in \
	 unfs3-$(VERSION)/unfsd.init \
	 unfs3-$(VERSION)/backend_win32.h \
	 unfs3-$(VERSION)/indent-all \
	 unfs3-$(VERSION)/backend_unix.h \
	 unfs3-$(VERSION)/nfs.h \
	 unfs3-$(VERSION)/locate.c \
	 unfs3-$(VERSION)/BRANCHES \
	 unfs3-$(VERSION)/fd_cache.h \
	 unfs3-$(VERSION)/daemon.c \
	 unfs3-$(VERSION)/error.h \
	 unfs3-$(VERSION)/contrib/nfsotpclient/README \
	 unfs3-$(VERSION)/contrib/nfsotpclient/mountclient \
	 unfs3-$(VERSION)/contrib/nfsotpclient/mountclient/__init__.py \
	 unfs3-$(VERSION)/contrib/nfsotpclient/mountclient/mountpacker.py \
	 unfs3-$(VERSION)/contrib/nfsotpclient/mountclient/mountconstants.py \
	 unfs3-$(VERSION)/contrib/nfsotpclient/mountclient/mounttypes.py \
	 unfs3-$(VERSION)/contrib/nfsotpclient/nfsotpclient.py \
	 unfs3-$(VERSION)/contrib/nfsotpclient/rpc.py \
	 unfs3-$(VERSION)/contrib/rpcproxy/rpcproxy \
	 unfs3-$(VERSION)/LICENSE \
	 unfs3-$(VERSION)/fh.h \
	 unfs3-$(VERSION)/fh.c \
	 unfs3-$(VERSION)/Config/exports.y \
	 unfs3-$(VERSION)/Config/exports.l \
	 unfs3-$(VERSION)/Config/exports.h \
	 unfs3-$(VERSION)/Config/Makefile.in \
	 unfs3-$(VERSION)/locate.h \
	 unfs3-$(VERSION)/md5.c \
	 unfs3-$(VERSION)/fh_cache.c \
	 unfs3-$(VERSION)/config.h.in \
	 unfs3-$(VERSION)/attr.h \
	 unfs3-$(VERSION)/configure.ac \
	 unfs3-$(VERSION)/mount.h \
	 unfs3-$(VERSION)/readdir.c \
	 unfs3-$(VERSION)/user.h)
	rm -rf /tmp/unfs3-make-dist-dir

# automatically generated dependencies follow
