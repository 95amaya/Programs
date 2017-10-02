# gawk -f p3b.awk reservation.txt
BEGIN { 
    printf("%-12s %-10s %5s %10s\n", "Name", "Flight", "Seats", "Total Cost"); 
    Name = "";
    CustCost;
}
{
    # CUST gives new customer info
    # Reset Customer Cost
    if($1 == "CUST") 
    {
        Name = $NF;
        CustCost = 0;
    }
    # RESERVE gives flight information 
    # $2 = Flight, $3 = Seats, $4 = Total Cost
    # Flight is associative array holding values of seats per flight
    else if($1 == "RESERVE")
    {
        printf("%-12s %10s %5s %10.2lf\n", Name, $2, $3, $4*$3);
        CustCost += $3*$4;
        Flight[$2] += $3;
    }
    # ENDCUST ends customer info.
    # Print Total Customer cost
    else if($1 == "ENDCUST")
    {
        printf("%30s %9.2lf\n", "Total:", CustCost);
    }
    # Else invalid input was received
    else{
        printf("Invalid Input\n");
    }
}
END {
    # Print the Flights and Number of seats per flight 
    printf("%-10s %10s\n", "Flight", "Total Seats");
    for(key in Flight)
    {
        printf("%-10s %10s\n", key, Flight[key]);
    }    
}