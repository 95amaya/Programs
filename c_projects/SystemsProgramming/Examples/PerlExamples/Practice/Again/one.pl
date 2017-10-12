#!/usr/bin/perl -w
use strict;
use warnings;

my @validList;
my @invalidList;

my $arg;
foreach $arg (@ARGV)
{
  if( -f $arg )
  {
    push @validList, $arg;
  }
  else
  {
    push @invalidList, $arg;
  }
}

print "---- Valid ----\n" . join("\n", sort(@validList)) . "\n";
print "---- Invalid ----\n" . join("\n", reverse(sort(@invalidList))) . "\n";