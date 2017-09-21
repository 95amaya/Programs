#!/usr/bin/perl -w
# scalars
my $total = 10.95;
my $courseNumber = "CS3423";
my $weird = "3423";
$total += $weird;
print "My total is $total\n";
my $course = $courseNumber;
$course = "CS" . 1713;
print "course is ", $course, "\n";
print "courseNumber is ", $courseNumber, "\n";

