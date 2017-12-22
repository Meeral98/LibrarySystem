#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <stdio.h>
#include "borrowing.h"

typedef struct
{
    int building;
    char city[100];
    char street[100];
}address;

typedef struct
{
    char first_name[100];
    char last_name[100];
    long ID;
    address a;
    long phone_number;
    int age;
    char email[100];
    int borrows;

}user;

address constructAddress(int,char*,char*);
user constructUser(char*,char*,int,address,long,int,char*);
void addUser(); //adds a new user to array of users
void fgetUsers(char*); //gets all users from file into array and returns number of users
int deleteUser(int);
int findUser(int);
address getAddress();
void printUser();
void fprintUser(FILE*); //prints all users in file
void saveUsers(char fileName[]); //saves users in file

#endif // USER_H_INCLUDED
