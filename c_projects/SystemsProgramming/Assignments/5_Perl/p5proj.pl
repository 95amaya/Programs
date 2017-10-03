#!/usr/bin/perl -w
# perl p5proj.pl mm/dd/yyyy
if($#ARGV != 0) {
  print "usage: [DATE: mm/dd/yyyy]\n";
  die "Must specify a date\n";
}
print "$ARGV[0]\n";
my $date;
# print `ls`, "\n";
# print `cat p4Customer.txt`;
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

# ---------- Using Array -----------------------
# print join(':', split(/,/, $input)), "\n";
my @customer = split(/,/, $input);
print "Customer info - ", join(':', @customer), "\n";
if($customer[4] > $customer[3]) {
  print "Owes: $customer[4] > paid: $customer[3]\n";
  my $template = `cat template.txt`;
  $template =~ s/EMAIL/$customer[0]/g;
  $template =~ s/FULLNAME/$customer[1]/g;
  $template =~ s/TITLE/$customer[2]/g;
  $template =~ s/AMOUNT/$customer[4]/g;
  print $template, "\n";
}