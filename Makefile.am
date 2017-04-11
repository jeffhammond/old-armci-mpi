#
# Copyright (C) 2010. See COPYRIGHT in top-level directory.
#

ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -I$(top_srcdir)/src

EXTRA_DIST = VERSION

lib_LTLIBRARIES = libarmci.la

# Needed to connect with the GA build system
noinst_LTLIBRARIES = libarmcii.la

libarmci_la_SOURCES = src/common/conflict_tree.c   \
                      src/common/debug.c           \
                      src/common/groups.c          \
                      src/common/init_finalize.c   \
                      src/common/internals.c       \
                      src/common/malloc.c          \
                      src/common/message.c         \
                      src/common/message_gop.c     \
                      src/common/mutex.c           \
                      src/common/mutex_hdl_queue.c \
                      src/common/parmci.c          \
                      src/common/topology.c        \
                      src/common/util.c            \
                      src/common/value_ops.c

if USE_MPI2
libarmci_la_SOURCES += src/mpi2/buffer.c        \
                       src/mpi2/gmr.c           \
                       src/mpi2/onesided.c      \
                       src/mpi2/onesided_nb.c   \
                       src/mpi2/rmw.c           \
                       src/mpi2/strided.c       \
                       src/mpi2/strided_nb.c    \
                       src/mpi2/vector.c        \
                       src/mpi2/vector_nb.c
else
libarmci_la_SOURCES += src/mpi3/buffer.c        \
                       src/mpi3/gmr.c           \
                       src/mpi3/gmr-extras.c    \
                       src/mpi3/onesided.c      \
                       src/mpi3/onesided_nb.c   \
                       src/mpi3/rmw.c           \
                       src/mpi3/strided.c       \
                       src/mpi3/strided_nb.c    \
                       src/mpi3/vector.c        \
                       src/mpi3/vector_nb.c
endif

libarmci_la_LDFLAGS = -version-info $(libarmci_abi_version)

libarmcii_la_SOURCES = $(libarmci_la_SOURCES)
libarmcii_la_LDFLAGS = $(libarmci_abi_version)

include_HEADERS = src/armci.h src/armcix.h src/message.h src/mp3.h src/armciconf.h
noinst_HEADERS = src/armci_internals.h src/conflict_tree.h src/debug.h src/gmr.h

bin_PROGRAMS =
check_PROGRAMS = 
TESTS = 
XFAIL_TESTS = 

MPIEXEC = mpiexec -n 2
LOG_COMPILER=$(MPIEXEC)

include benchmarks/Makefile.mk
include tests/Makefile.mk

.PHONY: checkprogs
checkprogs: $(check_PROGRAMS)
