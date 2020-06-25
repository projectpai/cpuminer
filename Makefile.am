
if WANT_JANSSON
JANSSON_INCLUDES= -I$(top_srcdir)/compat/jansson
else
JANSSON_INCLUDES=
endif

EXTRA_DIST	= example-cfg.json cfg-regtest.json nomacro.pl

SUBDIRS		= compat

bin_PROGRAMS	= minerd

dist_man_MANS	= minerd.1

minerd_SOURCES	= elist.h miner.h compat.h \
		  cpu-miner.c util.c \
		  sha2.c scrypt.c \
		  sha3/tiny_sha3.h sha3/tiny_sha3.c sha3/sha3.c

if USE_ASM
if ARCH_x86
minerd_SOURCES += sha2-x86.S scrypt-x86.S
endif
if ARCH_x86_64
minerd_SOURCES += sha2-x64.S scrypt-x64.S
endif
if ARCH_ARM
minerd_SOURCES += sha2-arm.S scrypt-arm.S
endif
if ARCH_PPC
minerd_SOURCES += sha2-ppc.S scrypt-ppc.S
endif
endif

minerd_LDFLAGS	= $(PTHREAD_FLAGS)
minerd_LDADD	=  @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@
minerd_CFLAGS	= -fno-strict-aliasing
minerd_CPPFLAGS	= $(JANSSON_INCLUDES) $(PTHREAD_FLAGS)

if !HAVE_WINDOWS
minerd_LDADD	+= @LIBCURL_LIBS@
minerd_CPPFLAGS	+= @LIBCURL_CFLAGS@ @LIBCURL_CPPFLAGS@
endif
