
#include "system.h"
#include "borrowing.h"
#include "user.h"
#include <time.h>
#define BOOK_NOT_FOUND -1
#include <stdio.h>

//Linear search by ISBN in Library //return -1 if book not found
int findBook (char* isbn){

    int i;
    for(i=0; i<LIBRARY_SIZE; i++){
        if(strcmp(Library[i].ISPN,isbn)==0)
            return i;
    }
        return BOOK_NOT_FOUND;
}

//Delete a book by ISBN in Library // swap the to-be-deleted-book by the last one and decrement library size by 1
int deleteBook (char* isbn){

    int index=findBook(isbn);
    if(index==-1)
        return 0;
    int i;
    for(i=0;i<BORROWINGS_SIZE;i++)
    {
        if((strcmp(Borrowings[i].isbn,isbn)==0)&&(Borrowings[i].returned==0))
        {
            Users[findUser(Borrowings[i].ID)].borrows--;
            time_t t=time(NULL);
            struct tm tm=*localtime(&t);
            Borrowings[i].Returned=constructDate(tm.tm_mday,tm.tm_mon,tm.tm_year);
            Borrowings[i].returned=1;
        }
    }
    Library[index]=Library[LIBRARY_SIZE-1];
    LIBRARY_SIZE--;
    return 1;
}

//fgets book informations and store it in Library
void addBook(){
        printf("Enter title: ");
        fgets(Library[LIBRARY_SIZE].Title,sizeof(Library[LIBRARY_SIZE].Title),stdin);
        Library[LIBRARY_SIZE].Title[strlen(Library[LIBRARY_SIZE].Title)-1]=0;
        fflush(stdin);

        printf("Enter author: ");
        fgets(Library[LIBRARY_SIZE].Author,sizeof(Library[LIBRARY_SIZE].Author),stdin);
        Library[LIBRARY_SIZE].Author[strlen(Library[LIBRARY_SIZE].Author)-1]=0;
        fflush(stdin);

        printf("Enter publisher: ");
        fgets(Library[LIBRARY_SIZE].Publisher,sizeof(Library[LIBRARY_SIZE].Publisher),stdin);
        Library[LIBRARY_SIZE].Publisher[strlen(Library[LIBRARY_SIZE].Publisher)-1]=0;
        fflush(stdin);

        printf("Enter ISBN: ");
        fgets(Library[LIBRARY_SIZE].ISPN,sizeof(Library[LIBRARY_SIZE].ISPN),stdin);
        Library[LIBRARY_SIZE].ISPN[strlen(Library[LIBRARY_SIZE].ISPN)-1]=0;
        fflush(stdin);
        if(findBook(Library[LIBRARY_SIZE].ISPN)!=-1)
        {
            printf("ISBN already exists!");
            return;
        }

        printf("Enter publishing date: ");
        fgets(Library[LIBRARY_SIZE].PubDate,sizeof(Library[LIBRARY_SIZE].PubDate),stdin);
        Library[LIBRARY_SIZE].PubDate[strlen(Library[LIBRARY_SIZE].PubDate)-1]=0;
        fflush(stdin);

        char num[9];
        printf("Enter copies: ");
        fgets(num,sizeof(num),stdin);
        num[strlen(num)-1]=0;
        fflush(stdin);
        Library[LIBRARY_SIZE].Copies=atoi(num);

        printf("Enter Copies_left: ");
        fgets(num,sizeof(num),stdin);
        num[strlen(num)-1]=0;
        fflush(stdin);
        Library[LIBRARY_SIZE].Copies_left=atoi(num);

        printf("Enter category: ");
        fgets(Library[LIBRARY_SIZE].Category,sizeof(Library[LIBRARY_SIZE].Category),stdin);
        Library[LIBRARY_SIZE].Category[strlen(Library[LIBRARY_SIZE].Category)-1]=0;
        fflush(stdin);

        LIBRARY_SIZE++;
        return;
}

//Print most popular books (first five books in the Borrowings array)
void printMostPopular(){
    printf("Most popular books:\n");
    int i=0;
    while(i<LIBRARY_SIZE && i<5){
        printf("%s\n",Library[i].Title);
        i++;
    }
}

//Print info of the ith book
void printBook(int i){
    printf("%s, %s, %s, %s, %s, %d, %d, %s\n",Library[i].Title, Library[i].Author, Library[i].Publisher, Library[i].ISPN,Library[i].PubDate, Library[i].Copies, Library[i].Copies_left, Library[i].Category);
}

//Print all Library books' info
void printLibrary(){
    int i;
    for(i=0;i<LIBRARY_SIZE;i++)
        printBook(i);
}

//Check if subs is a substring from main
int isSubstr(char* main, char* subs){
    int i,j;
    int dif=strlen(main)-strlen(subs);
    for(i=0; i<=dif; i++){
        for(j=0; j<strlen(subs); j++){
            if(tolower(main[i+j])!=tolower(subs[j]))
               break;
        }
        if(j==strlen(subs))
            return 1;
    }
    return 0;
}

//return the required book info based on entry
char* infoReq(int ind, int entry){
    switch(entry){
        case 2: return Library[ind].Author;
        case 3: return Library[ind].ISPN;
        case 4: return Library[ind].Category;
    }
}

/*
Search for a book based on entry:
1 book title (or part of it)
2 author name
3 ISBN
4 category
*/
int searchBook (char* key, int entry){
    int isFound=0;
    if(entry==1){
        int i;
        for(i=0; i<LIBRARY_SIZE; i++){
            if( isSubstr(Library[i].Title,key) ){
                isFound=1;
                printBook(i);
            }
        }
    }
    else {
        int i;
        for(i=0; i<LIBRARY_SIZE; i++){
            if(strcmp(infoReq(i,entry),key)==0 ){
                isFound=1;
                printBook(i);
            }
        }
    }
    if(!isFound)
        printf("Book not found!\n");
    return isFound;
}

//Edit a specific book info based on entry
int editBooks(int index, int data, char* newData)
{
    switch(data)
    {
        case 1: strcpy(Library[index].Title,newData);
                break;
        case 2: strcpy(Library[index].Author,newData);
                break;
        case 3: strcpy(Library[index].ISPN,newData);
                break;
        case 4: strcpy(Library[index].Publisher,newData);
                break;
        case 5: strcpy(Library[index].Category,newData);
                break;
        default:return 0;
    }
    return 1;
}
