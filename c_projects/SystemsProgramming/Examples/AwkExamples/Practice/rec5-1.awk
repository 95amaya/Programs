# gawk -f rec5-1.awk courses.csv
# using gawk to peform csv -> html manipulation
# FS = Field Seperator
# $0 = line, NF = end of line
BEGIN { FS=","; printf("<table>\n"); }
{
    #printf("Print: %s\n", $0);
    printf("\t<tr>\n");
    for(i=1; i <= NF; i++)
    {
        #printf("i: %d, $i: %s\n", i, $i);
        printf("\t\t<td>%s<\\td>\n", $i);
    }
    printf("\t<\\tr>\n");
}
END { printf("<\\table>\n"); }