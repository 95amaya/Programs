#!/bin/bash
read -p "Email: " email
read -p "Full Name (First Last): " firstname lastname
read -p "Apt: APT-" apt
read -p "Monthly Rent Amount: $" monthlyrent
read -p "Next Due Date: " duedate
balance=0

# See if customer exists, look in Data directory
if [ $(find ./Data -name "$email" | wc -l) -eq 1 ]; then # gt 0 ? eq 1
    echo -e "Error: customer already exists\n"
    # Do nothing
else
    # Create Customer File
    # echo "Creating Customer File..."
    echo "$email $firstname $lastname" > $email # Redirect to file
    echo "$apt $monthlyrent $balance $duedate" >> $email # Append to file

    # echo completion
    echo -e "\n------ New Customer ------"
    echo "$email $firstname $lastname"
    echo -e "$apt $monthlyrent $balance $duedate\n"
fi