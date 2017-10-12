#!/usr/bin/perl -w
use strict;
use warnings;
# perl four.pl input8-4.txt
open(IN, "<", $ARGV[0]) or die "Could not open input file\n";

my $line;

while ( $line = <IN> ) {
  if($line =~ /<h\d>(.*[pP]roject.*)<\/h\d>/) {
    print "<strong>$1</strong>\n";
  }
  else {
    print;
  }
}