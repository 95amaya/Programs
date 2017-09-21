print '1. List of animals from @animals', "\n";
my @animals = ("monkey", "baboon", "longhorn", "aggie");
foreach my $animal (@animals) {
    print $animal, "\n";
}

print '2. List of fruit from a valueList', "\n";
foreach my $fruit ("apple", "grape", "apple") {
    print $fruit, "\n";;
}

print '3. List of animals from @animals using $_', "\n";
foreach (@animals) {
    print $_, "\n";
}

