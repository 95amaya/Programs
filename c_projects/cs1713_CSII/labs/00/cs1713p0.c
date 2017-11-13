/**
cs 1713p0.c by Michael Amaya
Purpose:
    This program computes the average grade for each student.
Command Parameters:
    n/a
Input:
    The standard input file stream contains mulitple lines (terminated by EOF).
    Each line contains:
    dExam1 dExam2 dFinalExam szStudnetNr szName
    10.2lf 10.2lf 10.2lf    6s  20s (May have blanks)
Results:
    Prints the student Id, name, exam scores, and average for each student.
Returns:
    0 - normal
    2 - bad input, not enough data values on line
Notes:
    When bad input is encountere, the program terminates.
    If compiling using visual studio, tell compiler not to give its warning
    about safety of scanf and printf
**/

//#define _CRT_SECURE_NO_WARNINGS 1

/* Include Files */

#include <stdio.h>
#include "cs1713p0.h"

int main(int argc, char *argv[])
{
    Student student;                        // Student structure for holding student data
    FILE *pfileStudent;                     // FILE variable for student file
    char szInputBuffer[MAX_LINE_SIZE + 1];  // input buffer for fgets
    int iScanfCnt;                          // scanf returns the number of successful inputs
    double dAverage;                        // grade average for a student

    pfileStudent = stdin;

    // Print heading
    printf("%-10s %-20s %10s %10s %10s %10s\n", "ID", "Name", "Exam 1", "Exam 2", "Final", "Average");
    
    // Read data input lines of text until EOF. fets returns NULL at EOF
    while(fgets(szInputBuffer, MAX_LINE_SIZE, pfileStudent)) //returns szInputBuffer with contents from stream
    {
       if(szInputBuffer[0] == '\n')
           continue;

        iScanfCnt = sscanf(szInputBuffer, "%lf %lf %lf %6s %20[^\n]\n" // sscanf reads string and formats to value
                                                                // locations; returns num of items filled successfully  
            , &student.dExam1                           // specify 6s as max number of characters to be
            , &student.dExam2                           // input because if there is more it can write over memory
            , &student.dFinalExam                       // causing code breakdown. 20[^n] means take last 20 characters 
            , student.szStudentIdNr                     // or until you get to the new line, so that name can have
            , student.szStudentFullNm);                 // spaces.

        // Check for bad input. scanf returns the number of valid conversions
        if(iScanfCnt < 5)
        {
            printf("invalid input when reading student data, only %d valid values. \n"
                , iScanfCnt);
            printf("\tdata is %s\n", szInputBuffer);
            return ERR_BAD_INPUT;
        }

        dAverage = (student.dExam1 + student.dExam2 + student.dFinalExam) / 3;

        printf("%-10s %-20s %10.2f %10.2f %10.2f %10.2f\n" // Strings can be right or left adjusted but
            , student.szStudentIdNr                        // Numerical vaules with decimal should always
            , student.szStudentFullNm                      // be right adjusted for decimal.
            , student.dExam1
            , student.dExam2
            , student.dFinalExam
            , dAverage);

    }
    fclose(pfileStudent);
    return 0;
}
