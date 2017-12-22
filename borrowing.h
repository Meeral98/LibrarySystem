#ifndef BORROWING_H_INCLUDED
#define BORROWING_H_INCLUDED


typedef struct date
{
    int day;
    int month;
    int year;
}date;

typedef struct borrowing
{
    int ID;
    char ispn[30];
    date Borrowed;
    date Due;
    date Returned;
    int returned;
}borrowing;

date scanDate();
date constructDate(int day,int month,int year);
borrowing constructBorrowing(char*,int,date,date);
int borrow(char*ispn,int ID,date Borrowed,date Due);
int returnBorrow(char*ispn,int ID,date Returned);
void saveBorrow(char*);
void printBorrow();
void readBorrow(char*);
#endif // BORROWING_H_INCLUDED
