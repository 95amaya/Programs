#!/bin/bash
# check for too few arguments, be careful of the spacing
# if [ $# -lt 1 ]; then
#     echo "usage: simpWhile number"
#     echo "       where number is a number"
#     exit 1
# fi
# sum=0
# index=$1
# # the spacing is important
# while [ $index -gt 0 ]; do
#     echo -ne "$index "
#     if [ $index -ne 1 ]; then
#         echo -ne "+ "
#     fi
#     ((sum=sum+index))
#     ((index=index-1))
# done
# echo -ne "\n = $sum\n"

echo "Enter one of the following actions or press CTRL-D to exit."
echo "C - create a customer file"
echo "P - accept a customer payment"
echo "F - find customer by apartment number"

read action
# echo "Action = $action"
case "$action" in
    [Cc]) ./CreateAction.sh;; # Run CreateAction.sh
    [Pp]) ./PaymentAction.sh;; # Run PaymentAction.sh
    [Ff]) ./FindAction.sh;; # Run FindAction.sh
    *)   echo "Error: invalid action value"
         exit 1;; # Failed execution
esac
