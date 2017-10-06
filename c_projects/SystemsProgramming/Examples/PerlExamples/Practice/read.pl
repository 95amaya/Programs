#!/usr/bin/perl -w
use strict;
use warnings;

open(INFILE, "<", "test.pl")
    or die "could not open INFILE: $!\n";

my $count = 1;
while(my $line = <INFILE>) {
    # print $line;
    chomp $line;
    # print $line . "\n";
    # put code in here
    if($count % 5 == 0){
      print "line 5\n";
    }
    $count++;
}
close(INFILE);
# open(OUTFILE, ">", "last.txt");
# print OUTFILE $lastLine;
# close(OUTFILE);

open(IN, "<", $ARGV[0]) or die "Could not open file $ARGV[0]\n";


while (my $line = <IN>) {
  if ($line eq "findme\n"){
    print "Found on line $count\n";
    last; # break
  }
  $count++;
}