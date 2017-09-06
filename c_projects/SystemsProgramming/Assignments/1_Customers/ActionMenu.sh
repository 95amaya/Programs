#!/bin/bash
go=0
while [ $go ]; do
    echo "Enter one of the following actions or press CTRL-D to exit."
    echo "C - create a customer file"
    echo "P - accept a customer payment"
    echo "F - find customer by apartment number"

    if ! read action; then
        break;
    fi
    # echo "Action = $action"
    case "$action" in
        [Cc]) ./CreateAction.sh;; # Run CreateAction.sh
        [Pp]) ./PaymentAction.sh;; # Run PaymentAction.sh
        [Ff]) ./FindAction.sh;; # Run FindAction.sh
        *)   echo -e "Error: invalid action value\n";; # Redisplay action menu
    esac
done