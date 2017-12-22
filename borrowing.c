#include "borrowing.h"
#include "user.h"
#include "book.h"

extern user u[100];
extern Book Library[100];
extern borrowing b[300];
extern bSize;
extern CURRENT_SIZE;

int borrow(char*ispn,int ID,date Borrowed, date Due)
{
    int i=findUser(ID);
    int k=search(ispn);
    if(i==-1)
    {
        printf("User ID not found!\n");
        if(k==-1)
            printf("Book ISPN not found!\n");
    }
    else
    {
        if(k==-1)
            printf("Book ISPN not found!\n");
        else
        {
            if(u[i].borrows==3)
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
                    u[i].borrows++;
                    Library[k].borrowed++;
                    Library[k].Copies_left--;
                    b[bSize]=constructBorrowing(ispn,ID,Borrowed,Due);
                    bSize++;
                    printf("%d",bSize);
                    return 1;
                }
            }
        }
    }
    return 0;
}

int returnBorrow(char*ispn,int ID,date Returned)
{
    int i=findUser(ID);
    int k=search(ispn);
    int j;
    for(j=0;j<bSize;j++)
    {
        if(b[j].returned)
            continue;
        if(b[j].ID==ID)
        {
            if(strcmp(b[j].ispn,ispn)==0)
                break;
        }
    }
    if(j==bSize)
        return 0;
    b[j].returned=1;
    u[i].borrows--;
    Library[k].Copies_left++;
    b[j].Returned=Returned;
    return 1;


}

int mostPopular()
{
    int i,max=-1,res;
    for(i=0;i<CURRENT_SIZE;i++)
    {
        if(Library[i].borrowed>max)
        {
            res=i;
            max=Library[i].borrowed;
        }
    }
    return res;

}
date constructDate(int d,int m,int y)
{
    date Date;
    Date.day=d;
    Date.month=m;
    Date.year=y;
    return Date;
}
date scanDate()
{
    int d,m,y;
    scanf("%d/%d/%d",&d,&m,&y);
    return constructDate(d,m,y);
}
borrowing constructBorrowing(char*ispn,int ID,date b,date d)
{
    borrowing Borrowing;
    strcpy(Borrowing.ispn,ispn);
    Borrowing.ID=ID;
    Borrowing.Borrowed=b;
    Borrowing.Due=d;
    Borrowing.Returned=constructDate(0,0,0);
    Borrowing.returned=0;
    return Borrowing;
}
void saveBorrow(char*fileName)
{
    FILE*f=fopen(fileName,"w");
    int i;
    for(i=0;i<bSize;i++)
        fprintf(f,"%s, %d, %d/%d/%d, %d/%d/%d, %d/%d/%d\n",b[i].ispn,b[i].ID,b[i].Borrowed.day,b[i].Borrowed.month,b[i].Borrowed.year,b[i].Due.day,b[i].Due.month,b[i].Due.year,b[i].Returned.day,b[i].Returned.month,b[i].Returned.year);
    fclose(f);
}
void printBorrow()
{
    int i;
    for(i=0;i<bSize;i++)
        printf("%s, %d, %d/%d/%d, %d/%d/%d, %d/%d/%d\n",b[i].ispn,b[i].ID,b[i].Borrowed.day,b[i].Borrowed.month,b[i].Borrowed.year,b[i].Due.day,b[i].Due.month,b[i].Due.year,b[i].Returned.day,b[i].Returned.month,b[i].Returned.year);
}
void readBorrow(char*fileName)
{
    FILE*f=fopen(fileName,"r");
    int i;


}
