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
    process=/proc/$1
    if test -d "$process"; then
        printf "Watching process %s\n" $1
        echo "Press any key to quit"
        while [ true ] ; do
            read -t 6 -n 1
            if [ $? = 0 ] ; then
                exit ;
            else
                clear
                echo '============================================'
                cat $process/status
                echo '============================================'
                echo "Press any key to quit"
            fi
        done
    else
        echo "Process not found, quitting"
    fi

}

printHelp () {
    echo "--help, -h      | Display this help output."
    echo "--pname         | Watch process specified by name. If multiple processes with the same name exist, the first found will be shown."
    echo "--pid           | Watch process specified by pid"
    echo "--displayProcs  | Displays all current process ids and their names"
}

parseOptions () {
    if [ "$1" == "--help" ] || [ "$1" == "-h" ]; then
        printHelp
    elif [ "$1" == "--pname" ]; then
        found=0
        procList=`ls /proc | grep [[:digit:]] | sort -n`
        for process in $procList 
        do  
            foundName=`head /proc/$process/status -n 1 2> /dev/null`
            if [ ${foundName:5} == "$2" ]; then
                watchProcess $process
                found=1
            fi
        done
        if [ $found == 0 ]; then
            printf "Process with name %s was not found\n" $2
        fi

    elif [ "$1" == "--pid" ] && [ $2 > 0 ]; then
        watchProcess $2
    elif [ "$1" == "--displayProcs" ]; then
        displayProcesses
    else
        echo "Command option not known. Available options: "
        printHelp
    fi
}


parseOptions $@