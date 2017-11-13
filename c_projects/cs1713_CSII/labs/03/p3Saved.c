/**********************************************************************
p3afn946.c by your name
Purpose:
    This program reads book information and a command file.   It 
    processes the commands against the book information.
    This is the driver code for the routines written by the students.
Command Parameters:
    p3 -b bookFileName -c commandFileName
Input:
    Book	same as Programming Assignment #2 although there is different data.

    Command	This is different from the previous assignment.  The file 
            contains  text in the form of commands.  
        CUSTOMER BEGIN szBookId szCustomerId szCheckedOutDt dLateFeePerDay dMaxLateFee szTitle  
            specifies the beginning of customer request and includes all the 
            identification information from program 2.
        CUSTOMER ADDRESS szStreetAddress,szCity,szStateCd,szZipCd
            specifies the address for a customer (separated by commas)
        CUSTOMER TRANS cTransType    szBookId   szTransDt
            specifies a single book transaction.  Steps:
            -	Print the Transaction Type, Book Id, and Transaction Date 
            -	Lookup the book ID using a binary search.  If not found, print a 
                warning (but do not terminate your program) and return.
            -	If the transaction date is invalid, show a message stating "invalid date", 
                but do not terminate.  Use the validateDate  function.
            -	If the transaction type is C (meaning checkout):
                o	If the book is already checked out, show a message stating 
                    "already checked out", but do not terminate.
                o	Otherwise, check out the book to this customer, setting the book's 
                    customer ID.  The book's checked out date needs to be set to the 
                    transaction's date.
            -	If the transaction type is R (meaning return):
                o	Use dateDiff to subtract the book's szCheckOutDt from the transaction's szTransDt
                o	If the difference is more than 14:
                    --	Determine the number of days late by subtracting 14 from that difference.  
                    --	Compute the late fee by multiplying the number of days late 
                        by the book's dLateFeePerDay.
                    --	If that late fee is greater than the book's dMaxLateFee, 
                        change it to dMaxLateFee.
                    --  Print the late fee.
                    --	Add the computed late fee to the customer's dFeeBalance
                o	Set the book's customer ID to "NONE".
                o	Set the book's check out date to "0000-00-00".
        CUSTOMER COMPLETE
            specifies the completion   of a customer.  Print the total fees for this customer.
        BOOK CHANGE szBookId dLateFeePerDay dMaxLateFee
            change the Late Fee Per Day and Max Late Fee to the specified values
        BOOK SHOW szBookId    
            requests a display of a particular book.  Show all of its information.
               
Results:
    Prints the Books prior to sorting
    Prints the Books after sorting.
    Processes the commands (see above) and shows any errors.
    Prints the resulting Books
Returns:
    0  normal
    -1 invalid command line syntax
    -2 show usage only
    -3 error during processing, see stderr for more information

Notes:
    p3 -?       will provide the usage information.  In some shells,
                you will have to type p3 -\?

**********************************************************************/

// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs1713p3.h"

/******************** getBooks **************************************
    int getBooks(Book bookM[], char * pszBookFileName)
Purpose:
    Retrieves the books from the file specified..
Parameters:
    O   Book bookM[]          an array which is used for returning the books.
    I   char *pszBookFileName name of the file containing the book data
Returns:
    A count of the number of read.
Notes:
    1. This opens the file based on the specified file name. 
    2. The data in the data file is in this format
    szBookId szCustomerId szCheckedOutDt dLateFeePerDay dMaxLateFee szTitle
    9s        6s             10s           lf            lf          40s (may contain spaces)
**************************************************************************/

int getBooks(Book bookM[], char * pszBookFileName)
{
    char szInputBuffer[100];		// input buffer for reading data
    int i = 0;                      // subscript in bookM
    int iScanfCnt;                  // returned by sscanf
    FILE *pFileBook;              // Stream Input for Books data. 

    /* open the Books stream data file */
    if (pszBookFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-b");

    pFileBook = fopen(pszBookFileName, "r");
    if (pFileBook == NULL)
        exitError(ERR_BOOK_FILENAME, pszBookFileName);

    /* get book information until EOF
    ** fgets returns null when EOF is reached.
    */
    while (fgets(szInputBuffer, 100, pFileBook) != NULL)
    {
        // check for too many books to fit in the bookM array
        if (i >= MAX_BOOKS)
            exitError(ERR_TOO_MANY_BOOKS, szInputBuffer);
        iScanfCnt = sscanf(szInputBuffer, "%9s %6s %10s %lf %lf %[^\n]\n"
            , bookM[i].szBookId
            , bookM[i].szCustomerId
            , bookM[i].szCheckedOutDt
            , &bookM[i].dLateFeePerDay
            , &bookM[i].dMaxLateFee
            , bookM[i].szTitle);
        
        // It should have populated all six variables, if not exit with
        // an error.
        if (iScanfCnt < 6)
            exitError(ERR_BOOK_DATA, szInputBuffer);
        i++;
    }
    fclose(pFileBook);
    return i;
}

/******************** sortBooks **************************************
    void sortBooks(Book bookM[], int iBookCnt)
Purpose:

Parameters:
  
Returns:
    
Notes:
    
**************************************************************************/
void sortBooks(Book bookM[], int iBookCnt)  // uses bubble sort algorithm
{
    int i, j;

    for(i = 0; i < iBookCnt; i++)   // Number of elements
    {
        for(j = 0; j < iBookCnt - 1; j++) // Number of comparisons
        {
            if(strcmp(bookM[j].szBookId, bookM[j+1].szBookId) > 0) // Switch elements into descending order
            {
                Book temp = bookM[j];       // Can copy contents of one structure into another
                bookM[j] = bookM[j+1];      // simply using = operator
                bookM[j+1] = temp;
            }
        }
    }

}

/******************** printBooks **************************************
    void printBooks(char *pszHeading, Book bookM[], int iBookCnt)
Purpose:
    Prints each book in a table format
Parameters:
    I char *pszHeading    Heading to print before printing the table of books
    I Book bookM[]        Array of books
    I int iBookCnt        Number of elements in the bookM array.
Returns:
    n/a
Notes:
    
**************************************************************************/
void printBooks(char *pszHeading, Book bookM[], int iBookCnt)
{
    int i;
    printf("\n%s\n", pszHeading);

    // output column headings
    printf("   %-9s %-40s %-8s %-10s %-8s %-8s \n"
        , "Book Id", "Title", "Customer", "Ck Out Dt", "Late Fee", "Max Late");

    // output each book in a table format
    for (i = 0; i < iBookCnt; i++)
    {
        printf("   %-9s %-40s %-8s %-10s %8.2lf %8.2lf \n"
            , bookM[i].szBookId
            , bookM[i].szTitle
            , bookM[i].szCustomerId
            , bookM[i].szCheckedOutDt
            , bookM[i].dLateFeePerDay
            , bookM[i].dMaxLateFee
            );
    }
}


/********************processCustomerCommand *****************************
    void processCustomerCommand(Book bookM[], int iBookCnt
     , char *pszSubCommand, char *pszRemainingInput
     , Customer *pCustomer)
Purpose:
    Processes the subcommands associated with the CUSTOMER command:
        CUSTOMER BEGIN szBookId szCustomerId szCheckedOutDt dLateFeePerDay dMaxLateFee szTitle  
            specifies the beginning of customer request and includes all the identification information from program 2.
        CUSTOMER ADDRESS szStreetAddress,szCity,szStateCd,szZipCd
            specifies the address for a customer (separated by commas)
        CUSTOMER TRANS cTransType    szBookId   szTransDt
            specifies a single book transaction.  Steps:
            -	Print the Transaction Type, Book Id, and Transaction Date 
            -	Lookup the book ID using a binary search.  If not found, print a warning (but do not terminate your program) and return.
            -	If the transaction date is invalid, show a message stating "invalid date", but do not terminate.  Use the validateDate  function.
            -	If the transaction type is C (meaning checkout):
                o	If the book is already checked out, show a message stating "already checked out", but do not terminate.
                o	Otherwise, check out the book to this customer, setting the book's customer ID.  The book's checked out date needs to be set to the transaction's date.
            -	If the transaction type is R (meaning return):
                o	Use dateDiff to subtract the book's szCheckOutDt from the transaction's szTransDt
                o	If the difference is more than 14:
                    --	Determine the number of days late by subtracting 14 from that difference.  
                    --	Compute the late fee by multiplying the number of days late by the book's dLateFeePerDay.
                    --	If that late fee is greater than the book's dMaxLateFee, change it to dMaxLateFee.
                    --  Print the late fee.
                    --	Add the computed late fee to the customer's dFeeBalance
                o	Set the book's customer ID to "NONE".
                o	Set the book's check out date to "0000-00-00".
        CUSTOMER COMPLETE
            specifies the completion   of a customer.  Print the total fees for this customer.


Parameters:
    I/O Book bookM[]                  Array of books
    I   int   iBookCnt                Number of elements in bookM[]
    I   char  *pszSubCommand          Should be BEGIN, ADDRESS, REQUEST or COMPLETE
    I   char  *pzRemainingInput       Points to the remaining characters in the input
                                      line (i.e., the characters that following the
                                      subcommand).
    I/O Customer *pCustomer           The BEGIN subcommand begins a new customer.  
Notes:

**************************************************************************/
void processCustomerCommand(Book bookM[], int iBookCnt
    , char *pszSubCommand, char *pszRemainingInput
    , Customer *pCustomer)
{
    int iScanfCnt;
    Transaction transaction;

    // Determine what to do based on the subCommand
    if (strcmp(pszSubCommand, "BEGIN") == 0)
    {
        // Taking in first line including customer id, fee balance, email address, and full name seperated by spaces
        iScanfCnt = sscanf(pszRemainingInput, "%6s %lf %40s %30[^\n]\n" // since pCustomer is pointer to a structure
            , pCustomer->szCustomerId // 6 character max                must use -> to reference attributes
            , &pCustomer->dFeeBalance // double precision               Still need address of attribute
            , pCustomer->szEmailAddr  // 40 character max
            , pCustomer->szFullName); // 30 character max

        // Check for bad customer identification data
        if (iScanfCnt < 4)
            exitError(ERR_CUSTOMER_ID_DATA, pszRemainingInput);

    }
    else if (strcmp(pszSubCommand, "COMPLETE") == 0)
    {
        // print the customer's total fees
        // your code 

    }
    else if (strcmp(pszSubCommand, "ADDRESS") == 0)
    {
        // get the postal address and print it
        // Taking in second line including street address, city, state, and zip code
            iScanfCnt = sscanf(pszRemainingInput, "%30[^,],%20[^,],%2[^,],%5[^\n]\n" // Input MUST BE in EXACT format
                , pCustomer->szStreetAddress   // 30 character max
                , pCustomer->szCity            // 20 character max
                , pCustomer->szStateCd         // 2 character max
                , pCustomer->szZipCd);         // 5 character max

	// Check for bad customer address information
        if (iScanfCnt < 4)
            exitError(ERR_CUSTOMER_ID_DATA, pszRemainingInput);
	
	printf("*************************Library Receipt*************************\n");
	// Print first line customer ID, email address, full name, and balance
        printf("%6s %s %s (previously owed %.2lf)\n", pCustomer->szCustomerId, pCustomer->szEmailAddr
            , pCustomer->szFullName, pCustomer->dFeeBalance);

	// Print customer address information
	printf("%s\n%s, %s %s\n", pCustomer->szStreetAddress, pCustomer->szCity
                , pCustomer->szStateCd, pCustomer->szZipCd);

        // print the column heading for the transactions
        printf("\t\t\t\t\t%-5s  %-9s  %-10s\n", "Trans", "Book", "Date");

    }
    else if (strcmp(pszSubCommand, "TRANS") == 0)
    {
        // your code

        printf("\n");
    }
    else printf("   *** %s %s\n", ERR_CUSTOMER_SUB_COMMAND, pszSubCommand);
}

/********************processBookCommand *****************************
    void processBookCommand(Book bookM[], int iBookCnt
         , char *pszSubCommand, char *pszRemainingInput)
Purpose:
    Processes the subcommands associated with the BOOK command:
        BOOK CHANGE szBookId dLateFeePerDay dMaxLateFee
            change the Late Fee Per Day and Max Late Fee to the specified values
        BOOK SHOW szBookId    
            requests a display of a particular book.  Show all of its information.
                
Parameters:
    I/O Book bookM[]                  Array of books
    I   int   iBookCnt                Number of elements in bookM[]
    I   char  *pszSubCommand          Should be CHANGE or SHOW
    I   char  *pzRemainingInput       Points to the remaining characters in the input
                                      line (i.e., the characters that following the
                                      subcommand).
Notes:

**************************************************************************/
void processBookCommand(Book bookM[], int iBookCnt
                             , char *pszSubCommand, char *pszRemainingInput)
{
    Book book;

    int iScanfCnt;
    int i;
    // Determine what to do based on the subCommand
    // your code
}
/******************** searchBooks *****************************
    int searchBooks(Book bookM[], int iBookCnt, char *pszMatchBookId)
Purpose:
    Using a binary search, it finds the specified book in the booKM array.
Parameters:
    I   Book bookM[]                 Array of books
    I   int   iBookCnt               Number of elements in bookM[]
    I   char *pszMatchBookId         Book Id to find in the array
Returns:
    >= 0   subscript of where the match value was found
    -1     not found
Notes:

**************************************************************************/
int searchBooks(Book bookM[], int iBookCnt, char *pszMatchBookId)
{
    // your code
}


/*** include your processTransaction code from program #2 ***/
/***********************************************************************************************
double processTransaction(Book bookM[], int iBookCnt, Customer customer, Transaction transaction)

Purpose:
    Processs transaction requests and return any late fees inquired

Parameters:
    Book bookM[]                Book array holding book information in library
    int iBookCount              Integer holding number of books in bookM[]
    Customer customer           Customer structure holding customer information
    Transaction transaction     Transaction structure holding trasaction information

Results:
    Customer transaction late fee. If there is not one it returns 0.
    
Notes:
    Checking out or Returning is not case sensitive to the input file.
    Key string "NONE" used book customer id information if 
    the book has not been checked out. 


***************************************************************************************************/

double processTransaction(Book bookM[], int iBookCount, Customer customer, Transaction transaction)
{
    double dFee = 0.0;  // only used in return case
    int iKey;           // used to find the book index in bookM[] array

    switch(transaction.cTransType)
    {
        /***********************_CheckOut case_*******************************/
        case 'C': case 'c':
            iKey = searchBooks(bookM, iBookCount, transaction.szBookId); // Find book in the library
            
            // Is book in the library?
            if(iKey >= 0)
            {
                // Check if book has been checked out already
                if(strcmp(bookM[iKey].szCustomerId, "NONE") == 0)
                {
                    strcpy(bookM[iKey].szCustomerId, customer.szCustomerId);    // copy customer customer ID into book customer ID
                    strcpy(bookM[iKey].szCheckedOutDt, transaction.szTransDt);  // copy customer transaction date into 
                                                                                //book check out date
                } 
                // Check book out for customer replacing bookM[iKey] with customer id and check out date
                else
                    printf(" *** Already Checked Out\t");
            }
            else
                printf(" *** Book Not Found\t");

            
            printf("\n");
            break;
        
        /***********************_Return case_*******************************/
        // Resets book Id with 'NONE' and check out date with '0000-00-00'
        case 'R': case 'r':
            iKey = searchBooks(bookM, iBookCount, transaction.szBookId); // Find out where book is in the library
            
            // Is library book in the library?
            if(iKey >= 0)
            {
                // Is it being returned by the right customer?
                if(strcmp(bookM[iKey].szCustomerId, customer.szCustomerId) == 0)
                {
                    //printf("Returning book.. Date Checked Out: %s", bookM[iKey].szCheckedOutDt); // used for debugging
                    
                    // find how many days late it was returned (14 day checkout period)
                    int lateReturn =  dateDiff(transaction.szTransDt, bookM[iKey].szCheckedOutDt) - 14; // Find out if
                                                                        // Book had been returned late
                    double dCheckFee = 0;       // Declare check fee double used to check against the MAX LATE FEE
                    
                    // Is the book Late?
                    if(lateReturn > 0)
                    {
                        dCheckFee = bookM[iKey].dLateFeePerDay * lateReturn; //Compute Associated fee
                        // Is the fee over the limit?
                        if(dCheckFee > bookM[iKey].dMaxLateFee)
                            dFee = bookM[iKey].dMaxLateFee; // Get the Max Late Fee
                        else
                            dFee = dCheckFee;               // otherwise get the regular late fee
                    }
                   

                /*  Used for debugging purposes to make sure late fees are being processes correctly
                        printf("\t%d *  %.2lf  = %.2lf > %.2lf ? %.2lf\t"
                        , lateReturn
                        , bookM[iKey].dLateFeePerDay
                        , dCheckFee, bookM[iKey].dMaxLateFee, dFee);
                  */  

                    printf(" Late Fee = %.2lf", dFee);                  // Print late fee for transaction
                    strcpy(bookM[iKey].szCustomerId, "NONE");           // Reset customer id in library
                    strcpy(bookM[iKey].szCheckedOutDt, "0000-00-00");   // Reset check out date in library

                }
                else
                    printf(" *** Wrong customer returning book\t"); // wrong customer Error
            }
            else
                printf(" *** Book Not Found\t");    // Book not found in the library Error

            
            printf("\n");
            break;
        
        default: 
            printf("%c - Not a Transaction Type. Couldn't process Transaction.\n", transaction.cTransType);
            break;
    }

    return dFee;    // Return late fee incurred through transaction
}
