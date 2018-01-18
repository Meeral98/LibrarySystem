#include "borrowing.h"
#include "user.h"
#include "book.h"
#include "time.h"
#include <stdio.h>
borrowing Borrowings[MAX_BORROWINGS_SIZE];
int BORROWINGS_SIZE=0;

/*
Borrowing function takes user ID, Book isbn, due and borrowing dates
Validate user's ID and book's ISBN
Validate that the user has a maximum of 3 borrows at the same time
Validate that there is still copies of the required book before borrowing
*/
int borrow(char*isbn, int ID, date Borrowed, date Due)
{
    int i=findUser(ID);
    int k=findBook(isbn);
    if(i==-1)
    {
        printf("User ID not found!\n");
        if(k==-1)
            printf("Book ISBN not found!\n");
    }
    else
    {
        if(k==-1)
            printf("Book ISBN not found!\n");
        else
        {
            if(Users[i].borrows==3)
            {
                printf("User Borrowing Limit exceeded!\n");
                if(Library[k].Copies_left==0)
                    printf("Book is out of available copies!\n");
            }
            else
            {
                if(Library[k].Copies_left==0)
                    printf("Book is out of available copies!\n");
                else
                {
                    Users[i].borrows++;
                    Library[k].borrowed++;
                    Library[k].Copies_left--;
                    Borrowings[BORROWINGS_SIZE]=constructBorrowing(isbn,ID,Borrowed,Due,constructDate(0,0,0),0);
                    BORROWINGS_SIZE++;
                    int i;
                    book temp;
                    for(i=k;i>0;i--)
                    {
                        if(Library[i].borrowed>Library[i-1].borrowed)
                        {
                            temp=Library[i];
                            Library[i]=Library[i-1];
                            Library[i-1]=temp;
                        }
                        else
                            break;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

//Return borrowing function that takes book's ISBN, user's ID and date returned
int returnBorrowing(char* isbn, int ID, date Returned)
{
    int i=findUser(ID);
    int k=findBook(isbn);
    int j;
    for(j=0;j<BORROWINGS_SIZE;j++)
    {
        if(Borrowings[j].returned)
            continue;
        if(Borrowings[j].ID==ID)
        {
            if(strcmp(Borrowings[j].isbn,isbn)==0)
                break;
        }
    }
    if(j==BORROWINGS_SIZE)
        return 0;
    Borrowings[j].returned=1;
    Users[i].borrows--;
    Library[k].Copies_left++;
    Borrowings[j].Returned.day=Returned.day;
    Borrowings[j].Returned.month=Returned.month;
    Borrowings[j].Returned.year=Returned.year;
    return 1;
}

//Constructor for the date struct
date constructDate(int d, int m, int y)
{
    date Date;
    Date.day=d;
    Date.month=m;
    Date.year=y;
    return Date;
}

//fgets date in the format: dd/mm/yyyy
date scanDate()
{
    int d,m,y;
    char buffer[11];
    fgets(buffer,sizeof(buffer),stdin);
    fflush(stdin);
    d=atoi(strtok(buffer,"/"));
    m=atoi(strtok(NULL,"/"));
    y=atoi(strtok(NULL,"\n"));
    return constructDate(d,m,y);
}

/*
constructor for the borrowing struct
date initialized with 0/0/0
*/
borrowing constructBorrowing(char*isbn, int ID, date b, date d, date r, int ret)
{
    borrowing Borrowing;
    strcpy(Borrowing.isbn,isbn);
    Borrowing.ID=ID;
    Borrowing.Borrowed=b;
    Borrowing.Due=d;
    Borrowing.Returned=r;
    Borrowing.returned=ret;
    return Borrowing;
}

//Write Borrowings array into file with the name fileName
void writeBorrowings(char* fileName)
{
    FILE*f=fopen(fileName,"w");
    int i;
    for(i=0;i<BORROWINGS_SIZE;i++)
        fprintf(f,"%s, %d, %d/%d/%d, %d/%d/%d, %d/%d/%d\n",Borrowings[i].isbn,Borrowings[i].ID,Borrowings[i].Borrowed.day,Borrowings[i].Borrowed.month,
        Borrowings[i].Borrowed.year,Borrowings[i].Due.day,Borrowings[i].Due.month,Borrowings[i].Due.year,Borrowings[i].Returned.day,Borrowings[i].Returned.month,Borrowings[i].Returned.year);
    fclose(f);
}

//Print all borrowings info
void printAllBorrowings()
{
    int i;
    for(i=0;i<BORROWINGS_SIZE;i++)
        printBorrowing(i);
}

//Print the ith borrowing info in the Borrowings array
void printBorrowing(int i)
{
    printf("%s, %d, %d/%d/%d, %d/%d/%d, %d/%d/%d\n",Borrowings[i].isbn,Borrowings[i].ID,Borrowings[i].Borrowed.day,Borrowings[i].Borrowed.month,Borrowings[i].Borrowed.year,Borrowings[i].Due.day,Borrowings[i].Due.month,
           Borrowings[i].Due.year,Borrowings[i].Returned.day,Borrowings[i].Returned.month,Borrowings[i].Returned.year);
}

//Read borrowings from file with the name fileName using fgets
//sort borrowings based on most borrowed
void readBorrowings(char* fileName)
{
    FILE* file=fopen(fileName,"r");
    char buffer[200];
    int counter=0;

    if(file!=NULL){
        while(fgets(buffer,200,file)){
            char  *isbn, *issue_date, *due_date, *date_returned;
            int *id;
            isbn=strtok(buffer,",");
            id=atoi(strtok(NULL,","));
            issue_date=strtok(NULL,",")+1;
            due_date=strtok(NULL,",")+1;
            date_returned=strtok(NULL,",")+1;

            int d=atoi(strtok(issue_date,"/"));
            int m=atoi(strtok(NULL,"/"));
            int y=atoi(strtok(NULL,"/"));
            date issue=constructDate(d, m, y);
            d=atoi(strtok(due_date,"/"));
            m=atoi(strtok(NULL,"/"));
            y=atoi(strtok(NULL,"/"));
            date due=constructDate(d, m, y);
            int ret=strcmp(date_returned,"0/0/0\n")==0? 0 : 1;
            d=atoi(strtok(date_returned,"/"));
            m=atoi(strtok(NULL,"/"));
            y=atoi(strtok(NULL,"/"));
            date returned=constructDate(d, m, y);

            Borrowings[counter]=constructBorrowing(isbn, id, issue, due, returned,ret);

            int user_index=findUser(id);
            int book_index=findBook(isbn);
            if(book_index!=-1)
                Library[book_index].borrowed++;

            if(user_index!=-1 && book_index!=-1){
                if(!Borrowings[counter].returned)
                    Users[user_index].borrows++;
            }
            counter++;
        }
        BORROWINGS_SIZE=counter;
        int i,j,maxIndex;
        book temp;
        for(i=1;i<LIBRARY_SIZE;i++)
        {
            for(j=i;j>0;j--)
            {
                if(Library[j].borrowed>Library[j-1].borrowed)
                {
                    temp=Library[j];
                    Library[j]=Library[j-1];
                    Library[j-1]=temp;
                }
                else
                    break;
            }
        }
    }
    else
        printf("File not found\n");
    fclose(file);
}

//Check if date d1 comes before date d2 //returns true if date 2 is before/equal date 1
int inTime(date d1,date d2)
{
    if(d2.year==d1.year)
    {
        if(d2.month==d1.month)
        {
            if(d2.day<=d1.day)
                return 1;
            return 0;
        }
        if(d2.month<d1.month)
            return 1;
        return 0;
    }
    if(d2.year<d1.year)
        return 1;
    return 0;
}

//Print overdue books by comparing current date with due date
void printOverDue()
{
    int counter=0;
    int i;
    time_t t=time(NULL);
    struct tm tm=*localtime(&t);
    date currentDate=constructDate(tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
    for(i=0;i<BORROWINGS_SIZE;i++)
    {
        if((inTime(Borrowings[i].Due,currentDate))||(Borrowings[i].Returned.day!=0))
            continue;
        printBorrowing(i);
    }
}

//Check if two dates are equal
int isEqual(date d1,date d2)
{
    if((d1.day==d2.day)&&(d1.month==d2.month)&&(d1.year==d2.year))
        return 1;
    return 0;
}
