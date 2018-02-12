#!/bin/bash

export PATH=/opt/arm/usr/bin:$PATH

arm-linux-gcc endian.c -o endian-arm

cp endian-arm /tftpboot/


