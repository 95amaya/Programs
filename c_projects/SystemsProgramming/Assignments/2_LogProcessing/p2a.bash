#!/bin/bash

# Using grep to do an inverted match on all lines ending with 2017
# Outputting these lines to text files for further processing 
grep -v "2017$" ./lastlog1.out > ./p2aData/log1_nonusers
grep -v "2017$" ./lastlog2.out > ./p2aData/log2_nonusers

# p2a.sed script commands
# Need to remove the first line of the log file because it does not contain relavent info
# Then extract user IDs from each line by searching for regular expression and writing over line with that matched pattern
# sed -e '1d' -e 's/\([a-z]*[0-9]*\).*/\1/g' ./p2aData/log1_nonusers.txt > ./p2aData/log2_nonusers_formatted.txt
# sed -e '1d' -e 's/\([a-z]*[0-9]*\).*/\1/g' ./p2bData/log2_nonusers.txt > ./p2aData/log2_nonusers_formatted.txt

sed -f p2a.sed ./p2aData/log1_nonusers > ./p2aData/log1_IDs
sed -f p2a.sed ./p2aData/log2_nonusers > ./p2aData/log2_IDs

# p2aDollar.sed
# Need to make sure to add a '$' to the end of the line to make it match uniquely for these regex
# Need to escape with '\$' to add '$'
# sed -e 's/$/\$/g' sed1.txt > ./sed12.txt 

# Only need to do it to one file because it will be compared to the other to find the intersection
sed -f p2aDollar.sed ./p2aData/log1_IDs > ./p2aData/log1_dollar

# Find the intersection of the 2 files, one with regex, and the other with normal user IDs
# Make sure there is not '$' by itself in the regexp file otherwise output will be wrong
grep -f ./p2aData/log1_dollar ./p2aData/log2_IDs > ./p2aData/p2a.out

# This was used for testing purproses to check for a match between p2a and p2b output
# sort ./p2aData/p2a.out > ./p2aData/p2aSorted.out
# cat ./p2aData/p2aSorted.out | wc -l