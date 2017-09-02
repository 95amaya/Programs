read -p "Apartment number (format: APT-xx): APT-" apt

# Check if apartment exists in any of the customer files
if [ $(find -name "*@*" | grep -rw "./" -e "$apt" | wc -l) -eq 1 ]; then
    echo "Apartment Exists!"
    # echo "Email: $email" 
    # echo "Name: $firstname $lastname"  
    # echo "Apt: APT-" apt
    # echo "Monthly Rent Amount: $" monthlyrent
    # echo "Next Due Date: " duedate
else
    echo "Error: apartment number not found"
fi