# gawk -v date="blahhhh" -f p4.awk p4Customer.txt
# using gawk to peform csv -> html manipulation
# FS = Field Seperator
# $0 = line, NF = end of line
# ($1) Customer Email - email address also uniquely defines a customer
# ($2) Full Customer Name (e.g., Bob L Head) 
# ($3) Title (e.g., Mr., Col., Ms.)
# ($4) Paid Amount - how much the customer has previously paid
# ($5) Owe Amount - how much the customer owes
# s/EMAIL/$1/g
# s/TITLE/$3/g
# s/FULLNAME/$2/g
# s/NAME/$2/g
# s/AMOUNT/$5-$4/g
# s/DATE/date/g

BEGIN { FS=","; }
{
    # printf("Print: %s\n", $);
    if($5 > $4) {
        # printf("Print: %s\n", $0);
        # print $0;

        amount = $5 - $4;
        print "s/EMAIL/" $1 "/g" > "SedScripts/g" $1 ".sed";
        print "s/TITLE/" $3 "/g" > "SedScripts/g" $1 ".sed";
        print "s/FULLNAME/" $2 "/g" > "SedScripts/g" $1 ".sed";
        print "s/NAME/" $2 "/g" > "SedScripts/g" $1 ".sed"; 
        print "s/AMOUNT/" amount "/g" > "SedScripts/g" $1 ".sed"; 
        # print "s/DATE/" date "/g"; 
    }
    # printf("\t<tr>\n");
    # for(i=1; i <= NF; i++)
    # {
    #     #printf("i: %d, $i: %s\n", i, $i);
    #     printf("\t\t<td>%s<\\td>\n", $i);
    # }
    # printf("\t<\\tr>\n");
}
END { }

# EMAIL - customer email address (1st attribute)
# TITLE - customer title (3rd attribute)
# FULLNAME - full customer name
# NAME - customer name 
# AMOUNT - owe amount
# DATE - date the payment must be received.  This is passed as the only parameter to proj4.bash.