
#include "system.h"
#define BOOK_NOT_FOUND -1
extern int CURRENT_SIZE;
extern Book Library[100];

void add(Book newBook){
    Library[CURRENT_SIZE]=newBook;
    CURRENT_SIZE++;
    return;
}

int search(const char* ispn){

    int i;
    for(i=0; i<CURRENT_SIZE; i++){
        if(strcmp(Library[i].ISPN,ispn)==0) //strcmp
            return i;
    }
        return BOOK_NOT_FOUND;
}

void delete(const char* ispn){

    int index=search(ispn);
    Book temp=Library[index];
    Library[index]=Library[CURRENT_SIZE];
    Library[CURRENT_SIZE]=temp;

    CURRENT_SIZE--;
    return;
}
void readBook()
{
        Book new_book;
        char c[100];
        printf("Enter title: \n");
        gets(new_book.Title);

        printf("Enter author: ");
        gets(new_book.Author);

        printf("Enter publisher: ");
        gets(new_book.Publisher);

        printf("Enter ispn: ");
        scanf("%s",new_book.ISPN);

        printf("Enter copies: ");
        scanf("%d",&new_book.Copies);

        printf("Enter Copies_left: ");
        scanf("%d",&new_book.Copies_left);

        printf("Enter category: ");
        scanf("%s",new_book.Category);
        add(new_book);
}
void printBook(int i)
{
    printf("%s, %s, %s, %s,%s, %d, %d, %s\n",Library[i].Title, Library[i].Author, Library[i].Publisher, Library[i].ISPN,Library[i].PubDate, Library[i].Copies, Library[i].Copies_left, Library[i].Category);
}
void printBooks()
{
    int i;
    for(i=0;i<CURRENT_SIZE;i++)
        printBook(i);
}
