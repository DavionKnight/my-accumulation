#!/bin/bash

if [ $# != 2 ];then
    echo "sh top_cpu.sh stationservice 10"
    exit
fi

PID=`adb shell pidof $1`
TIMEOUT=$(($2*60))
echo -e "process:$1 pid:$PID test time:$2min\n"

FILE=top.txt

#adb shell "top -b -H -n$TIMEOUT -d1 -p $PID" > $FILE
#ps -AT -O pri,sch,name| grep stationservice 

thread_all=`cat $FILE | grep $1 | awk -F " " '{print $1}'|sort -ru`
#echo $thread_all

echo ""
calculate() {
    COUNT=0
    COUNT=`cat $FILE | grep -w $1 | wc -l`
    VAL=`cat $FILE | grep $1 | awk -F " " '{print $9}'`
    #echo val=$VAL
    T=0.0
    for i in $VAL
    do
        T=`echo "$T+$i"|bc`
    done
    name=`cat $FILE | grep $1 | awk -F " " 'NR==1{print $12}'`
    echo ===$T,$COUNT
    AV=`echo "scale=2;$T/$COUNT"|bc|awk '{printf "%.2f", $0}'`
    echo "thread $1:$name\ttotal:$T\tcount:$COUNT\taverage:$AV\n"
}

for i in $thread_all
do
    calculate $i
done


