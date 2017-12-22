

#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include "book.h"


void add(Book newBook);
int search(const char* ispn);
void delete(const char* ispn);
void readBook();
void printBook(int);
void printBooks();

#endif // SYSTEM_H_INCLUDED

