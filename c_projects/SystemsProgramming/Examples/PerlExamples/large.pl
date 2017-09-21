#!/usr/bin/perl
use strict;
my $count = 0;

# See if there are two arguments to the command.  Note that
# $#ARGV is the subscript of the last argument.  Since subscripts
# begin with 0, it should be one less than the number expected.

if ($#ARGV != 1) {
    print "Usage:  large directoryName biggerThanSize\n";
    die "two arguments expected";
}

# make certain the directory exists
if (not -d $ARGV[0]) {
    print "Usage:  large directoryName biggerThanSize\n";
    die "specified directory $ARGV[0] does not exist";
}

# get all the *.pl files in the specified directory
my @files = glob("$ARGV[0]/*.pl");
foreach my $file (@files) {
# see if file size is greater than the specified size
    if (-s $file > $ARGV[1]) {
        print "$file \t ", -s $file, "\n"; 
        $count++;
    }
}
print "\nNumber of files in '$ARGV[0]' larger than $ARGV[1] is $count\n";

