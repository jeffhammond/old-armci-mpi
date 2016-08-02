#! /bin/sh

# Exit on error
set -ev

MPI_IMPL="$1"

case "$MPI_IMPL" in
    mpich)
        if [ "${TRAVIS_OS_NAME}" = "linux" ] ; then
            export PATH=$HOME/deps/mpich/bin:$PATH
        fi
        #mpichversion
        mpicc -show
        ;;
    openmpi)
        if [ "${TRAVIS_OS_NAME}" = "linux" ] ; then
            export PATH=$HOME/deps/open-mpi/bin:$PATH
        fi
        #ompi_info --arch --config
        mpicc --showme:command
        ;;
esac

# Environment variables
export CFLAGS="-std=c99"
export MPICC="mpicc"

# Configure and build
./autogen.sh
./configure --disable-static --enable-win-allocate --prefix=/tmp

# Run unit tests
export ARMCI_VERBOSE=1
make
make checkprogs
make check

# Verify that installation works
make install
