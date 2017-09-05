#!/bin/bash
set -x # echo on

read -p "Apartment number (format: APT-xx): APT-" apt

filename=$(find -name "*@*" | grep -rwl "./" -e "$apt") #r - recursive, w - word match, l - filenames that contain match

# Check if apartment exists in any of the customer files
if [ $(find -name "*@*" | grep -rw "./" -e "$apt" | wc -l) -eq 1 ]; then
    items=()
    while read line; do
        items+=( $line )
        # echo "line = $line"
    done < $filename

    # declare | grep $filename
    # declare | grep $line_array
    # declare | grep $items
    # echo "line_array = ${line_array[@]}"
    # echo "lines_array = ${lines_array[@]}"
    # echo "items = ${items[@]}"

    # Print relevant information
    echo "Email: ${items[0]}" 
    echo "Name: ${items[1]} ${items[2]}"  
    echo "Apt: ${items[3]}"
    echo "Monthly Rent Amount: \$${items[4]}"
    echo "Next Due Date: ${items[6]}"
else
    echo "Error: apartment number not found"
fi