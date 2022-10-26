#!/bin/bash

if (( $# < 2 ));then
    echo "sh top_cpu.sh -p stationservice 10"
    echo "sh top_cpu.sh -t stationservice 10"
    echo "sh top_cpu.sh -p top.txt"
    exit
fi

FILE=top.txt
PROCESS=stationservice

if [ $# = 2 ];then
    if [ -f $2 ];then
        FILE=$2
    else
        echo "sh top_cpu.sh -p stationservice 10"
        echo "sh top_cpu.sh -t stationservice 10"
        echo "sh top_cpu.sh -p top.txt"
        exit
    fi
elif [ $# = 3 ];then
    P_T=$1
    PID=`adb shell pidof $2`
    TIMEOUT=$(($3*60))
    PROCESS=$2
    echo "process:$2 pid:$PID testTime:$3min"
    if [ $P_T = "-t" ];then
        adb shell "top -b -H -n$TIMEOUT -d1 -p $PID" > $FILE
    else
        adb shell "top -b -n$TIMEOUT -d1 -p $PID" > $FILE
    fi
else
    echo "sh top_cpu.sh stationservice 10"
    exit
fi

echo ""
TOTAL_CPU=0
calculate_t() {
    COUNT=`cat $FILE | grep -w $1 | wc -l`
    VAL=`cat $FILE | grep $1 | awk -F " " '{print $9}'`
    #echo val=$VAL
    T=0.0
    COUNT_REJECT0=0
    MAX=0.0
    MIN=0.0
    for i in $VAL
    do
        #point num compare
        if [ `expr $MAX \> $i` -eq 0 ];then
            MAX=$i
        fi
        if [ `expr $MIN \< $i` -eq 0 ];then
            MIN=$i
        fi

        T=`echo "$T+$i"|bc`
        if [ $i != 0.0 ];then
            COUNT_REJECT0=`echo "$COUNT_REJECT0+1"|bc`
            #echo $i,$COUNT_REJECT0
        fi
    done
    name=`cat $FILE | grep $1 | awk -F " " 'NR==1{print $12}'`
    AV=`echo "scale=2;$T/$COUNT"|bc|awk '{printf "%.2f", $0}'`
    echo "thread $1:$name"
    echo "    total:$T"
    echo "    MAX:$MAX"
    echo "    MIN:$MIN"
    echo "    count:$COUNT                average(include 0):$AV"
    if [ $COUNT_REJECT0 != 0 ];then
        AV1=`echo "scale=2;$T/$COUNT_REJECT0"|bc|awk '{printf "%.2f", $0}'`
        echo "    count:$COUNT(reject 0):$COUNT_REJECT0    average(reject 0):$AV1"
        TOTAL_CPU=`echo "$TOTAL_CPU+$AV1"|bc`
    fi
    echo ""
}

if [ $P_T = "-t" ];then
    thread_all=`cat $FILE | grep $PROCESS | awk -F " " '{print $1}'|sort -u`
    echo $thread_all

    for i in $thread_all
    do
        calculate_t $i
    done
else
    COUNT=0
    process_all=`cat $FILE | grep $PROCESS | awk -F " " '{print $9}'`
    echo $process_all

    for i in $process_all
    do
        if [ $i != 0.0 ];then
            TOTAL_CPU=`echo "$TOTAL_CPU+$i"|bc`
            COUNT=`echo "$COUNT+1"|bc`
        fi
    done
    AV=`echo "scale=2;$TOTAL_CPU/$COUNT"|bc|awk '{printf "%.2f", $0}'`
    echo "AV:$AV"

fi
echo "TOTAL:$TOTAL_CPU"

