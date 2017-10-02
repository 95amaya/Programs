#!/bin/bash
# Assignment 4
# 10/1/2017
# usage: bash p4.bash [DATE: mm/dd/yyyy]

if [ $# -ne 1 ]; then
  echo "usage: $0 [DATE: mm/dd/yyyy]"
  exit 1
fi

# duedate=${1//\//\\\/} # Convert date to mm\/dd\/yyyy for sed
duedate=$1

(cd $PWD/SedScripts && cd ../ ) 2>/dev/null || mkdir $PWD/SedScripts # check if directory already exists

# Process customers who have not paid amount owed by generating sed scripts
gawk -v date="$duedate" -f p4.awk p4Customer.txt 2>/dev/null # redirect stderr to suppress warning message

cd $PWD/Emails 2>/dev/null && cd ../ && rm -r $PWD/Emails 2>/dev/null
mkdir $PWD/Emails

# Generate emails for customers to pay amount still owed 
for file in ./SedScripts/* ; do   # Use "./*" ... NEVER bare "*" ...
  if [ -e "$file" ] ; then        # Make sure it isn't an empty match.
    base=$(basename $file)
    filename=${base%.*}
    email=${filename:1}
    sed -f $file template.txt > ./Emails/$email
  fi
done