#!/bin/bash

if [ $# -ne 1 ]; then
  echo "usage: $0 [DATE: mm/dd/yyyy]"
  exit 1
fi

gawk -f p4.awk test.txt
# gawk -f p4.awk p4Customer.txt

 #  Correct glob use:
 #+ always use "for" loop, prefix glob, check for existence:
for file in ./SedScripts/* ; do          # Use "./*" ... NEVER bare "*" ...
  if [ -e "$file" ] ; then    # Make sure it isn't an empty match.
    # echo $file
    #  echo $(cat $file)
    # echo $(basename $file)
    base=$(basename $file)
    filename="${base%.*}"
    # echo "${base%.*}"
    # len=${#base}
    # email=${base:1:len-5}
    email=${filename:1}
    echo $email
    # sed -f $file template.txt > ./Emails/$email
  fi
done