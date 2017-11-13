/**********************************************************************
p2afn946.c  (change the name to use your abc123 id)
Purpose:
    This program reads customer transactions to produce output 
    suitable as a Library Receipt. 
Command Line Arguments:
    p2  -b LibraryBookFileName -c  customerTransactionFileName  
Input:  
    Stream input file which contains many customers, each 
    containing possibly many book transactions.  There are three different 
    kinds of lines of data for each transaction:
    - Customer Identification Information:
        o One line per customer (separated by spaces)
            szCustomerId  dFeeBalanace  szEmailAddr  szFullName 
             6s              lf           40s           30s (may contain spaces)
        o Although szFullName is a maximum of 30 characters, it may 
          contain spaces; therefore, you cannot simply use %30s.  
          For szFullName, you will have to use a bracket format 
          code: %30[^\n] which doesn't have an 's' in it.
    - Customer Address Information:
        o One line per customer (separated by commas)
        o szStreetAddress              szCity   szStateCd   szZipCd
              30s (may contain spaces)   20s      2s          5s
        o Although szStreetAddress is a maximum of 30 characters, 
          it may contain spaces; therefore, you cannot simply use %30s.  
          You will have to use a bracket format code using %[^,]
        o You do not need another while loop for this address information 
          since there is only one per customer.  You will need to use fgets 
          and an if statement.
    - Book Transaction:
        o 0 to many book transactions per customer (terminated by END in the Book ID)
        o cTransType    szBookId   szTransDt 
           1c            s9              s10
        o cTransType must be either C for check out or R for return

Results:
    Prints each Library Receipt in a readable format.
    Examples:
        ******************** Library Receipt ***********************
        111111 petem@xyz.net Pete Moss (previously owed 0.75)
        123 Boggy Lane
        New Orleans LA 70112
        Trans  Book       Date
          C    JOYPGM001  2016-01-25
          C    TECHDR001  2016-01-25
        ******************** Library Receipt ***********************
        222222 pcorn@abc.net Pop Corn (previously owed 0.00)
        456 Kernel
        San Antonio TX 78210
        Trans  Book       Date
          C    TECHDR001  2016-01-25
          C    TECHDR002  2016-01-25
          C    JOYPGM004  2016-01-25
Returns:
    0  normal
    -1 invalid command line syntax
    -2 show usage only
    -3 error during processing, see stderr for more information
Notes:
    p1 -?  will provide the usage information.  In some shells,
                you will have to type reserve -\?
  
**********************************************************************/
// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
//#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs1713p2.h"
FILE *pFileCust;               // stream Input for Customer Transaction data
FILE *pFileBook;

void processCommandSwitches(int argc, char *argv[], char **ppszCustomerFileName, char **ppszLibraryFileName);

int main(int argc, char *argv[])
{
    char *pszCustomerFileName = NULL;   // Declare customer file name pointer
    char *pszLibraryFileName  = NULL;   // Declare library file name pointer
    Book bookM[MAX_BOOKS];              // Declare array for library information
    int iBookCount = 0;                 // Declare book count for how many books in the array

    // Process the command switches
    processCommandSwitches(argc, argv,  &pszCustomerFileName, &pszLibraryFileName);

////////////////_Processing of Library File information_////////////////////////////
    // open the Library Book stream data file
    if (pszLibraryFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-b");
    
    pFileBook = fopen(pszLibraryFileName, "r");     // Open book file to begin for processing
    if (pFileBook == NULL)
        exitError(ERR_CUSTOMER_FILENAME, pszLibraryFileName);

    iBookCount = getLibrary(bookM);                 // Process book file information
    fclose(pFileBook);                              // Close book file
    printLibrary(bookM, iBookCount);                // Print library or book information


//////////////_Processing of Customer File information_/////////////////////////////
    
    // open the Customer Transaction stream data file
    if (pszCustomerFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-c");
    
    pFileCust = fopen(pszCustomerFileName, "r");    // Open customer file to begin for processing
    if (pFileCust == NULL)
        exitError(ERR_CUSTOMER_FILENAME, pszCustomerFileName);
   
    // process the Customers Data
    processCustomers(bookM, iBookCount);

    fclose(pFileCust);                              // Close customer file end of processing

    printLibrary(bookM, iBookCount);                // Print library or book information
    printf("\n");    // included so that you can put a breakpoint on this line
    return 0;
}

/*************
void printLibrary(Book bookM[], int iBookCount)

Purpose:
    Prints out library information

Parameters:
    Book bookM[]        Array holding library book information
    int iBookCount      Integer holding the size of bookM[] array.

Results:	
		Original Book Information
	 Book ID           Title                       Customer ID   Checked Out  Late Fee   Max Fee
	JOYPGM001   The Joys of Programming               NONE       0000-00-00     0.25      50.00
	JOYPGM002   The Joys of Programming               333333     2016-01-05     0.25      50.00
	JOYPGM003   The Joys of Programming               NONE       0000-00-00     0.25      50.00
	JAVADD001   Java Isn't an Addiction               NONE       0000-00-00     0.30      60.00
	PYTHON001   Learn Python Without Getting Bit      111111     2016-01-02     0.30      60.00
	PYTHON002   Learn Python Without Getting Bit      NONE       0000-00-00     0.30      60.00
	TECHDR001   My Technical Dream Job                NONE       0000-00-00     0.25      50.00
	JOYPGM004   The Joys of Programming               NONE       0000-00-00     0.25      50.00
	LINUXX004   Learning Linux                        333333     2016-01-05     0.30      60.00
	COBOLL001   How your Grandpa Coded in COBOL       NONE       0000-00-00     0.10      10.00
	EXCELL001   Excel at Excell                       444444     2015-09-01     0.80      65.00
	PERLLL001   Is PERL the Jewel of Programming?     NONE       0000-00-00     0.10      10.00
	SQLDBB001   Making Your DB Queries SQueeL         555555     2016-02-16     0.30      60.00
	PRANKS001   Software Pranks                       NONE       0000-00-00     0.90      60.00
	ARTINT001   A.I. Practical Algorithms             333333     2015-11-15     0.30      55.00

Notes:

*************/

void printLibrary(Book bookM[], int iBookCount)
{
    int i = 0;

    printf("\n\tOriginal Book Information\n");                              // Print title
    printf("%8s%16s%34s%14s%10s%10s\n", "Book ID", "Title", "Customer ID"   // Print table columns
        , "Checked Out", "Late Fee", "Max Fee");
    while(i < iBookCount)                                                   // Go through bookM[] array
    {
        printf("%-12s%-38s%-10s%11s%9.2lf%11.2lf\n", bookM[i].szBookId      // Print book information
            , bookM[i].szTitle, bookM[i].szCustomerId, bookM[i].szCheckedOutDt
            , bookM[i].dLateFeePerDay, bookM[i].dMaxLateFee);

        i++;
    }
}

/**********************************************************************
void printCompLibrary(Book bookM[], Book bookComp[],  int iBookCount)

Purpose:
    Only prints out library information that has been modified since previous transaction

Parameters:
    Book bookM[]        Array holding new trasaction library book information
    Book bookComp[]     Array holding last trasactions library book information
    int iBookCount      Integer holding the size of bookM[] array.

Results:
    Prints the library book information that has been modified by a new trasaction.

Notes:

***********************************************************************/

void printCompLibrary(Book bookM[], Book bookComp[], int iBookCount)
{
    int i;

    printf("\n\tBook Information Changed\n");                               // Print title
    printf("%8s%16s%34s%14s%10s%10s\n", "Book ID", "Title", "Customer ID"   // Print table columns
        , "Checked Out", "Late Fee", "Max Fee");
    for(i = 0; i < iBookCount; i++)                                         // Go through bookM[] array
    {
        if(strcmp(bookM[i].szCustomerId, bookComp[i].szCustomerId) != 0)    // comparing new array book customer id 
                                                                            // to original to see which
                                                                            // elements were changed
        {
            printf("%-12s%-38s%-10s%11s%9.2lf%11.2lf\n", bookM[i].szBookId  // Print contents of that element that
                , bookM[i].szTitle, bookM[i].szCustomerId, bookM[i].szCheckedOutDt // was changed
                , bookM[i].dLateFeePerDay, bookM[i].dMaxLateFee);
        }
    }
}

/*************************************************************************
void processCustomers()

Purpose:
    Format inputted customer library transaction information.

Inputs:
    N/A void method.
    However, it reads from a stream input file expecting format:
    Line 1: Customer Identification Information
    Line 2: Customer Address Information
    Line 3-END: Book Transaction Information

Results:
    Outputs formatted customer transaction receipt shown below:
    
        *************************Library Receipt*************************
	111111 petem@xyz.net Pete Moss (previously owed 0.75)
	123 Boggy Lane
	New Orleans LA 70112
	Trans  Book       Date      
	  C    JOYPGM001  2016-01-25	
	  C    TECHDR001  2016-01-25	
	  R    PYTHON001  2016-01-25	 Late Fee = 2.70
                                       Total Fees = 3.45                               

Notes:
    Processes each customer trasaction individually and  will keep running even when there 
    is an error with the input customer file information

**************************************************************************/


void processCustomers(Book bookM[], int iBookCount)
{
    Customer customer;                      // Instantiate customer structure
    Transaction trans;                      // Instantiate transaction structure
    char szInputBuffer[MAX_LINE_SIZE + 1];  // Add one for zero byte termination
    Book bookComp[MAX_BOOKS];               // Array for debugging purposes used to compare trasaction updates
                                            //holding old library book information. 
    int iScanfCnt;                          // sscanf counter of succesfully inputted data

    double dFee;                            // Instantiate late fee variable

    while(fgets(szInputBuffer, MAX_LINE_SIZE, pFileCust) != NULL)
    {
        printf("*************************Library Receipt*************************\n");
        iScanfCnt = 0;      // reset sscanf counter with each new customer
        dFee = 0;
        memcpy(bookComp, bookM, (sizeof bookM[0]) * iBookCount); // copies bookM contents into bookComp by copying the length
        // of the array (in bytes), which is # of bytes of first element * total number of elements to get exact memory amount

        // Taking in first line including customer id, fee balance, email address, and full name seperated by spaces
        iScanfCnt = sscanf(szInputBuffer, "%6s %lf %40s %30[^\n]\n"
            , customer.szCustomerId // 6 character max
            , &customer.dFeeBalance // double precision
            , customer.szEmailAddr  // 40 character max
            , customer.szFullName); // 30 character max
        
        // Check for valid customer information
        if(iScanfCnt < 4)
        {
            printf("%s: %s", ERR_CUSTOMER_ID_DATA, szInputBuffer); // don't exit this time just give a printf error
        }

        // Print first line customer ID, email address, full name, and balance
        printf("%6s %s %s (previously owed %.2lf)\n", customer.szCustomerId, customer.szEmailAddr
            , customer.szFullName, customer.dFeeBalance);
        
        if(fgets(szInputBuffer, MAX_LINE_SIZE, pFileCust) != NULL)  // Checking if customer file still 
                                                                    //has lines of data to be processed
        {
            iScanfCnt = 0;      // Reset scanf counter
       
            // Taking in second line including street address, city, state, and zip code
            iScanfCnt = sscanf(szInputBuffer, "%30[^,],%20[^,],%2[^,],%5[^\n]\n" // Input MUST BE in EXACT format
                , customer.szStreetAddress   // 30 character max
                , customer.szCity            // 20 character max
                , customer.szStateCd         // 2 character max
                , customer.szZipCd);         // 5 character max
            
            // Check for valid customer address information
            if(iScanfCnt < 4)
            {
                printf("%s: %s", ERR_CUSTOMER_ADDRESS_DATA, szInputBuffer); // don't exit this time use printf instead
            }

            printf("%s\n%s %s %s\n", customer.szStreetAddress, customer.szCity  // Print customer address information
                , customer.szStateCd, customer.szZipCd);
        }

        /*****************************_Trasaction processing_************************************/ 
       
        //printf("(Late Day difference) * (Late Fee Per Day) = (Check Fee) > (Max Fee) ? (Late Fee)\n"); // Used for debugging
       
       // Format table for transaction data: transaction type, book id, and date stamp
        printf("%-7s%-11s%-10s\n", "Trans", "Book", "Date");
       
       while(fgets(szInputBuffer, MAX_LINE_SIZE, pFileCust) != NULL)
        {
            // reset scanf counter
            iScanfCnt = 0;

            // Taking in line including:
            //      transaction type    (1 character max)
            //      book id             (9 character max)
            //      transaction dest.   (10 char max)
            iScanfCnt = sscanf(szInputBuffer, "%1c %9s %10s", &trans.cTransType, trans.szBookId, trans.szTransDt);
            
            // check for valid transaction data information
            if(iScanfCnt < 3)
            {
                printf("%s: %s", ERR_TRANSACTION_DATA, szInputBuffer); // don't exit this time use printf and continue
            }

            // check if customer transaction record is finished reading in
            if(strcmp(trans.szBookId, "END") == 0)
                break;
            
            // print formatted trasaction values from transaction structure
            printf("%3c%13s%12s\t", trans.cTransType, trans.szBookId, trans.szTransDt);
            
            customer.dFeeBalance += processTransaction(bookM, iBookCount, customer, trans); // Process customer trasaction
            // And return a fee which will be added onto the customer's initial late fee balance.
        }
         
        printf("%43s %.2lf\n", "Total Fees =", customer.dFeeBalance); // Print customer's total fees at end of trasaction
       
       /* Used for debugging purposes printing out the the library book information that has been modifiend by each customer
          transaction. Break statement is used to break out of first customer transaction to make processing a bit easier
          before trying to process ALL of the customer transactions

        printCompLibrary(bookM, bookComp,  iBookCount);
        break;
        */
    }
}
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
            iKey = findBook(bookM, iBookCount, transaction.szBookId); // Find book in the library
            
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
            iKey = findBook(bookM, iBookCount, transaction.szBookId); // Find out where book is in the library
            
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

/**********************************************************
int findBook(Book bookM[], int iBookCount, char szBookId[]

Purpose:
    Finds book in the bookM[] arrat by matching its Book Id

Parameters:
    Book bookM[]        Array holding books with individual book information
    int iBookCount      Integer holding size of bookM[] array
    char szBookId[]     Null terminated string holding book ID string

Results
    Returns the index of the book found in bookM[] array.
    If a book is not found it returns -1.

Notes:
    strcmp() is used and is case sensitive so book information
    NEEDS to be exact.

**********************************************************/
int findBook(Book bookM[], int iBookCount, char szBookId[])
{
    int iIndex = 0;

    while(iIndex < iBookCount)  // While counting through bookM[] array try to find the book
    {
        if(strcmp(bookM[iIndex].szBookId, szBookId) == 0)   // Compare book ID's for a match
            return iIndex;                                  // return book found index
        iIndex++;
    }

    return -1; // Book Not Found
}

/******************** processCommandSwitches *****************************
void processCommandSwitches(int argc, char *argv[], char **ppszCustomerFileName, char **ppszLibraryFileName)
Purpose:
    Checks the syntax of command line arguments and returns the filenames.
    If any switches are unknown, it exits with an error.
Parameters:
    I   int argc                        count of command line arguments
    I   char *argv[]                    array of command line arguments
    O   char **ppszCustomerFileName     customer transaction file name
    O   char **ppszLibraryFileName      library book file name
Notes:
    If a -? switch is passed, the usage is printed and the program exits
    with USAGE_ONLY.
    If a syntax error is encountered (e.g., unknown switch), the program
    prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
**************************************************************************/
void processCommandSwitches(int argc, char *argv[], char **ppszCustomerFileName, char **ppszLibraryFileName)
{
    int i; 

    for (i = 1; i < argc; i++)
    {
        // check for a switch
        if (argv[i][0] != '-')
            exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        // determine which switch it is
        switch (argv[i][1])
        {
            case 'b':                   // Customer Transaction File Name switch
                if (++i >= argc)
                    exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
                else
                    *ppszLibraryFileName = argv[i];
                break;
            
            case 'c':                   // Customer Transaction File Name switch
                if (++i >= argc)
                    exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
                else
                    *ppszCustomerFileName = argv[i];
                break;
            
            case '?':
                exitUsage(USAGE_ONLY, "", "");
                break;
            default:
                exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        }
        
        // Used for debugging purposes making sure pointer are pointing to correct file name
        // printf("\ncustomer file name: %s\nLibrary book file name: %s\n", *ppszCustomerFileName
        //      , *ppszLibraryFileName); 
        
    }
}

/******************** exitError *****************************
    void exitError(char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    Prints an error message and diagnostic to stderr.  Exits with
    ERROR_PROCESSING.
Parameters:
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitError(char *pszMessage, char *pszDiagnosticInfo)
{
    fprintf(stderr, "Error: %s %s\n"
        , pszMessage
        , pszDiagnosticInfo);
    exit(ERROR_PROCESSING);
}
/******************** exitUsage *****************************
    void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    If this is an argument error (iArg >= 0), it prints a formatted message
    showing which argument was in error, the specified message, and
    supplemental diagnostic information.  It also shows the usage. It exits
    with ERR_COMMAND_LINE_SYNTAX.

    If this is just asking for usage (iArg will be -1), the usage is shown.
    It exits with USAGE_ONLY.
Parameters:
    I int iArg                      command argument subscript
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
    if (iArg >= 0)
        fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
            , iArg
            , pszMessage
            , pszDiagnosticInfo);
    fprintf(stderr, "p2 -b libraryBookFile -c customerTransactionFile\n");
    if (iArg >= 0)
        exit(-1);
    else
        exit(-2);
}
/******************** getLibrary *****************************
int getLibrary(Book bookM[])
Purpose:
    Retrieves the books using the FILE pointer, pFileBook, that 
    you defined above the main function and returns a count of the number of books.
Parameters:
    O   Book bookM[]    an array which is used for returning the books.
Returns:
    A count of the number of read.
Notes:
    1. Uses pFileBook as the FILE pointer for reading the file.  It must
       have been opened with fopen prior to calling this function.
    2. The data in the data file is in this format
    szBookId szCustomerId szCheckedOutDt dLateFeePerDay dMaxLateFee szTitle
    9s        6s             10s           lf            lf          40s (may contain spaces)
**************************************************************************/
int getLibrary(Book bookM[])
{
    int i = 0;
    char szInputBuffer[100];
    int iScanfCnt = 0;
    // Read the books until EOF
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
    return i;
}
/******************** validateDate ***********************************
int validateDate(char szDate[], UtsaDate *pDate);
Purpose:
    Validates the date and returns (via the second parameter) the 
    UtsaDate.   
Parameters:
    I char szDate[]         Date as a string in the form "yyyy-mm-dd"
    O UtsaDate *pDate       Address of a UtsaDate structure for 
                            returning the date.
Notes:
    1. The length must be 10 characters.
    2. The date must be in the form "yyyy-mm-dd".
    3. The month must be 01-12.
    4. The day must be between 1 and the max for each month
               Mar 31 Aug 31 Jan 31
               Apr 30 Sep 30 Feb 29
               May 31 Oct 31
               Jun 30 Nov 30
               Jul 31 Dec 31
    5. If Feb 29 was specified, validate that the year is a leap year.
Return Value:
    0     date is valid
    1     year is invalid
    2     month is invalid
    3     day is invalid
    4     invalid length or format
**********************************************************************/
int validateDate(char szDate[], UtsaDate *pDate)
{
    static int iDaysPerMonth[] = 
       { 0, 31, 29, 31
          , 30, 31, 30
          , 31, 31, 30
          , 31, 30, 31 };
    int iCharCnt = 0;
    int iScanfCnt;

    // Check for too few characters for the yyy-mm-dd format
    if (strlen(szDate) != 10)
        return 4;  // invalid format due to length
    
    // The year should be 4 characters 
    iCharCnt = strspn(szDate, "0123456789");
    if (iCharCnt != 4)
        return 1;  // invalid year
    
    // Use sscanf to pluck out the year, month, and day
    iScanfCnt = sscanf(szDate, "%4d-%2d-%2d"
        , &pDate->iYear
        , &pDate->iMonth
        , &pDate->iDay);
    // If sscanf returned less than 3, then something was bad
    if (iScanfCnt < 3)
        return 4;  // invalid format
    
    // Validate Month
    if (pDate->iMonth < 1 || pDate->iMonth > 12)
        return 2;  // month invalid
    
    // Validate day based on max days per month 
    if (pDate->iDay < 1 || pDate->iDay > iDaysPerMonth[pDate->iMonth])
        return 3;  // day invalid

    // if the 29th of Feb, check for leap year
    if (pDate->iDay == 29 && pDate->iMonth == 2)
    {
        if (pDate->iYear % 4 == 0 && (pDate->iYear % 100 != 0 || pDate->iYear % 400 == 0))
            return 0;    // it is a leap year
        else return 3;   // not a leap year, so the day is invalid
    }
    return 0;
}
/******************** dateDiff ***********************************
int dateDiff(char szDate1[], char szDate2[])
Purpose:
    Validates the dates and returns the difference in days of the 
    first date minus the second date.   
Parameters:
    I char szDate1[]        First date as a string in the form "yyyy-mm-dd"
    I char szDate2[]        Second date as a string in the form "yyyy-mm-dd"
Notes:
    1. We validate/convert the days to UtsaDate format.  If the date is
       invalid, we exit and show a message.
    2. For each of the dates, we determine the number of days since
       "0000-03-01" by starting the count at 1 for 0000-03-01. Using
       March 1st eliminates some leap day issues. 
    3. Return the difference in days
Return Value:
    the difference in dates
**********************************************************************/
int dateDiff(char szDate1[], char szDate2[])
{
    UtsaDate date1;
    UtsaDate date2;
    int iJulian1;
    int iJulian2;
  
    if (validateDate(szDate1, &date1) != 0)
        exitError("Invalid 1st date for dateDiff: ", szDate1);

    if (validateDate(szDate2, &date2) != 0)
        exitError("Invalid 2nd date for dateDiff: ", szDate2);

    iJulian1 = utsaDateToUtsaJulian(date1);
    iJulian2 = utsaDateToUtsaJulian(date2);

    return iJulian1 - iJulian2;
}

/******************** utsaDateToUtsaJulian ***********************************
int utsaDateToUtsaJulian(UtsaDate date)
Purpose:
    Converts a date to a UTSA Julian Days value.  This will start numbering
    at 1 for 0000-03-01. Making dates relative to March 1st helps eliminate
    some leap day issues. 
Parameters:
    I char szDate1[]        First date as a string in the form "yyyy-mm-dd"
    I char szDate2[]        Second date as a string in the form "yyyy-mm-dd"
Notes:
    1 We replace the month with the number of months since March.  
      March is 0, Apr is 1, May is 2, ..., Jan is 10, Feb is 11.
    2 Since Jan and Feb are before Mar, we subtract 1 from the year
      for those months.
    3 Jan 1 is 306 days from Mar 1.
    4 The days per month is in a pattern that begins with March
      and repeats every 5 months:
           Mar 31 Aug 31 Jan 31
           Apr 30 Sep 30
           May 31 Oct 31
           Jun 30 Nov 30
           Jul 31 Dec 31
       Therefore:
           Mon  AdjMon  NumberDaysFromMarch (AdjMon*306 + 5)/10
           Jan    10      306
           Feb    11      337
           Mar     0        0
           Apr     1       31
           May     2       61
           Jun     3       92
           Jul     4      122 
           Aug     5      153
           Sep     6      184
           Oct     7      214
           Nov     8      245
           Dec     9      275
    5 Leap years are 
           years that are divisible by 4 and
           either years that are not divisible by 100 or 
           years that are divisible by 400
Return Value:
    the number of days since 0000-03-01 beginning with 1 for 
    0000-03-01.
**********************************************************************/
int utsaDateToUtsaJulian(UtsaDate date)
{
    int iCountDays;
    // Calculate number of days since 0000-03-01

    // If month is March or greater, decrease it by 3.
    if (date.iMonth > 2)
        date.iMonth -= 3;
    else
    {
        date.iMonth += 9;  // adjust the month since we begin with March
        date.iYear--;      // subtract 1 from year if the month was Jan or Feb
    }
    iCountDays = 365 * date.iYear                                // 365 days in a year
        + date.iYear / 4 - date.iYear / 100 + date.iYear / 400   // add a day for each leap year
        + (date.iMonth * 306 + 5) / 10                           // see note 4
        + (date.iDay );                                          // add the days
    return iCountDays;
}
