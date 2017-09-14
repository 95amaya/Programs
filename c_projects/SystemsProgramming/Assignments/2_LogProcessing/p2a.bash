#!/bin/bash

# echo Hello World
# items=()
# while read -r line || [[ -n "$line" ]]; do # Deals with file that does not have \n at end to get last line
#     items+=( $line )
#     # echo "line = $line"
# done

# # declare | grep 'items'
# echo "items = ${items[@]}"

# grep -wvhr 2017 | sed -n '/2016/p'
# grep -wvhr 2017 | sed -n 's/2016/2017/p'

# grep -wvhr 2017 | sed -n 's/[a-z]//p' # match any lower case letters 1 time and replace with nothing
# grep -wvhr 2017 | sed -n 's/[a-z]*[0-9]*//p' # match any lower case letters many times and replace with nothing
# grep -wvhr 2017 | sed -n 's/.*/Hello/2' # replace line with hello
# grep -wvhr 2017 | sed -n 's/\([a-z]*[0-9]*\).*/\1/p' # replace line with regex expression on first match
# grep -wvhr 2017 | sed -n 's/\([a-z]*[0-9]*\).*/\1/p' dummy.txt

# grep -wvhr 2017 ./dummy.txt # w - match word, v - invert match, h - no filename, r - recursive search

# grep -wv 2017 ./lastlog1.out > dummy.txt
# grep -wv 2017 ./lastlog2.out >> dummy.txt
# sed -n 's/\([a-z]*[0-9]*\).*/\1/p' ./dummy.txt > sed1.txt 
# grep -wc js45 ./sed1.txt 

# sed -f p2a.sed dummy.txt

# create names
# create names with + $
# use grep -f to match files
# grep -wv 2017 ./lastlog1.out > dummy1.txt
# grep -wv 2017 ./lastlog2.out > dummy2.txt
# sed -n 's/\([a-z]*[0-9]*\).*/\1/p' ./dummy1.txt > sed1.txt 
# sed -n 's/\([a-z]*[0-9]*\).*/\1/p' ./dummy2.txt > sed2.txt 
# sed -n 's/$/\$/p' sed1.txt > ./sed11.txt 
# sed -n 's/$/\$/p' sed2.txt > ./sed22.txt
# grep -f sed11.txt sed22.txt > test1.txt # want to match by word, NOT consistent
# cat ./test1.txt | wc -l
# # grep -f test1.txt sed11.txt | wc -l
# # grep -f test1.txt sed22.txt | wc -l
# grep -f sed11.txt test1.txt | wc -l
# grep -f sed22.txt test1.txt | wc -l


# diff sed1.txt sed2.txt
# Append files on top of each other
# sort by name
# use uniq -c to get 
# use sed to to inclue user ids with count = 2 and remove count
# grep -v "2017$" ./lastlog1.out > dummy.txt # search for string at end of file
grep -wv 2017 ./lastlog1.out > dummy.txt
grep -wv 2017 ./lastlog2.out >> dummy.txt
sed -n 's/\([a-z]*[0-9]*\).*/\1/p' ./dummy.txt > sed.txt 
sort sed.txt | uniq -c > sedCount.txt # Sort and count occurences
# sed -n 's/\( *2 [a-z]*[0-9]*\).*/\1/p' ./sedCount.txt
sed -n 's/ *2 \([a-z]*[0-9]*\).*/\1/p' ./sedCount.txt | wc -l
