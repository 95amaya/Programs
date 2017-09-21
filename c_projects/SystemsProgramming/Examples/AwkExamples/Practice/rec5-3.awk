# gawk -f rec5-3.awk dummydata.txt
# gawk -v test="100" -f rec5-3.awk dummydata.txt
BEGIN { printf("---- Start ----\n"); print test; }
{
    #process lines getting username 
    #printf("\t<tr>\n");
    #for(i=1; i <= NF; i++)
    #{
    #    #printf("i: %d, $i: %s\n", i, $i);
    #    printf("\t\t<tr>%s<\\tr>\n", $i);
    #}
    #printf("\t<\\tr>\n");
}
END { 
    printf("Zip file statistics for USER (change later)\n");
    printf("Count: XX | Total size: XX | Average size: XX\n");    
}