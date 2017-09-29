# gawk -f rec5-3.awk dummydata.txt
# gawk -v user="rslavin" -f rec5-3.awk dummydata.txt
BEGIN { 
    sum = 0;
    count = 0;
    # print test; 
}
{
    if(match($3, user)) {
        print $0
        if($NF ~ /\.zip$/) {
            sum += $5;
            count++;
        }
    }
}
END { 
    printf("Zip file statistics for %s\n", user);
    if (count > 0) {
        avg = sum/count
        printf("Count: %d | Total size: %d | Average size: %.2lf\n", count, sum, avg); 
    }
    else 
        print "No files matched"; 
}