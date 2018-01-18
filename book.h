
#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#define MAX_LIBRARY_SIZE 100

typedef struct book {
    char ISPN[100];
    char Title[100];
    char Author[30];
    char Publisher[30];
    int Copies;
    int Copies_left;
    int borrowed;
    char Category[30];
    char PubDate[30];

}book;

extern book Library[MAX_LIBRARY_SIZE];
extern int LIBRARY_SIZE;
extern char libraryFile[];

void constructBook(book*,char*,char*,char*,char*,char*,int,int,char*);
void readBooks(char*); //loads books from file
void writeBooks(char*); //saves books to file


#endif // BOOK_H_INCLUDED
