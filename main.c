#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "UI.h"
#include "book.h"
#include "borrowing.h"
#include "system.h"


char libraryFile[]="Library.txt";
char usersFile[]="Users.txt";
char borrowingsFile[]="Borrowings.txt";


int main()
{
    //load data from files
    readBooks(libraryFile);
    readUsers(usersFile);
    readBorrowings(borrowingsFile);
    //user interface
    printMostPopular();
    mainMenu();
    return 0;
}
