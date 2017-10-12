#!/usr/bin/perl -w
use strict;
use warnings;

my %idHash;
my $id;
my $count;

open(IN, "<", $ARGV[0]) or die "Could not open input file\n";

# Read every command line argument as a file: while(<>){}
while(<IN>)
{
  ($id, $count) = split(" ", $_);
  $idHash{$id} += $count;
}

foreach my $key (sort(keys %idHash))
{
  print "$key $idHash{$key}\n";
}