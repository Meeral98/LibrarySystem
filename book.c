#include <stdio.h>
#include "book.h"

extern Book Library[100];
extern CURRENT_SIZE;
void Constructor(Book* new_book, char* title, char* author, char* publisher, char* ispn,char*pubdate, int copies, int copies_left, char* category){
    strcpy(new_book->ISPN,ispn);
    strcpy(new_book->Title,title);
    strcpy(new_book->Author,author);
    strcpy(new_book->Publisher,publisher);
    strcpy(new_book->PubDate,pubdate);
    new_book->Copies=copies;
    new_book->Copies_left=copies_left;
    new_book->borrowed=0;
    strcpy(new_book->Category,category);
    return ;
}
void read_books(){
    FILE* file;
    file=fopen("Books.txt", "r");
    char buffer[200];
    char*ptr;
    //void Constructor(Book* new_book, char* title, char* author, char* publisher, char* ispn, int copies, int copies_left, char* category){
    //C How to Program, Paul Deitel, Pearson Education. Inc, 0-13-612356-2, 29/10/2009, 5, 3, Programming
    int counter=0;
    if(file!=NULL){
        while(fgets(buffer,200,file)){
            ptr=buffer;
            char *title, *author, *publisher, *ispn, *date, *copies, *copies_left, *category;
            title=strtok(ptr,",");
            ptr+=strlen(title)+1;
            author=strtok(ptr,",");
            ptr+=strlen(author)+1;
            publisher=strtok(ptr,",");
            ptr+=strlen(publisher)+1;
            ispn=strtok(ptr,",");
            ptr+=strlen(ispn)+1;
            date=strtok(ptr,",");
            ptr+=strlen(date)+1;
            copies=strtok(ptr,",");
            ptr+=strlen(copies)+1;
            copies_left=strtok(ptr,",");
            ptr+=strlen(copies_left)+2;
            category=ptr;
            Constructor(&Library[counter], title, author+1, publisher+1, ispn+1, date, atoi(copies), atoi(copies_left), category);
            counter++;
        }
        CURRENT_SIZE=counter;
    }
    else
        printf("File not found\n");
    fclose(file);
}

void write_books(){
    FILE* file;
    file=fopen("Books.txt", "w");
        //C How to Program, Paul Deitel, Pearson Education. Inc, 0-13-612356-2, 29/10/2009, 5, 3, Programming
    int i;
    for(i=0; i<CURRENT_SIZE; i++){
        fprintf(file,"%s, %s, %s, %s,%s, %d, %d, %s\n",Library[i].Title, Library[i].Author, Library[i].Publisher, Library[i].ISPN,Library[i].PubDate, Library[i].Copies, Library[i].Copies_left, Library[i].Category);
    }
    fclose(file);
}
