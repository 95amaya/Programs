/*
 * File: employee.c
 * ----------------
 * This program tests the functions defined for records of type
 * employeeRecordT and employeeT.
 */

#include <stdio.h>
#include <stdlib.h>

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

/* Main program */

main()
{
    payrollT payroll;

    InitEmployeeTable();
    payroll = CreatePayroll(staff, nEmployees);
    ListEmployees(payroll);
}

static void InitEmployeeTable(void)
{
    employeeRecordT empRec;

    empRec.name = "Ebenezer Scrooge";
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
    nEmployees = 2;
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
