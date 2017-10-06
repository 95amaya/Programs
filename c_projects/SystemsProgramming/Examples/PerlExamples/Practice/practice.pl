#!/usr/bin/perl -w
use strict;
use warnings;
# perl p5proj.pl mm/dd/yyyy
if($#ARGV != 0) {
  print "usage: [DATE: mm/dd/yyyy]\n";
  die "Must specify a date\n";
}
print "$ARGV[0]\n";
# print "$ARGV[0]\n";
# my @date = split(/\//, $ARGV[0]);
# print join("\\\/", @date) . "\n";
# my $date = join("\\\/", split(/\//, $ARGV[0]));
# print "new date - $date\n";
my $input = `cat test.txt`;

# ---------- Using regex 1 -----------------------
# my $format = `cat test.txt` =~ /(.*),(.*),(.*),(.*),(.*)/;
# print "$input\n";
# print "Matches: $format, $1 | $2 | $3 | $4 | $5\n";

# ---------- Using regex 2 -----------------------
# my ($email, $name, $sirname, $paid, $owes);
# ($email, $name, $sirname, $paid, $owes) = `cat test.txt` =~ /(.*),(.*),(.*),(.*),(.*)/;
# print "Matches: $format, email: $email, name: $name, sirname: $sirname | paid: $paid | owes: $owes\n";
# if ($owes > $paid) {
#   print "Owes more than paid\n";
# }

# ---------- Reading from file -----------------------
open(INFILE, "<", "p4Customer.txt")
    or die "could not open INFILE: $!\n";
while(my $line = <INFILE>) {
    # print $line;
    chomp $line;
    print $line . "\n";
    # put code in here
}
close(INFILE);
# open(OUTFILE, ">", "last.txt");
# print OUTFILE $lastLine;
# close(OUTFILE);
# ---------- Using Split Array -----------------------
# print join(':', split(/,/, $input)), "\n";
my @customer = split(/,/, $input);
print "Customer info - ", join(':', @customer), "\n";
if($customer[4] > $customer[3]) {
  print "Owes: $customer[4] > paid: $customer[3]\n";
  my $template = `cat template.txt`;
  my $name = (split(/ /, $customer[1]))[-1]; # Get last value of split
  print "Last Name: $name\n";
  $template =~ s/EMAIL/$customer[0]/g;
  $template =~ s/FULLNAME/$customer[1]/g;
  $template =~ s/TITLE/$customer[2]/g;
  $template =~ s/NAME/$name/g;
  $template =~ s/AMOUNT/$customer[4]/g;
  # $template =~ s/DATE/$date/g;
  # print $template, "\n";
  print "Read Customer\n";
  # Check if directory exists
  # if(-d "./Emails") {
  #   print "IS a Directory!\n";
  #   print `rm -r ./Emails`;
  # }

  # print `mkdir ./Emails`;
  # open(my $file, '>', "./Emails/$customer[0]");
  # print $file "$template";
  # close $file;
}