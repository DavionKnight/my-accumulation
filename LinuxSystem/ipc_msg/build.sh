#!/bin/bash
#
#  COPYRIGHT NOTICE
#  Copyright (C) 2016 HuaHuan Electronics Corporation, Inc. All rights reserved
#
#  Author       	:Kevin_fzs
#  File Name        	:/home/kevin/works/projects/RtFileSystem/busybox-1.23.2\build-ppc.sh
#  Create Date        	:2016/07/13 14:08
#  Last Modified      	:2016/07/13 14:08
#  Description    	:
#

export PATH=/opt/ppc/eldk4.2/usr/bin:$PATH
#export PATH=/opt/mips/eldk4.1/usr/bin:$PATH

#mips_4KC-gcc send.c -o send
#mips_4KC-gcc recv.c -o recv
ppc_85xxDP-gcc send.c -o send
ppc_85xxDP-gcc recv.c -o recv
cp send /tftpboot/
cp recv /tftpboot/

