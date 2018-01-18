

#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include "book.h"

//Linear search by ISBN in Library //return -1 if book not found
int findBook(char* isbn);

//Delete a book by ISBN in Library // swap the to-be-deleted-book by the last one and decrement library size by 1
int deleteBook(char* isbn);

//fgets book informations and store it in Library
void addBook();

//Print most popular books (first five books in the Borrowings array)
void printMostPopular();

//Print info of the ith book
void printBook(int i);

//Print all Library books' info
void printLibrary();

//Check if subs is a substring from main
int isSubstr(char* main, char* subs);

//return the required book info based on entry
char* infoReq(int ind, int entry);

/*
Search for a book based on entry:
1 book title (or part of it)
2 author name
3 ISBN
4 category
*/
int searchBook (char* key, int entry);

//Edit a specific book info based on entry
int editBooks(int index, int data, char* newData);




#endif // SYSTEM_H_INCLUDED

