#!/bin/sh
#Tyler Kelly
#COP3353
#Assignment4
#April21
    #checks to ensure one argument entered
    if [ $# -ne 1 ]
    then
       echo "Please provide one directory to search"
       echo "Example usage: assignment4.sh directory_name"
       exit 1
    fi
    #checks to ensure is direcotry
    if [ ! -d "$1" ]
    then
       echo "$1: Invalid Directory. Aborting Script."
       exit 1
    fi
    #go to the desired directory
    cd "$1"
    #variables needed
    read=0
    write=0
    exe=0
    numFiles=0
    numDir=0
    #forloop that counts through both files and
    #directories when it comes to determing if 
    #r, w, or x and adds up results
    for filename in *
    do
    if [ -r "$filename" ]
    then
       read=`expr $read + 1`
    fi
    if [ -x "$filename" ]
    then
       exe=`expr $exe + 1`
    fi
    if [ -w "$filename" ]
    then
       write=`expr $write + 1`
    fi
    if [ -f "$filename" ]
    then
       numFiles=`expr $numFiles + 1`
    fi
    done
    #counts how many directories there are
    for dir in */
    do
    if [ -d "$dir" ]
    then
       numDir=`expr $numDir + 1`
    fi
    done
    #adds up dir and files
    total=`expr $numDir + $numFiles`
    #prints to screen
    echo "In the directory $1"
    echo "  Number of directories     : $numDir"
    echo "  Number of files           : $numFiles"
    echo "  Number of readable items  : $read"
    echo "  Number of writable        : $write"
    echo "  Number of executable items: $exe"
    echo "-------------------------------"
    echo "Total number of items: $total"
