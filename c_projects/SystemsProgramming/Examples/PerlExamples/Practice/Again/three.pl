#!/usr/bin/perl -w
use strict;
use warnings;
# perl three.pl input8-3.txt

open(IN, "<", $ARGV[0]) or die "Could not open input file\n";

my $line;

while ( $line = <IN> ) {
  # * - any number of things preceding it
  # \d - digit
  # \w - alphanumeric
  # () - grouping
  # \(? - escape to check for open parenthesis. Then, match one or none
  $line =~ s/\(?(\d{3})[^\w]*(\d{3})[^\w]*(\d{4})/($1)-$2-$3/g;
  print $line;
}