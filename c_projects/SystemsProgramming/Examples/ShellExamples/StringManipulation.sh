#!/bin/bash
printenv
echo "your current directory is $(pwd)"
echo "your home directory is $(eval echo "~$USER")"

# Take sum of paramaters X 2
ARGS=("$@")
sum=0
echo "Total Number of parameters = ${#ARGS[@]}"
((paramAns = ${#ARGS[@]} * 2))
echo "Paramater length X 2 = $paramAns"

TRform=`tr " " + <<< "${ARGS[@]}"`
# TRform=$(tr " " + <<< ${ARGS[@]})
echo "TR Format = $TRform"
Args1=${ARGS[@]}
echo "String Format = ${Args1// /+}"
# Set Internal Field Seperator to "+"
IFS=+
# Get Arguments in Summation format (ex. $1+$2+etc...) 
# [*] uses IFS formatting generated string from arrary
sumFormat="${ARGS[*]}"
echo "IFS Format=$sumFormat"
# Plug sumFormat into calculator to get summation using here string <<< command
sum=`bc <<< "$sumFormat"`
echo "Total Summation = $sum"
#### Set the IFS to | ####
IFS='|'

echo "Command-Line Arguments Demo"

echo "*** All args displayed using \$@ positional parameter ***"
echo "$@"        #*** double quote added ***#

echo "*** All args displayed using \$* positional parameter ***"
echo "$*"        #*** double quote added ***#
