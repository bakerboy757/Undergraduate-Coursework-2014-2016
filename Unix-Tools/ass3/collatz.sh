#!/bin/bash
#assign3
#tck13
function step {
   var=$1
   count=0
   while [ $var -ne 1 ]; do
      if [ $((var % 2)) -eq 0 ]; then
         var=$((var/2))
         let count=count+1
      else
         var=$((var*3+1))
 	 let count=count+1
      fi
   done
   echo "The number of Collatz steps for '$1' are $count."
}
if [ $# -eq 0 ]; then
   echo "Incorrect number of arguments";
   exit;
fi
for i;  do
   step $i
done
