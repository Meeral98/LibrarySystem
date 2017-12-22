
#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED


typedef struct Book {
    char ISPN[30];
    char Title[30];
    char Author[30];
    char Publisher[30];
    int Copies;
    int Copies_left;
    int borrowed;
    char Category[30];
    char PubDate[30];
    //char *Date; // use time.h
}Book;

void Constructor(Book* new_book, char* title, char* author, char* publisher, char* ispn,char*pubdate, int copies, int copies_left, char* category);
void read_books();
void write_books();


#endif // BOOK_H_INCLUDED
