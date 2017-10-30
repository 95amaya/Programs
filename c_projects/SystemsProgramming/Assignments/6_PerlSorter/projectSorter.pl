#!/usr/bin/perl -w
use strict;
use warnings;
use File::Basename;
# use Cwd;
# projectSorter.pl [Directory]

if($#ARGV != 0 || ($#ARGV == 0 && not -d $ARGV[0])) {
    print "usage: projectSorter.pl [Directory]\n";
    die "Must specify an Existing directory\n";
}

my @directory = glob("$ARGV[0]/*");
my $file;
# my $path = cwd();
# print @directory;
# Create Miscellaneous Directory

if( not -d "./$ARGV[0]/misc" )
{
    print `mkdir ./$ARGV[0]/misc`;
}

foreach $file (@directory)
{
    #check if assignment exists in directory
    # my $assign = basename($file) =~ s/.*proj(.*)/$1;
    my $assign = basename($file);
    if ( $assign =~ /^proj\w*\..*/ )
    {
        $assign =~ s/^proj(\w*)\..*/$1/;
        my $newDir = "assignment" . $assign;
        # print "Assign Directory: $newDir\n";

        if( not -d "./$ARGV[0]/$newDir" ) 
        {
            # print "Make new Directory!\n";
            print `mkdir ./$ARGV[0]/$newDir`;
        }
        # print "Move to new Directory!\n";
        print `mv $file ./$ARGV[0]/$newDir`;
    }
    else 
    {
        print `mv $file ./$ARGV[0]/misc`
        # print "Move to misc!\n"
    }
}
