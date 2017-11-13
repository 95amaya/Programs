/**********************************************************************
p3afn946.c by Michael Amaya
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
    Sort bookM[] array in ascending bookId order using bubble sort.

Parameters:
    Book bookM[]    - Book array holding all the books in the library
    iBookCnt        - Stores the book count of bookM[], or size of the array

Returns:
    An ascending order sorted bookM[].
    
Notes:
    Because a Book is a structure you can copy the contents of one struct into
    another simply using '=' operator.
    
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
    printf("%s\n", pszHeading);

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
    printf("\n");
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
	printf("\t\t\t\t\t%43s %.2lf\n", "Total Fees =", pCustomer->dFeeBalance); // Print customer's total fees at end of trasaction
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
 	// reset scanf counter
            iScanfCnt = 0;

            // Taking in line including:
            //      transaction type    (1 character max)
            //      book id             (9 character max)
            //      transaction dest.   (10 char max)
            iScanfCnt = sscanf(pszRemainingInput, "%1c %9s %10s", &transaction.cTransType, transaction.szBookId, transaction.szTransDt);
            
            // check for valid transaction data information
            if(iScanfCnt < 3)
            {
                printf("%s: %s", ERR_TRANSACTION_DATA, pszRemainingInput); // don't exit this time use printf and continue
            }

	    // print formatted trasaction values from transaction structure
            printf("%43c%13s%12s\t", transaction.cTransType, transaction.szBookId, transaction.szTransDt);
            
            pCustomer->dFeeBalance += processTransaction(bookM, iBookCnt, pCustomer, transaction); // Process customer trasaction
            // And return a fee which will be added onto the customer's initial late fee balance.
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
    char szFirstSix[7];                 // Holds the first 6 characters of the bookId
    char *pszBookNum, *pszLibBookNum;   // Used for getting book number and library book number to compare values

    int iScanfCnt;
    int i, iKey;


    if(strcmp(pszSubCommand, "CHANGE") == 0)
    {
        iScanfCnt = sscanf(pszRemainingInput, "%9s %lf %lf\n", book.szBookId
            , &book.dLateFeePerDay, &book.dMaxLateFee);
        
        if(iScanfCnt < 3)
        {
            printf("%s: %s", ERR_CHANGE_SUB_COMMAND, pszRemainingInput); // don't exit this time use printf and continue
        }
        
        iKey = searchBooks(bookM, iBookCnt, book.szBookId);
        
      /*  for(i = 0; i < 6; i++)
            szFirstSix[i] = book.szBookId[i];
        
        if(strcmp(szFirstSix, "XXXXXX") == 0)
        {
            pszBookNum = book.szBookId + 6; // Getting number of book Id only
            for(i = 0; i < iBookCnt; i++)
            {
                pszLibBookNum = bookM[i].szBookId + 6; // 6 is correct offset to get number portion of bookId
               // printf("\tPointer: %p -> %s\n", pszLeft, pszLeft);
                if(strcmp(pszBookNum, pszLibBookNum) == 0)
                {
                   // printf("   %-9s %-40s %-8s %-10s %8.2lf %8.2lf \n"
                        , bookM[i].szBookId
                        , bookM[i].szTitle
                        , bookM[i].szCustomerId
                        , bookM[i].szCheckedOutDt
                        , bookM[i].dLateFeePerDay
                        , bookM[i].dMaxLateFee
                        );
                    bookM[i].dLateFeePerDay = book.dLateFeePerDay;
                    bookM[i].dMaxLateFee = book.dMaxLateFee;
                //    printf("   %-9s %-40s %-8s %-10s %8.2lf %8.2lf \n"
                        , bookM[i].szBookId
                        , bookM[i].szTitle
                        , bookM[i].szCustomerId
                        , bookM[i].szCheckedOutDt
                        , bookM[i].dLateFeePerDay
                        , bookM[i].dMaxLateFee
                        );
                }
            }
        }*/
        if(iKey >= 0)
        {
           // printf("Book: %s\tLate Fee: %.2lf\tMAX Late Fee: %.2lf\n", book.szBookId, book.dLateFeePerDay, book.dMaxLateFee);
            bookM[iKey].dLateFeePerDay = book.dLateFeePerDay;
            bookM[iKey].dMaxLateFee = book.dMaxLateFee;
        }
        else printf("  ** Book Not Found\n");
        printf("\n");
    }
    else if(strcmp(pszSubCommand, "SHOW") == 0)
    {
        iScanfCnt = sscanf(pszRemainingInput, "%9s\n", book.szBookId);
        
        if(iScanfCnt < 1)
        {
            printf("%s: %s", ERR_SHOW_SUB_COMMAND, pszRemainingInput); // don't exit this time use printf and continue
        }

        iKey = searchBooks(bookM, iBookCnt, book.szBookId);

        //for(i = 0; i < 6; i++)
          //  szFirstSix[i] = book.szBookId[i];

        if(iKey >= 0) // if book can be found print it out
        {
            printf("   %-9s %-40s %-8s %-10s %8.2lf %8.2lf \n"
                , bookM[iKey].szBookId
                , bookM[iKey].szTitle
                , bookM[iKey].szCustomerId
                , bookM[iKey].szCheckedOutDt
                , bookM[iKey].dLateFeePerDay
                , bookM[iKey].dMaxLateFee
                );
        }
        /*else if(strcmp(szFirstSix, "XXXXXX") == 0) // If bookId has this generic value you are going to be finding multiple books
        {
            pszBookNum = book.szBookId + 6; // Getting number of book Id only
            for(i = 0; i < iBookCnt; i++)
            {
                pszLibBookNum = bookM[i].szBookId + 6; // 6 is correct offset to get number portion of bookId
               // printf("\tPointer: %p -> %s\n", pszLeft, pszLeft);
                if(strcmp(pszBookNum, pszLibBookNum) == 0)
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
            printf("\n");
        }*/
        else printf("  ** Book Not Found\n");
        printf("\n");
    }
    else printf("   *** %s %s\n", ERR_CUSTOMER_SUB_COMMAND, pszSubCommand);
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
    // Binary Search
    int low, mid, max;
    low = 0;
    max = iBookCnt;

    while(low <= max)
    {
        mid = (low + max) / 2;

        if(strcmp(bookM[mid].szBookId, pszMatchBookId) == 0)
        {
       //     printf("\n\t\tBook Found!!!\n"); // Debugging purposes
            return mid;
        }
        else if(strcmp(bookM[mid].szBookId, pszMatchBookId) > 0) // 1 - 2 library book > book match
        {
         //       printf("\n %s\t>\t%s\n", bookM[mid].szBookId, pszMatchBookId); // Debugging purposes
                max = mid - 1;
        }
        else if(strcmp(bookM[mid].szBookId, pszMatchBookId) < 0)
            {
        //        printf("\n %s\t<\t%s\n", bookM[mid].szBookId, pszMatchBookId); // Debugging purposes
                low = mid + 1;
            }
    }

    return -1; // Book not found
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

double processTransaction(Book bookM[], int iBookCount, Customer *pCustomer, Transaction transaction)
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
                    strcpy(bookM[iKey].szCustomerId, pCustomer->szCustomerId);    // copy customer customer ID into book customer ID
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
                if(strcmp(bookM[iKey].szCustomerId, pCustomer->szCustomerId) == 0)
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
