

/*
 * File: employee.c
 * ----------------
 * This program tests the functions defined for records of type
 * employeeRecordT and employeeT.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Type: string
 * ------------
 * The type string is identical to the type char *, which is
 * traditionally used in C programs.  The main point of defining a
 * new type is to improve program readability.   At the abstraction
 * levels at which the type string is used, it is usually not
 * important to take the string apart into its component characters.
 * Declaring it as a string emphasizes this atomicity.
 */

typedef char *string;



/*
 * Constants
 * ---------
 * MaxEmployees -- Maximum number of employees
 */

#define MaxEmployees 100

/*
 * Type: employeeRecordT
 * ---------------------
 * This structure defines a type for an employee record.
 */

typedef struct {
    string name;
    string title;
    string ssnum;
    double salary;
    int withholding;
} employeeRecordT;

/*
 * Type: employeeT
 * ---------------
 * This type definition introduces an employeeT as a
 * pointer to the same record type as before.
 */

typedef struct {
    string name;
    string title;
    string ssnum;
    double salary;
    int withholding;
} *employeeT;

/*
 * Type: payrollT
 * --------------
 * This type represents an entire collection of employees.  The
 * type definition uses a dynamic array of employeeT values to
 * ensure that there is no maximum bound imposed by the type.
 * The cost of this design is that the programmer must explicitly
 * allocate the storage for the array using NewArray.
 */

typedef struct {
    int nEmployees;
    employeeT *employees;
} *payrollT;

/*
 * Global variables
 * ----------------
 * staff       -- Array of employees
 * nEmployees  -- Number of employees
 * manager     -- Used to produce a figure for the code
 */

static employeeRecordT staff[MaxEmployees];
static int nEmployees;

static employeeRecordT manager = {
    "Ebenezer Scrooge", "Partner", "271-82-8183", 250.00, 1
};

/* Private function declarations */

static void InitEmployeeTable(void);
static payrollT CreatePayroll(employeeRecordT staff[], int nEmployees);
static void ListEmployees(payrollT payroll);
static double AverageSalary(payrollT payroll);
static void EmployeePayroll(payrollT payroll); // prints out payroll of employees
string ReadLine(FILE *infile);
string GetLine(void);

/* Main program */

main()
{
    payrollT payroll;

    InitEmployeeTable();
    payroll = CreatePayroll(staff, nEmployees);
    //ListEmployees(payroll); // used for error checking
    EmployeePayroll(payroll);
    
    /***   Free Memory  ***/
    int i;
    for (i = 0; i < nEmployees; i++) {
        free(payroll->employees[i]->name);
        free(payroll->employees[i]->title);
        free(payroll->employees[i]->ssnum);
        free(payroll->employees[i]);
    }
    free(payroll->employees);
    free(payroll);
}

static void InitEmployeeTable(void)
{
    employeeRecordT empRec;
	 
         // index counter, character flusher, scanf counter
        int i, c, iScanfCount, iWithholding;
        double dSalary;

	// Ask for employee size input
	printf("How many employees: ");
	iScanfCount = scanf("%i", &nEmployees);
//	printf("%i\n", nEmployees);

        // look for valid input within max employee range
	while(iScanfCount != 1 && (nEmployees <= 0 || nEmployees > MaxEmployees))
        {
            while((c = getchar()) != '\n' && c != EOF); // flushing input buffer
            printf("ERROR: Invalid Number\n");
            printf("How many employees: ");
	    iScanfCount = scanf("%i", &nEmployees);
        }
	
        for(i = 0; i < nEmployees; i++)
        {
                free(GetLine());
               
                printf("Employee #%i\n", i+1);
                printf("\tName: ");
                empRec.name = GetLine();
        //	printf("%s\n", empRec.name);
                
                printf("\tTitle: ");
                empRec.title = GetLine();
         //   printf("%s\n", *empRec.title);
            
                printf("\tSSN: ");
                empRec.ssnum = GetLine();
         //   printf("%s\n", *empRec.ssnum);
                
                printf("\tSalary: ");
                iScanfCount = scanf("%lf", &dSalary);
                while(iScanfCount != 1)
                {
                    while((c = getchar()) != '\n' && c != EOF); // flushing input buffer
                    printf("ERROR: Invalid Salary\n");
                    printf("\tSalary: ");
                    iScanfCount = scanf("%lf", &dSalary);
                }
                    
                empRec.salary = dSalary;
                printf("\tWithholding exceptions: ");
                iScanfCount = scanf("%i", &iWithholding);

                while(iScanfCount != 1)
                {
                    while((c = getchar()) != '\n' && c != EOF); // flushing input buffer
                    printf("ERROR: Invalid Exceptions\n");
                    printf("\tWithholding exceptions: ");
                    iScanfCount = scanf("%i", &iWithholding);
                }
                
                empRec.withholding = iWithholding;
                staff[i] = empRec;
	}
	
  /*  empRec.name = "Ebenezer Scrooge";
    empRec.title = "Partner";
    empRec.ssnum = "271-82-8183";
    empRec.salary = 250.00;
    empRec.withholding = 1;
    staff[0] = empRec; 
    empRec.name = "Bob Cratchit";
    empRec.title = "Clerk";
    empRec.ssnum = "314-15-9265";
    empRec.salary = 15.00;
    empRec.withholding = 7;
    staff[1] = empRec;
    nEmployees = 2; */
}

static payrollT CreatePayroll(employeeRecordT staff[], int nEmployees)
{
    payrollT payroll;
    int i;

    payroll = (payrollT) malloc(sizeof *payroll); // New(payrollT);
    payroll->employees = (employeeT *) malloc(nEmployees*sizeof(employeeT)); // NewArray(nEmployees, employeeT);
    payroll->nEmployees = nEmployees;
    for (i = 0; i < nEmployees; i++) {
        payroll->employees[i] = (employeeT)malloc(sizeof *((employeeT) NULL));   // (New(employeeT);
        payroll->employees[i]->name = staff[i].name;
        payroll->employees[i]->title = staff[i].title;
        payroll->employees[i]->ssnum = staff[i].ssnum;
        payroll->employees[i]->salary = staff[i].salary;
        payroll->employees[i]->withholding = staff[i].withholding;
    }
    return (payroll);
}

static void ListEmployees(payrollT payroll)
{
    int i;

    for (i = 0; i < payroll->nEmployees; i++) {
        printf("%s (%s)\n", payroll->employees[i]->name, payroll->employees[i]->title);
    }
}

static double AverageSalary(payrollT payroll)
{
    double total;
    int i;

    total = 0;
    for (i = 0; i < payroll->nEmployees; i++) {
        total += payroll->employees[i]->salary;
    }
    return (total / nEmployees);
}

static void EmployeePayroll(payrollT payroll)
{
	int i, iWithheld;
	double dTax, dNet, dSalary;
	printf("\n%-20s%10s%10s%12s\n", "Name", "Gross", "Tax", "Net");
	printf("----------------------------------------------------\n");
	
	for(i = 0; i < payroll->nEmployees; i++)
	{
		dSalary = payroll->employees[i]->salary;
		iWithheld = payroll->employees[i]->withholding;
		dTax = (dSalary - iWithheld) * 0.25;
		dNet = dSalary - dTax;
		printf("%-20s%10.2lf  -  %5.2lf   = %7.2lf\n", payroll->employees[i]->name, dSalary , dTax, dNet);
	}
        printf("\n");
        //printf("\nNumber of employess: %i\n", nEmployees);
}

/*
 * to read strings from user and dynamically allocate memory,
 * it might be good idea to use the following helper functions  
 * from the book lib 
 * 
 */
string ReadLine(FILE *infile)
{
    string line, nline;
    int n, ch, size;

    n = 0;
    size = 120;
    line = (string) malloc(size + 1);
    if(line==NULL) return NULL;
    while ((ch = getc(infile)) != '\n' && ch != EOF) {
        if (n == size) {
            size *= 2;
            nline = (string) malloc(size + 1);
            if(nline==NULL) {free(line); return NULL; }
            strncpy(nline, line, n);
            free(line);
            line = nline;
        }
        line[n++] = ch;
    }
    if (n == 0 && ch == EOF) {
        free(line);
        return (NULL);
    }
    line[n] = '\0';
    nline = (string) malloc(n + 1);
    if(nline==NULL) {free(line); return NULL; }
    strcpy(nline, line);
    free(line);
    return (nline);
}

string GetLine(void)
{
    return (ReadLine(stdin));
}

