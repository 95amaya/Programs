#!/bin/bash
read -p "Email: " email
read -p "Full Name (First Last): " firstname lastname
read -p "Apt: APT-" apt
read -p "Monthly Rent Amount: $" monthlyrent
read -p "Next Due Date: " duedate
balance=0

# See if customer exists
if [ $(find -name "$email" | wc -l) -eq 1 ]; then # gt 0 ? eq 1
    echo "Error: customer already exists"
    exit 1
fi

# Create Customer File
echo "Creating Customer File..."
echo "$email $firstname $lastname" > $email # Redirect to file
echo "APT-$apt $monthlyrent $balance $duedate" >> $email # Append to file

# echo completion
echo -e "\nCreated File $email with contents:"
echo "$email $firstname $lastname"
echo "APT-$apt $monthlyrent $balance $duedate"