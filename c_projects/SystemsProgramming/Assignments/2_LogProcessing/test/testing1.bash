#!/bin/bash

# was practicing using sed to take file without comments and write it to another file
# sed -e "/^#/d" > file 
grep -v "2017$" ./lastlog1.out > dummy1.txt
grep -v "2017$" ./lastlog2.out > dummy2.txt

sed -e '1d' -e 's/\([a-z]*[0-9]*\).*/\1/g' ./dummy1.txt > sed1.txt 
sed -e 's/\([a-z]*[0-9]*\).*/\1/g' ./dummy2.txt > sed2.txt
sed -e 's/$/\$/g' sed1.txt > ./sed12.txt 

grep -f sed12.txt sed2.txt > test1.txt # want to match by word, NOT consistent
sort test1.txt > sortTest1.txt
cat ./test1.txt | wc -l


grep -v "2017$" ./lastlog1.out > dummy.txt # search for string at end of file
grep -v "2017$" ./lastlog2.out >> dummy.txt
sed -e '1d' -e 's/\([a-z]*[0-9]*\).*/\1/g' ./dummy.txt > sed.txt 
sort sed.txt | uniq -c > sedCount.txt # Sort and count occurences
sed -n 's/ *2 \([a-z]*[0-9]*\).*/\1/p' ./sedCount.txt > test2.txt
cat test2.txt | wc -l

