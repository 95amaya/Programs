# gawk -v date="10/1/2017" -f p4.awk p4Customer.txt
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
# s/AMOUNT/$5/g
# s/DATE/date/g

BEGIN { 
  FS=","; 
  # change mm/dd/yyyy -> mm\/dd\/yyyy to work with sed
  gsub("/","\\\/",date); # returns num of matched occurences
} 
{
  # Owe amount greater than paid amout
  if($5 > $4) {
    # print $2;
    len = split($2, name, " "); # Split full name by space separator to get last name only
    # for (key in name) {
    #   print key ":" name[key];
    # }
    # Generate sed script to replace given phrases in a template email
    print "s/EMAIL/" $1 "/g" > "SedScripts/g" $1 ".sed";
    print "s/TITLE/" $3 "/g" > "SedScripts/g" $1 ".sed";
    print "s/FULLNAME/" $2 "/g" > "SedScripts/g" $1 ".sed";
    print "s/NAME/" name[len] "/g" > "SedScripts/g" $1 ".sed"; 
    print "s/AMOUNT/" $5 "/g" > "SedScripts/g" $1 ".sed"; 
    print "s/DATE/" date "/g" > "SedScripts/g" $1 ".sed"; 
  }
}
END { }

# EMAIL - customer email address (1st attribute)
# TITLE - customer title (3rd attribute)
# FULLNAME - full customer name
# NAME - customer name 
# AMOUNT - owe amount
# DATE - date the payment must be received.  This is passed as the only parameter to proj4.bash.