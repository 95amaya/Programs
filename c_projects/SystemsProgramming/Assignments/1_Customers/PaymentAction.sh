#!/bin/bash
read -p "Email: " email
read -p "Payment Amount: $" amount

if [ $(find -name "$email" | wc -l) -eq 1 ]; then # gt 0 ? eq 1
    echo "Customer Exists!"
else
    echo "Error: customer not found"
fi