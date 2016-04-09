#!/bin/bash
#assign6
#tck13
getArray(){
  array=()
  while IFS= read -r line
  do
    array+=("$line")
  done < "$1"
}

analyze(){
  if [ $size -gt ${#e} ]; then
     return
  fi
  if [[ $e =~ $regex ]]
  then
    echo "$e"
  fi
}

i=0
word=$2
size=${#word}

if [ $# -ne 2 ]; then
   echo "Incorrect number of arguments";
   exit;
fi

while [ $i -lt $size ]; do
  regex="$regex${2:$i:1}.*"
  #echo "${word:$i:1}"
  let i=i+1
done

getArray $1

for e in "${array[@]}"
do
  analyze $e $word $regex $size
done
