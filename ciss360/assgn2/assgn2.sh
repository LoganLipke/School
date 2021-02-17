#!/bin/bash

displayProcesses () {
    clear
    echo "Press any key to quit"
    while [ true ] ; do
        read -t 10 -n 1
        if [ $? = 0 ] ; then
            exit ;
        else
            echo '===================================='
            clear
            procList=`ls /proc | grep [[:digit:]]`
            for process in $procList
            do  
                processName=`head /proc/$process/status -n 1`
                printf "PID: %s Name: %s\n" $process $processName
                
            done
            echo "Press any key to quit"
        fi
    done
}

watchProcess () {
    break
}

parseOptions () {
    break
}

displayProcesses