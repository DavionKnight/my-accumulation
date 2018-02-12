
export ARCH=powerpc
#export PATH=/opt/mips/eldk4.1/usr/bin:/opt/mips/eldk4.1/bin:$PATH
export PATH=/opt/arm/usr/bin:$PATH
export CROSS_COMPILE=arm-linux-

arm-linux-gcc pthread.c -o pthread -lpthread

cp pthread /tftpboot
echo cp pthtread /tftpboot


