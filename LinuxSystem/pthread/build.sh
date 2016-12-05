
export ARCH=powerpc
export PATH=/opt/mips/eldk4.1/usr/bin:/opt/mips/eldk4.1/bin:$PATH
export CROSS_COMPILE=mips_4KC-

mips_4KC-gcc pthread.c -o pthread -lpthread

cp pthread /tftpboot
echo cp pthtread /tftpboot


