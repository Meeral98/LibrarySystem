#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "borrowing.h"

void saveAll(); //saves users,borrowings,books into their files
void mainMenu(); //includes all sub-menus
void bookManagement(); //sub-menu includes: add new book - delete new book - search for book(by name,ISBN,author,category) - edit book - add more copies
void userManagement(); //sub-menu includes: add user - delete user
void borrowManagement(); //sub-menu includes: borrow - return
void administrativeActions(); //sub-menu includes: most popular books - overdue books - printing either (users,books,borrows)


#endif // UI_H_INCLUDED
