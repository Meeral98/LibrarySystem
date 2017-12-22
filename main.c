#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "UI.h"
#include "book.h"
#include "borrowing.h"

int CURRENT_SIZE=0;
int MAX_LIBRARY_SIZE=100;
int bSize=0;
Book Library[100];
borrowing b[300];

char usersFile[]="D:/Codes/Uni/books.cont/abc.txt";
char borrowFile[]="D:/Codes/Uni/books.cont/borrow.txt";
user u[100];
int n;

int main()
{
    read_books();
    fgetUsers(usersFile);
    mainMenu();
    return 0;
}
