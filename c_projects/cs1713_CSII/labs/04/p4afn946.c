/**********************************************************************
p4afn946.c by Michael Amaya
Purpose:
    This program reads book information and a command file.   It 
    processes the commands against the book information.
    This is the driver code for the routines written by the students.
Command Parameters:
    p4 -b bookFileName -c commandFileName
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
        BOOK NEW 

Results:
    Prints the Books prior to sorting
    Processes the commands (see above) and shows any errors.
    Prints the resulting Books
Returns:
    0  normal
    -1 invalid command line syntax
    -2 show usage only
    -3 error during processing, see stderr for more information

Notes:
    p4 -?       will provide the usage information.  In some shells,
                you will have to type p4 -\?

**********************************************************************/

// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs1713p4.h"

/******************** printBooks **************************************
    void printBooks(char *pszHeading, Node *pHead)
Purpose:
    Prints each book in a table format
Parameters:
    Node *pHead         copy of node that points to front of Book list
    I int iBookCnt        Number of elements in the bookM array.
Returns:
    n/a
Notes:
    
**************************************************************************/
void printBooks(char *pszHeading, Node *pHead)
{
    Node *p;
    printf("%s\n", pszHeading);

    // output column headings
    printf("   %-9s %-40s %-8s %-10s %-8s %-8s \n"
        , "Book Id", "Title", "Customer", "Ck Out Dt", "Late Fee", "Max Late");

    // output each book in a table format
    for (p = pHead; p != NULL; p = p->pNext)
    {
        printf("   %-9s %-40s %-8s %-10s %8.2lf %8.2lf \n"
            , p->book.szBookId
            , p->book.szTitle
            , p->book.szCustomerId
            , p->book.szCheckedOutDt
            , p->book.dLateFeePerDay
            , p->book.dMaxLateFee
            );
    }
    printf("\n");
}


/********************processCustomerCommand *****************************
    void processCustomerCommand(Node **ppHead
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
            -	Lookup the book ID using a linear search.  If not found, print a warning (but do not terminate your program) and return.
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
    Node **ppHead               ppHead points to front of Book list
    I   char  *pszSubCommand          Should be BEGIN, ADDRESS, REQUEST or COMPLETE
    I   char  *pzRemainingInput       Points to the remaining characters in the input
                                      line (i.e., the characters that following the
                                      subcommand).
    I/O Customer *pCustomer           The BEGIN subcommand begins a new customer.  
Notes:

**************************************************************************/
void processCustomerCommand(Node **ppHead
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
            iScanfCnt = sscanf(pszRemainingInput, "%1c %9s %10s", &transaction.cTransType
                , transaction.szBookId, transaction.szTransDt);
            
            // check for valid transaction data information
            if(iScanfCnt < 3)
            {
                printf("%s: %s", ERR_TRANSACTION_DATA, pszRemainingInput); // don't exit this time use printf and continue
            }

	    // print formatted trasaction values from transaction structure
            printf("%43c%13s%12s\t", transaction.cTransType, transaction.szBookId, transaction.szTransDt);
            
            pCustomer->dFeeBalance += processTransaction(ppHead, *pCustomer, transaction); // Process customer trasaction
            // And return a fee which will be added onto the customer's initial late fee balance.
    }
    else printf("   *** %s %s\n", ERR_CUSTOMER_SUB_COMMAND, pszSubCommand);
}
/********************processBookCommand *****************************
    void processBookCommand(Node **ppHead, char *pszSubCommand, char *pszRemainingInput)
Purpose:
    Processes the subcommands associated with the BOOK command:
        BOOK CHANGE szBookId dLateFeePerDay dMaxLateFee
            change the Late Fee Per Day and Max Late Fee to the specified values
        BOOK SHOW szBookId    
            requests a display of a particular book.  Show all of its information.
        BOOK NEW    
                
Parameters:
    Node **ppHead               ppHead points to front of Book list
    I   char  *pszSubCommand          Should be CHANGE or SHOW
    I   char  *pzRemainingInput       Points to the remaining characters in the input
                                      line (i.e., the characters that following the
                                      subcommand).
Notes:

**************************************************************************/
void processBookCommand(Node **ppHead, char *pszSubCommand, char *pszRemainingInput)
{
    Book book;
    int iScanfCnt = 0;
    Node *iKey = NULL;
    Node *pPrecedes = NULL;
    
    if(strcmp(pszSubCommand, "NEW") == 0)
    {
        Node *pCheck = NULL;
        iScanfCnt = sscanf(pszRemainingInput, "%9s %6s %10s %lf %lf %[^\n]\n"
            , book.szBookId
            , book.szCustomerId
            , book.szCheckedOutDt
            , &book.dLateFeePerDay
            , &book.dMaxLateFee
            , book.szTitle);
        
        pCheck = searchLL(*ppHead, book.szBookId, &pPrecedes);
        
        if(pCheck == NULL || strcmp(pCheck->book.szBookId, book.szBookId) != 0) // If book does not already exist insert into List
            insertLL(ppHead, book);  
        else
            printf("\t\t\t*** Book Already Exists\n");

        printf("\n");
    }
    else if(strcmp(pszSubCommand, "CHANGE") == 0)
    {
        iScanfCnt = sscanf(pszRemainingInput, "%9s %lf %lf\n", book.szBookId
            , &book.dLateFeePerDay, &book.dMaxLateFee);
        
        if(iScanfCnt < 3)
        {
            printf("%s: %s", ERR_CHANGE_SUB_COMMAND, pszRemainingInput); // don't exit this time use printf and continue
        }
        
        iKey = searchLL(*ppHead, book.szBookId, &pPrecedes);
        
        if(iKey != NULL)
        {
           // printf("Book: %s\tLate Fee: %.2lf\tMAX Late Fee: %.2lf\n", book.szBookId, book.dLateFeePerDay, book.dMaxLateFee);
            iKey->book.dLateFeePerDay = book.dLateFeePerDay;
            iKey->book.dMaxLateFee = book.dMaxLateFee;
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

        iKey = searchLL(*ppHead, book.szBookId, &pPrecedes);

        if(iKey != NULL) // if book can be found print it out
        {
            printf("   %-9s %-40s %-8s %-10s %8.2lf %8.2lf \n"
                , iKey->book.szBookId
                , iKey->book.szTitle
                , iKey->book.szCustomerId
                , iKey->book.szCheckedOutDt
                , iKey->book.dLateFeePerDay
                , iKey->book.dMaxLateFee
                );
        } 
        else printf("  ** Book Not Found\n");
        printf("\n");
    }
    else printf("   *** %s %s\n", ERR_CUSTOMER_SUB_COMMAND, pszSubCommand);
}
/******************** searchBooks *****************************
    Node * searchLL(Node *pHead, char *pszMatchBookId)
Purpose:
    Using a binary search, it finds the specified book in the booKM array.
Parameters:
    Node *ppHead               a copy of the node that points to front of Book list
    Node *pPrecedes             points to Node before the insertion of the new Node
    I   char *pszMatchBookId         Book Id to find in the array
Returns:
    != NULL  Node of where the match value was found
    NULL     not found
Notes:

**************************************************************************/
Node * searchLL(Node *pHead, char *pszMatchBookId, Node **ppPrecedes)
{
    Node *p;
    
    /*  Starting with the head of LL and traversing through each node by getting address 
        within node struture to the next Node */
    for(p = pHead; p != NULL; p = p->pNext)
    {
        if(strcmp(p->book.szBookId, pszMatchBookId) >=  0)  // Found match or found node after where match should go
            return p;
        *ppPrecedes = p;    
    }
    return NULL; // Book not found
}

/******************** InsertBook *****************************
    Node * insertLL(Node **ppHead, Book book)
Purpose:
    Using a linear search, it finds the specified book in the booK list.
Parameters:
    Node **ppHead               ppHead points to front of Book list
    I   char *pszMatchBookId         Book Id to find in the array
Returns:
    != NULL  Node of where the match value was found
    NULL     not found
Notes:

**************************************************************************/
Node * insertLL(Node **ppHead, Book book)
{
    Node *pNew = NULL;              // Node has reference in memory but what it references
    Node *pPrecedes = NULL;         // is NULL
   
    pNew = allocateNode(book);    // free up some space for new Book
    searchLL(*ppHead, book.szBookId, &pPrecedes); // Searching linked list for existing book
    
    // If new term belongs at the front of the list add it to the front and switch ppHead to point to it
    if(*ppHead == NULL || pPrecedes == NULL)                 
    {
        pNew -> pNext = *ppHead;    // If term belongs at front of list pNew points to rest of the list
        *ppHead = pNew;
    }
    // if new term does not belong at front of list insert it by having pPrecedes point to it 
    // and pNew -> pNext point to pPrecedes pNext
    else 
    {
        pNew -> pNext = pPrecedes -> pNext;
        pPrecedes -> pNext = pNew;          // pPrecedes should be pointing to pNew node
    }
   
    return pNew; // Book not found
}

/*** include your processTransaction code from program #2 ***/
/***********************************************************************************************
double processTransaction(Node *ppHead, Customer customer, Transaction transaction)

Purpose:
    Processs transaction requests and return any late fees inquired

Parameters:
    Node **ppHead               ppHead points to front of Book list
    Customer customer           Customer structure holding customer information
    Transaction transaction     Transaction structure holding trasaction information

Results:
    Customer transaction late fee. If there is not one it returns 0.
    
Notes:
    Checking out or Returning is not case sensitive to the input file.
    Key string "NONE" used book customer id information if 
    the book has not been checked out. 


***************************************************************************************************/

double processTransaction(Node **ppHead, Customer customer, Transaction transaction)
{
    double dFee = 0.0;  // only used in return case
    Node *iKey = NULL;  // used to find the book Node in Book Linked List
    Node *pPrecedes = NULL;
    switch(transaction.cTransType)
    {
        /***********************_CheckOut case_*******************************/
        case 'C': case 'c':
            iKey = searchLL(*ppHead, transaction.szBookId, &pPrecedes); // Find book in the library
            
            // Is book in the library?
            if(iKey != NULL)
            {
                // Check if book has been checked out already
                if(strcmp(iKey->book.szCustomerId, "NONE") == 0)
                {
                    strcpy(iKey->book.szCustomerId, customer.szCustomerId);    // copy customer customer ID into book customer ID
                    strcpy(iKey->book.szCheckedOutDt, transaction.szTransDt);  // copy customer transaction date into 
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
            iKey = searchLL(*ppHead, transaction.szBookId, &pPrecedes); // Find book in the library
            
            // Is library book in the library?
            if(iKey != NULL)
            {
                // Is it being returned by the right customer?
                if(strcmp(iKey->book.szCustomerId, customer.szCustomerId) == 0)
                {
                    //printf("Returning book.. Date Checked Out: %s", bookM[iKey].szCheckedOutDt); // used for debugging
                    
                    // find how many days late it was returned (14 day checkout period)
                    int lateReturn =  dateDiff(transaction.szTransDt, iKey->book.szCheckedOutDt) - 14; // Find out if
                                                                        // Book had been returned late
                    double dCheckFee = 0;       // Declare check fee double used to check against the MAX LATE FEE
                    
                    // Is the book Late?
                    if(lateReturn > 0)
                    {
                        dCheckFee = iKey->book.dLateFeePerDay * lateReturn; //Compute Associated fee
                        // Is the fee over the limit?
                        if(dCheckFee > iKey->book.dMaxLateFee)
                            dFee = iKey->book.dMaxLateFee; // Get the Max Late Fee
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
                    strcpy(iKey->book.szCustomerId, "NONE");           // Reset customer id in library
                    strcpy(iKey->book.szCheckedOutDt, "0000-00-00");   // Reset check out date in library

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
