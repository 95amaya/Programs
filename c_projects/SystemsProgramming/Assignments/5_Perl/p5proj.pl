#!/usr/bin/perl -w
use strict;
use warnings;
# perl p5proj.pl mm/dd/yyyy

if($#ARGV != 0) {
  print "usage: [DATE: mm/dd/yyyy]\n";
  die "Must specify a date\n";
}

# Check if directory exists
if(-d "./Emails") {
  # Remove directory
  print `rm -r ./Emails`;
}
# Make emails directory
print `mkdir ./Emails`;

# Read from file
open(INFILE, "<", "p5Customer.txt")
    or die "could not open INFILE: $!\n";

while(my $line = <INFILE>) {
  chomp $line;
  # Get customer info by using comma as delimiter
  my @customer = split(/,/, $line);
  if($customer[4] > $customer[3]) {
    # print "Owes: $customer[4] > paid: $customer[3]\n";
    # print "$customer[1] owes money.\n";
    # print "Customer info - " . join(':', @customer) . "\n";
    my $template = `cat template.txt`;
    my $name = (split(/ /, $customer[1]))[-1]; # Get last value of split
    # print "Last Name: $name\n";
    $template =~ s/EMAIL/$customer[0]/g;
    $template =~ s/FULLNAME/$customer[1]/g;
    $template =~ s/TITLE/$customer[2]/g;
    $template =~ s/NAME/$name/g;
    $template =~ s/AMOUNT/$customer[4]/g;
    $template =~ s/DATE/$ARGV[0]/g;
    # print $template, "\n";
    open(OUTFILE, ">", "./Emails/$customer[0]");
    print OUTFILE $template;
    close(OUTFILE);
  }
  else {
    # print "$customer[1] does not owe money.\n"
  }
}
close(INFILE);