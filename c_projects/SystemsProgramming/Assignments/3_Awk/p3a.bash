#!/bin/bash

# Use gawk script to print last names first
# Pipe into sort to sort by last names
# Reverse the sorted strings to show first -> last name

# gawk -f p3a.awk unsortedNames.txt | sort
gawk -f p3a.awk unsortedNames.txt | sort | gawk -f p3a.awk > p3a.out