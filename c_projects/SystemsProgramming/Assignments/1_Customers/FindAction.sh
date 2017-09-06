#!/bin/bash
# set -x # echo on

read -p "Apartment number (format: APT-xx): APT-" apt

# Check if apartment exists in any of the customer files
if [ $(grep -rw "./Data" -e "$apt" | wc -l) -eq 1 ]; then
# if [[ $(wc -l < "${filename[*]}") -eq 1 ]]; then # Having trouble with
    filename=$(grep -rwl "./Data" -e "$apt") #r - recursive, w - word match, l - filenames that contain match
    items=()
    while read -r line || [[ -n "$line" ]]; do # Deals with file that does not have \n at end to get last line
        items+=( $line )
        # echo "line = $line"
    done < $filename

    # declare | grep $filename
    # declare | grep $line_array
    # declare | grep 'items'
    # echo "line_array = ${line_array[@]}"
    # echo "lines_array = ${lines_array[@]}"
    # echo "items = ${items[@]}"

    # Print relevant information
    echo -e "\n-----Customer------"
    echo "Email: ${items[0]}" 
    echo "Name: ${items[1]} ${items[2]}"  
    echo "Apt: ${items[3]}"
    echo "Monthly Rent Amount: \$${items[4]}"
    echo -e "Next Due Date: ${items[6]}\n"
else
    echo -e "Error: apartment number not found\n"
    # Do nothing
fi