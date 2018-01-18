#include <stdio.h>
#include "book.h"

book Library[MAX_LIBRARY_SIZE];
int LIBRARY_SIZE=0;

void constructBook(book* new_book, char* title, char* author, char* publisher, char* ispn, char* pubdate, int copies, int copies_left, char* category){
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
void readBooks(char* fileName){
    FILE* file;
    file=fopen(fileName,"r");
    char buffer[300];
    int counter=0;
    if(file!=NULL){
        while(fgets(buffer,300,file)){
            //break down lines into data
            char *title, *author, *publisher, *ispn, *date, *copies, *copies_left, *category;
            title=strtok(buffer,",");
            author=strtok(NULL,",");
            publisher=strtok(NULL,",");
            ispn=strtok(NULL,",");
            date=strtok(NULL,",");
            copies=strtok(NULL,",");
            copies_left=strtok(NULL,",");
            category=strtok(NULL,"\n");
            constructBook(&Library[counter], title, author+1, publisher+1, ispn+1, date+1, atoi(copies), atoi(copies_left), category+1);
            counter++;
        }
        LIBRARY_SIZE=counter;
    }
    else
        printf("File not found\n");
    fclose(file);
}

void writeBooks(char* fileName){
    FILE* file;
    file=fopen(fileName, "w");
    int i;
    for(i=0; i<LIBRARY_SIZE; i++){
        fprintf(file,"%s, %s, %s, %s, %s, %d, %d, %s\n",Library[i].Title, Library[i].Author, Library[i].Publisher, Library[i].ISPN,Library[i].PubDate, Library[i].Copies, Library[i].Copies_left, Library[i].Category);
    }
    fclose(file);
}
