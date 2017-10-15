#!/usr/bin/perl -w
use strict;
use warnings;
use File::Basename;
# find.pl -i perlRegexpPattern listOfFiles
# where -i  is optional

# Use shift method in arrays
if($#ARGV < 1) {
    print "usage: find.pl -i perlRegexpPattern listOfFiles\n";
    die "Must specify a regex pattern and a file list\n";
}
my $regex;
my $option = shift(@ARGV);

print "option: $option\n";
if( $option eq "-i" )
{
    $regex = shift(@ARGV);
    print "RegEx: $regex\n";
    my $file;
    foreach $file (@ARGV)
    {
        if(not -f $file){
            print "Invalid Filename: $file\n";
            next;
        }
        # if filename matches regular expression print file
        if( not $file =~ /$regex/ )
        {
            # Get file contents by line
            my @contents = split("\n", `cat $file`);
            # print join("\n", @contents);
            my $check = 0;

            foreach my $line (@contents)
            {
                # Check if line contains regular expression
                if( $line =~ /$regex/ )
                {
                     $check = 1; # Exit outer LOOP!
                     last;
                }
            }
            
            if( $check )
            {
                next;
            }
            print `basename $file`
        }
    }
}
else 
{
    $regex = $option;
    my $file; 
    foreach $file (@ARGV)
    {
        if(not -f $file){
            print "Invalid Filename: $file\n";
            next;
        }
        # print "$file\n";
        # if filename matches regular expression print file
        if($file =~ /$regex/ )
        {
            # print "regex: $regex\n";
            print `basename $file`;
        }
        else
        {
            # Get file contents by line
            my @contents = split("\n", `cat $file`);
            # print join("\n", @contents);

            foreach my $line (@contents)
            {
                # Check if line contains regular expression
                if($line =~ /$regex/ )
                {
                     print basename($file) . ":" . "$line\n";
                     # Exit LOOP!
                     last;
                }
            }
        }
    }
}