#ifndef BORROWING_H_INCLUDED
#define BORROWING_H_INCLUDED
#define MAX_BORROWINGS_SIZE 300

typedef struct date
{
    int day;
    int month;
    int year;
}date;

typedef struct borrowing
{
    int ID;
    char isbn[100];
    date Borrowed;
    date Due;
    date Returned;
    int returned;
}borrowing;

extern int BORROWINGS_SIZE;
extern borrowing Borrowings[MAX_BORROWINGS_SIZE];
extern char borrowingsFile[];

//fgets date in the format: dd/mm/yyyy
date scanDate();

//Constructor for the date struct
date constructDate(int day, int month, int year);

/*
constructor for the borrowing struct
date initialized with 0/0/0
*/
borrowing constructBorrowing(char*, int,date, date,date,int);

/*
Borrowing function takes user ID, Book isbn, due and borrowing dates
Validate user's ID and book's ISBN
Validate that the user has a maximum of 3 borrows at the same time
Validate that there is still copies of the required book before borrowing
*/
int borrow(char*isbn, int ID, date Borrowed, date Due);

//Return borrowing function that takes book's ISBN, user's ID and date returned
int returnBorrowing(char*isbn, int ID, date Returned);

//Read borrowings from file with the name fileName using fgets
//sort borrowings based on most borrowed
void readBorrowings(char* fileName);

//Write Borrowings array into file with the name fileName
void writeBorrowing(char* fileName);

//Print all borrowings info
void printAllBorrowings();

//Print the ith borrowing info in the Borrowings array
void printBorrowing(int i);

//Check if date d1 comes before date d2 //returns true if date 2 is before/equal date 1
int inTime(date d1, date d2);

//Print overdue books by comparing current date with due date
void printOverDue();

//Check if two dates are equal
int isEqual(date,date);
#endif // BORROWING_H_INCLUDED
