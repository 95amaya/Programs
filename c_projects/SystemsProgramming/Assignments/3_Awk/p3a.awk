# gawk -f p3a.awk unsortedNames.txt
BEGIN {}
{
    # Sort line last name -> first name 
    for(i=NF; i > 0; i--)
    {
       printf("%s ", $i);
    }
     printf("\n");
}
END {}