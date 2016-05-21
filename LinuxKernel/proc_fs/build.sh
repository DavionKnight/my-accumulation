#!/bin/sh
export ARCH=powerpc
export PATH=/home/kevin/Documents/ppc-tools/usr/bin:/opt/eldk42/bin:$PATH
export CROSS_COMPILE=ppc_85xxDP-

make

