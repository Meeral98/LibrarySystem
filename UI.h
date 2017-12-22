#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "borrowing.h"

void mainMenu();
void bookManagement();
void userManagement();
void borrowManagement();
void administrativeActions();
int inTime(date d1,date d2); //returns true if date 2 is before/equal date 1


#endif // UI_H_INCLUDED
