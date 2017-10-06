#!/usr/bin/perl -w
# perl test.pl hello goodbye blah HelloWorld
use strict;
use warnings;

my @arr = (1,2,3,4,5);
my @arr2 = (1..5);
my @arr3 = ("a".."z"); # works inclusively
my $len = @arr;
print "1st:$arr[0], 3rd:$arr[2], Total:$len\n"; # $#arr - last element 

if($#ARGV < 0) {
  die "No Arguments Specified\n";
}

foreach my $arg (@ARGV) {
  if(-f $arg) {
    print "File: $arg\n";
  }
  if(-d $arg) {
    print "Directory: $arg\n";
    print "---- Contents -----\n" . `ls ./$arg` . "\n";
  }
}

my ($a, $b, $c);
if($#ARGV > 2) { # Three Variables 
  ($a, $b, $c) = @ARGV[0 .. 2];
  print "\$a = $a, \$b = $b, \$c = $c\n";
}

print "What is your age? "; 
defined(my $age = <STDIN>) 
    or die "input error from STDIN (likely EOF)";
chomp $age;   # remove newline"
# my $today = `date "+%Y"`;
# print "Age = $age, Today = $today\n";
# my $bday = ($today + 0) - $age;
my $bday = (`date "+%Y"` + 0) - $age;
print "You were born in $bday \n";