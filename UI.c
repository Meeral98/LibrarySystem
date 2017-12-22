#include "user.h"
#include "UI.h"
#include "book.h"
#include <time.h>
extern Book Library[100];
extern n;
extern usersFile[];
extern borrowFile[];
void mainMenu()
{
    printf("Please choose one of the Following:\n");
    printf("Book Management:(1)\nMemember Management:(2)\nBorrow Management:(3)\nAdministrative Actions:(4)\nSave Changes:(5)\nExit:(6)\n");
    char input;
    scanf("%c",&input);
    getchar();
    switch(input)
    {
        case'1':system("cls");
                bookManagement();
                break;
        case'2':system("cls");
                userManagement();
                break;
        case'3':system("cls");
                borrowManagement();
                break;
        case'4':system("cls");
                administrativeActions();
                break;
        case'5':saveUsers(usersFile);
                write_books();
                saveBorrow(borrowFile);
                printf("Successfully Saved!\n");
                break;
        case'6':printf("Do you want to save changes before exit? Enter Y or N ");
                scanf("%c",&input);
                if(input=='Y'||input=='y')
                {
                    saveUsers("D:/Codes/Uni/books.cont/abc.txt");
                    write_books();
                    saveBorrow(borrowFile);
                    printf("Successfully Saved!\n");
                }
                exit(0);
        default:printf("Please enter a valid entry\n");
    }
    mainMenu();
}
void userManagement()
{
    printf("User Management:\n");
    printf("Add new user:(1)\nDelete user:(2)\nBack:(3)\n");
    char input;
    scanf("%c",&input);
    getchar();
    if(input=='1')
        if(n==100)
            printf("USER LIMIT REACHED!\n");
        else
            addUser();
    else if(input=='2')
    {
        int id;
        printf("Enter user ID:");
        scanf("%d",&id);
        getchar();
        int k=deleteUser(id);
        if(k==-1)
            printf("User not found\n");
        else
            printf("Successfully Deleted!\n");
    }
    else if(input=='3')
    {
        system("cls");
        mainMenu();
    }
    else
        printf("Please enter a valid entry\n");
    userManagement();
}
void bookManagement()
{
    printf("Book Management:\n");
    printf("Insert New Book:(1)\nSearch for a book:(2)\nAdd New Copies:(3)\nDelete:(4)\nEdit:(5)\nBack:(6)\n");
    char input,ispn[30];
    int x;
    scanf("%c",&input);
    getchar();
    switch(input)
    {
        case'1':readBook();
                break;
        case'2':printf("Enter Book ISPN: ");
                scanf("%s",ispn);
                getchar();
                x=search(ispn);
                if(x==-1)
                    printf("Book not found!\n");
                else
                    printBook(x);
                break;
        case'3':printf("Enter Book ISPN: ");
                scanf("%s",ispn);
                getchar();
                x=search(ispn);
                if(x==-1)
                    printf("Book not found!\n");
                else
                {
                    printf("Enter number of new copies: ");
                    int c;
                    scanf("%d",&c);
                    getchar();
                    Library[x].Copies+=c;
                    Library[x].Copies_left+=c;
                }
                break;
        case'4':printf("Enter Book ISPN: ");
                scanf("%s",ispn);
                getchar();
                delete(ispn);
                break;
        case'5':
        case'6':system("cls");
                mainMenu();
                break;
        default:printf("Please enter a valid entry\n");
    }
    bookManagement();
}
void borrowManagement()
{
    printf("Borrow Management:\n");
    printf("Borrow:(1)\nReturn:(2)\nBack:(3)\n");
    char input;
    int ID;
    char ispn[30];
    date Borrowed,Due,Returned;
    scanf("%c",&input);
    getchar();
    if(input=='1')
    {
        printf("Enter User ID: ");
        scanf("%d",&ID);
        printf("Enter Book ISPN: ");
        scanf("%s",ispn);
        getchar();
        printf("Enter Due Date: ");
        Due=scanDate();
        getchar();
        char buffer[26];
        time_t t=time(NULL);
        struct tm tm=*localtime(&t);
        Borrowed=constructDate(tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
        if(borrow(ispn,ID,Borrowed,Due)==1)
            printf("Successfully Borrowed!\n");
        else
            printf("Borrow Unsuccessful!\n");
    }
    else if(input=='2')
    {
        printf("Enter User ID: ");
        scanf("%d",&ID);
        printf("Enter Book ISPN: ");
        scanf("%s",ispn);
        getchar();
        printf("Enter date of return: ");
        Returned=scanDate();
        getchar();
        if(returnBorrow(ispn,ID,Returned)==1)
            printf("Successfully Returned!\n");
        else
            printf("Return Unsuccessful!\n");
    }
    else if(input=='3')
    {
        system("cls");
        mainMenu();
    }
    else
        printf("Please enter a valid entry\n");
    borrowManagement();
}
void administrativeActions()
{
    printf("Administrative Actions:\n");
    printf("Print User Data:(1)\nPrint Book Data:(2)\nPrint Borrow Data:(3)\nPrint Overdue Books:(4)\nPrint Most Popular Books:(5)\nBack:(6)\n");
    char input;
    scanf("%c",&input);
    getchar();
    switch(input)
    {
        case'1':printUser();
                break;
        case'2':printBooks();
                break;
        case'3':printBorrow();
                break;
        case'5':printBook(mostPopular());
                break;
        case'6':system("cls");
                mainMenu();
                break;
        default:printf("Please enter a valid entry\n");
    }
    administrativeActions();
}
