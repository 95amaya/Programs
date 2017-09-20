#!/bin/bash

# Get users who have not logged into each of the servers
grep -v "2017$" ./lastlog1.out > ./p2bData/log1_nonusers
grep -v "2017$" ./lastlog2.out > ./p2bData/log2_nonusers

# Same as p2a.bash - get user ids
sed -f p2a.sed ./p2bData/log1_nonusers > ./p2bData/log1_IDs
sed -f p2a.sed ./p2bData/log2_nonusers > ./p2bData/log2_IDs

# Concatenate, sort, and list count of occurences for each user ID and output that to a file
# cat ./p2bData/log1_IDs ./p2bData/log2_IDs | sort | uniq -c | wc -l
cat ./p2bData/log1_IDs ./p2bData/log2_IDs | sort | uniq -c > ./p2bData/sorted_IDs

# p2b.sed script commands
# eliminate the starting spaces and only keep IDs that occured twice
# remove single user ids from sed stream before getting user IDs with 2 occurences (spaces matter)
# sed -e '/ * 1 .*/d' -e 's/ *2 \([a-z]*[0-9]*\).*/\1/g' ./p2bData/sorted_IDs > p2b.out

sed -f p2b.sed ./p2bData/sorted_IDs > ./p2bData/p2b.out

# Used for testing purposes
# cat p2b.out | wc -l

