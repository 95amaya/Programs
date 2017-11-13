/**********************************************************************
cs1713p1.h
Purpose:
    Defines typedefs for
        Customer - includes email address, full name, birthdate, 
                   and postal address
        Transaction - either a Checkout or Return of a book
    Defines constants for
        boolean values
        error messages
        program return codes
    Prototypes
Notes:
    
**********************************************************************/

/**** typedefs ****/

// Customer information 
typedef struct
{
    char        szCustomerId[7];            // 6 character customer ID
    char        szEmailAddr[41];            // customer's email address is used
                                            // to uniquely define a customer
    char        szFullName[31];             // customer full name
    char        szStreetAddress[31];        // street number, street name, and 
                                            // (optional) apartment number
    char        szCity[21];                 // address city
    char        szStateCd[3];               // address state code
    char        szZipCd[6];                 // address zip code
    double      dFeeBalance;                // amount this customer owes in fees
} Customer;

// Customer Transaction
typedef struct
{
    char cTransType;                       // C - check out, R - return
    char szBookId[10];                     // Individual Book Id (not ISBN since
                                           // multiple copies have the same value)
    char szTransDt[11];                    // Date for the transaction
} Transaction;

/**** constants ****/
// Maximum sizes 
#define MAX_LINE_SIZE 100

// boolean
#define FALSE           0
#define TRUE            1

/*  Error Messages */
#define ERR_MISSING_SWITCH          "missing switch"
#define ERR_EXPECTED_SWITCH         "expected switch, found"
#define ERR_MISSING_ARGUMENT        "missing argument for"
#define ERR_CUSTOMER_FILENAME       "invalid customer transaction file name"
#define ERR_CUSTOMER_ID_DATA        "invalid customer id data"
#define ERR_CUSTOMER_ADDRESS_DATA   "invalid customer address data"
#define ERR_TRANSACTION_DATA        "invalid customer transaction data"

/* program return codes */
#define ERR_COMMAND_LINE_SYNTAX     -1      // invalid command line syntax
#define USAGE_ONLY                  -2      // show usage only
#define ERROR_PROCESSING            -3

/* prototypes */

/* functions you must code  */
void processCustomers();

void exitError(char *pszMessage, char *pszDiagnosticInfo);
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo);