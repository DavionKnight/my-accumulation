#!/bin/bash

export PATH=/opt/mips/eldk4.1/usr/bin:$PATH

mips_4KC-gcc endian.c -o endian-mips

cp endian-mips /tftpboot/


