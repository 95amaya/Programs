#!/bin/bash

# sed 1.0 - basic
# grep -wvhr 2017 | sed -n '/2016/p'
# grep -wvhr 2017 | sed -n 's/2016/2017/p'

# sed 2.0 - intermediate
# grep -wvhr 2017 | sed -n 's/[a-z]//p' # match any lower case letters 1 time and replace with nothing
# grep -wvhr 2017 | sed -n 's/[a-z]*[0-9]*//p' # match any lower case letters many times and replace with nothing
# grep -wvhr 2017 | sed -n 's/.*/Hello/2' # replace line with hello
# grep -wvhr 2017 | sed -n 's/\([a-z]*[0-9]*\).*/\1/p' # replace line with regex expression on first match
# grep -wvhr 2017 | sed -n 's/\([a-z]*[0-9]*\).*/\1/p' dummy.txt
# grep -wvhr 2017 ./dummy.txt # w - match word, v - invert match, h - no filename, r - recursive search

# file redirection
# grep -wv 2017 ./lastlog1.out > dummy.txt
# grep -wv 2017 ./lastlog2.out >> dummy.txt
# sed -n 's/\([a-z]*[0-9]*\).*/\1/p' ./dummy.txt > sed1.txt 

# ---------- p2a -------------
# 1.) get data of who hasn't logged into either server
# grep -wv 2017 ./lastlog1.out > dummy1.txt
# grep -wv 2017 ./lastlog2.out > dummy2.txt
# Store users who haven't logged into fox01 or fox02 in seperate files
grep -v "2017$" ./lastlog1.out > dummy1.txt
grep -v "2017$" ./lastlog2.out > dummy2.txt

# 2.) get user IDs only
# only get user ID from file and store in seperate files
sed -e '1d' -e 's/\([a-z]*[0-9]*\).*/\1/g' ./dummy1.txt > sed1.txt 
sed -e 's/\([a-z]*[0-9]*\).*/\1/g' ./dummy2.txt > sed2.txt

# 3.) create names with + $ for regex
# append '$' to end of user id to make proper regex expression from file1 
# NEED to REMOVE blank lines with "^$"
# sed -i '1d' sed1.txt
# sed -i '/^ \t$/d' sed1.txt
sed -e 's/$/\$/g' sed1.txt > ./sed12.txt 

# 4.) use grep -f to match files
# compare file1 (full of regex expressions) to file2
grep -f sed12.txt sed2.txt > test1.txt # want to match by word, NOT consistent

# Used for testing
# sort test1.txt > sortTest1.txt
# cat ./test1.txt | wc -l

# ------------- p2b ---------------
# 1.) Append files on top of each other and process using sed
# grep -wv 2017 ./lastlog1.out > dummy.txt
grep -v "2017$" ./lastlog1.out > dummy.txt # search for string at end of file
grep -v "2017$" ./lastlog2.out >> dummy.txt
sed -e '1d' -e 's/\([a-z]*[0-9]*\).*/\1/g' ./dummy.txt > sed.txt 

# 2 & 3.) sort by name & use uniq -c to get occurences
sort sed.txt | uniq -c > sedCount.txt # Sort and count occurences
# 4.) use sed to to inclue user ids with count = 2 and remove count
sed -n 's/ *2 \([a-z]*[0-9]*\).*/\1/p' ./sedCount.txt > test2.txt
cat test2.txt | wc -l

# Check the differences between outputs
# diff -B sortTest1.txt test2.txt # Works