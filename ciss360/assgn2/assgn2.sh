#!/bin/bash

displayProcesses () {
    clear
    echo "Press any key to quit"
    while [ true ] ; do
        read -t 6 -n 1
        if [ $? = 0 ] ; then
            exit ;
        else
            clear
            echo '============================================'
            procList=`ls /proc | grep [[:digit:]] | sort -n`
            for process in $procList 
            do  
                processName=`head /proc/$process/status -n 1 2> /dev/null`
                if [ $? = 0 ]; then
                    printf "PID: %s \t%s\n" "$process" "$processName"
                fi
            done
            echo '============================================'
            echo "Press any key to quit"
        fi
    done
}

watchProcess () {
    clear
    echo "Press any key to quit"
    while [ true ] ; do
        read -t 6 -n 1
        if [ $? = 0 ] ; then
            exit ;
        else
            clear
            echo '============================================'
            procList=`ls /proc | grep [[:digit:]] | sort -n`
            for process in $procList 
            do  
                processName=`head /proc/$process/status -n 1 2> /dev/null`
                if [ $? = 0 ]; then
                    printf "PID: %s \t%s\n" "$process" "$processName"
                fi
            done
            echo '============================================'
            echo "Press any key to quit"
        fi
    done
}

parseOptions () {
    break
}

watchProcess