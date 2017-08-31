#!/bin/bash
read -p "Enter Month (MMM) DayOfMonth and Year:" month day year
# convert the alpha month to a numeric
case "$month" in
    [Jj]an) mon=1;;
    [Ff]eb) mon=2;;
    [Mm]ar) mon=3;;
    [Aa]pr) mon=4;;
    [Mm]ay) mon=5;;
    [Jj]un) mon=6;;
    [Jj]ul) mon=7;;
    [Aa]ug) mon=8;;
    [Ss]ep) mon=9;;
    [Oo]ct) mon=10;;
    [Nn]ov) mon=11;;
    [Dd]ec) mon=12;;
    *)      echo "Bad month value = '$month'"
            exit 1;;
esac
echo "date=$mon/$day/$year"