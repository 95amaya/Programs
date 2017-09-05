#!/bin/bash
# set -x # echo on

read -p "Apartment number (format: APT-xx): APT-" apt

filename=$(find -name "*@*" | grep -rwl "./" -e "$apt") #r - recursive, w - word match, l - filenames that contain match
# Check if apartment exists in any of the customer files
if [ $(find -name "*@*" | grep -rw "./" -e "$apt" | wc -l) -eq 1 ]; then
    echo "Apartment Exists! $apt"
    # lines=$(cat $filename)
    read -a line_array < $filename
    
    arr=()
    while read line; do
        arr+=( $line )
        echo "line = $line"
    done < $filename
    # myarray()
    # while read line; do
    #     for word in line; do
    #         myarray+=($word)
    #     done
    # done < $filename     
    # echo "${#line_array}"
    declare | grep $filename
    declare | grep $line_array
    declare | grep $arr
    # echo "line_array = ${line_array[@]}"
    # echo "lines_array = ${lines_array[@]}"
    # echo "arr = ${arr[@]}"

    echo "Email: ${arr[0]}" 
    echo "Name: ${arr[1]} ${arr[2]}"  
    echo "Apt: ${arr[3]}"
    echo "Monthly Rent Amount: $'${arr[4]}'"
    echo "Next Due Date: ${arr[6]}"
else
    echo "Error: apartment number not found"
fi