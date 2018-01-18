#include "user.h"
#include "UI.h"
#include "book.h"
#include <time.h>
#include <stdio.h>

void saveAll(){
    writeUsers(usersFile);
    writeBooks(libraryFile);
    writeBorrowings(borrowingsFile);
    return;
}
void mainMenu()
{
    printf("Please choose one of the Following:\n");
    printf("Book Management:(1)\nMemember Management:(2)\nBorrow Management:(3)\nAdministrative Actions:(4)\nSave Changes:(5)\nExit:(6)\n");
    char input[2];
    fgets(input,2,stdin);
    fflush(stdin);
    switch(atoi(input))
    {
        case 1: system("cls");
                printf("Book Management:\n");
                bookManagement();
                break;
        case 2: system("cls");
                printf("User Management:\n");
                userManagement();
                break;
        case 3: system("cls");
                printf("Borrow Management:\n");
                borrowManagement();
                break;
        case 4: system("cls");
                printf("Administrative Actions:\n");
                administrativeActions();
                break;
        case 5: saveAll();
                printf("Successfully Saved!\n");
                break;
        case 6: printf("Do you want to save changes before exit? Enter Y or N ");
                char answer[2];
                fgets(answer,2,stdin);
                fflush(stdin);
                if(answer[0]=='Y'||answer[0]=='y')
                {
                    saveAll();
                    printf("Successfully Saved!\n");
                }
                exit(0);
        default:printf("Please enter a valid entry!\n");
    }
    mainMenu();
}
void userManagement()
{
    printf("Add new user:(1)\nDelete user:(2)\nBack:(3)\n");
    char input[2];
    fgets(input,2,stdin);
    fflush(stdin);
    if(atoi(input)==1)
    {
        if(USERS_SIZE==MAX_USERS_SIZE)
            printf("USER LIMIT REACHED!\n");
        else
            addUser();
    }
    else if(atoi(input)==2)
    {
        char id[11];
        printf("Enter user ID:");
        fgets(id,sizeof(id),stdin);
        fflush(stdin);
        int ret=deleteUser(atoi(id));
        if(ret==-1)
            printf("User not found!\n");
        else if(ret==0)
            printf("User still has unreturned books. Please return borrowed books then try again!\n");
        else
            printf("Successfully Deleted!\n");
    }
    else if(atoi(input)==3)
    {
        system("cls");
        mainMenu();
    }
    else
        printf("Please enter a valid entry!\n");
    userManagement();
}
void bookManagement()
{
    printf("Insert New Book:(1)\nSearch for a book:(2)\nAdd New Copies:(3)\nDelete:(4)\nEdit:(5)\nBack:(6)\n");
    char ispn[100];
    char input[2];
    fgets(input,2,stdin);
    fflush(stdin);
    int bookIndex;
    switch(atoi(input))
    {
        case 1: addBook();
                break;
        case 2: system("cls");
                printf("Search by Title:(1)\nSearch by Author:(2)\nSearch by ISBN:(3)\nSearch by Category:(4)\nBack:(5)\n");
                char entry[2];
                char key[100];
                fgets(entry,2,stdin);
                fflush(stdin);
                if(atoi(entry)==5)
                    bookManagement();
                printf("Enter Search Data: ");
                fgets(key,sizeof(key),stdin);
                key[strlen(key)-1]=0;
                fflush(stdin);
                if((atoi(entry)<1)||(atoi(entry)>4))
                {
                    printf("Invalid Input!\n");
                    bookManagement();
                }
                searchBook(key,atoi(entry));
                break;
        case 3: printf("Enter Book ISBN: ");
                fgets(ispn,sizeof(ispn),stdin);
                ispn[strlen(ispn)-1]=0;
                fflush(stdin);
                bookIndex=findBook(ispn);
                if(bookIndex==-1)
                    printf("Book not found!\n");
                else
                {
                    printf("Enter number of new copies: ");
                    char newCopies[10];
                    fgets(newCopies,sizeof(newCopies),stdin);
                    fflush(stdin);
                    if(atoi(newCopies)<0)
                    {
                        printf("Invalid number of copies!\n");
                        break;
                    }
                    Library[bookIndex].Copies+=atoi(newCopies);
                    Library[bookIndex].Copies_left+=atoi(newCopies);
                }
                break;
        case 4: printf("Enter Book ISBN: ");
                fgets(ispn,sizeof(ispn),stdin);
                ispn[strlen(ispn)-1]=0;
                fflush(stdin);
                if(deleteBook(ispn))
                    printf("Successfully Deleted!\n");
                else
                    printf("Book not found!\n");
                break;
        case 5: printf("Enter Book ISBN: ");
                fgets(ispn,sizeof(ispn),stdin);
                ispn[strlen(ispn)-1]=0;
                fflush(stdin);
                int index=findBook(ispn);
                if(index==-1)
                    printf("Book not found!\n");
                else
                {
                    system("cls");
                    printBook(index);
                    printf("Edit Title:(1)\nEdit Author:(2)\nEdit ISBN:(3)\nEdit Publisher:(4)\nEdit Category:(5)\nBack:(6)\n");
                    char n[2];
                    fgets(n,2,stdin);
                    fflush(stdin);
                    if(atoi(n)==6)
                        bookManagement();
                    printf("Enter new data: ");
                    char data[100];
                    fgets(data,sizeof(data),stdin);
                    if(editBooks(index,atoi(n),data)==1)
                        printf("Successfully Edited!\n");
                    else
                        printf("Invalid entry!");
                }
                break;
        case 6: system("cls");
                mainMenu();
                break;
        default:printf("Please enter a valid entry\n");
    }
    bookManagement();
}
void borrowManagement()
{
    printf("Borrow:(1)\nReturn:(2)\nBack:(3)\n");
    char ID[10], input[2];
    char ispn[100];
    date Borrowed,Due,Returned;
    fgets(input,2,stdin);
    fflush(stdin);
    if(atoi(input)==1)
    {
        printf("Enter User ID: ");
        fgets(ID,sizeof(ID),stdin);
        ID[strlen(ID)-1]=0;
        fflush(stdin);
        printf("Enter Book ISBN: ");
        fgets(ispn,sizeof(ispn),stdin);
        ispn[strlen(ispn)-1]=0;
        fflush(stdin);
        printf("Enter Due Date: ");
        Due=scanDate();
        fflush(stdin);
        time_t t=time(NULL);
        struct tm tm=*localtime(&t);
        Borrowed=constructDate(tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
        if(borrow(ispn,atoi(ID),Borrowed,Due)==1)
            printf("Successfully Borrowed!\n");
        else
            printf("Borrowing Unsuccessful!\n");
    }
    else if(atoi(input)==2)
    {
        printf("Enter User ID: ");
        fgets(ID,sizeof(ID),stdin);
        ID[strlen(ID)-1]=0;
        fflush(stdin);
        printf("Enter Book ISBN: ");
        fgets(ispn,sizeof(ispn),stdin);
        ispn[strlen(ispn)-1]=0;
        fflush(stdin);
        printf("Enter date of return: ");
        Returned=scanDate();
        fflush(stdin);
        if(returnBorrowing(ispn,atoi(ID),Returned))
            printf("Successfully Returned!\n");
        else
            printf("Return Unsuccessful!\n");
    }
    else if(atoi(input)==3)
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
    printf("Print User Data:(1)\nPrint Book Data:(2)\nPrint Borrow Data:(3)\nPrint Overdue Books:(4)\nPrint Most Popular Books:(5)\nBack:(6)\n");
    char input[2];
    fgets(input,2,stdin);
    fflush(stdin);
    switch(atoi(input))
    {
        case 1: printUsers();
                break;
        case 2: printLibrary();
                break;
        case 3: printAllBorrowings();
                break;
        case 4: printOverDue();
                break;
        case 5: printMostPopular();
                break;
        case 6: system("cls");
                mainMenu();
                break;
        default:printf("Please enter a valid entry\n");
    }
    administrativeActions();
}
