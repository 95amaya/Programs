#!/bin/bash
read -p "Email: " email
read -p "Payment Amount: $" amount

if [ $(find -name "$email" | wc -l) -eq 1 ]; then # gt 0 ? eq 1
    echo "Customer Exists!"
    items=()
    items+=($(sed '2q;d' $email)) # deserializes 2nd line into an array
    # declare | grep 'items'
    ((items[2] = ${items[2]} + $amount)) # Convert to integer and add to balance
    # declare | grep 'items'
    # replace the 2nd line with the new 2nd line and updated account balance
    sed -i "2s/.*/${items[*]}/" $email
    # sed "2s/.*/${items[*]}/" $email > dummy.txt # need asterick

    # slower way to do it using array slicing
    # items=()
    # while read line; do
    #     items+=( $line )
    #     # echo "line = $line"
    # done < $email
    # declare | grep 'items'
    # # Add amount to payment
    # ((newBalance = ${items[5]} + $amount))
    # echo "$newBalance"
    # declare | grep '$items'
    # echo ${items[@]:0:3} #> dummy.txt
    # echo "${items[@]:3:2} $newBalance ${items[6]}" #>> dummy.txt

else
    echo "Error: customer not found"
fi