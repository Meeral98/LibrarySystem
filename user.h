#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "borrowing.h"
#define MAX_USERS_SIZE 100

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
extern user Users[MAX_USERS_SIZE];
extern int USERS_SIZE;
extern char usersFile[];

address constructAddress(int,char*,char*);
user constructUser(char*,char*,int,address,long,int,char*);
void addUser(); //adds a new user (during program) to array of users
void readUsers(char*); //gets all users from file into array and returns number of users
int deleteUser(int); //deletes user by ID; returns -1 if not found, 0 if found but still has unreturned borrowed books, 1 if deleted
int findUser(int); //finds user by ID; returns user index is found, -1 if not found
address getAddress(); //scans address during program
void printUser(); //prints one user to screen (by index)
void printUsers(); //prints all users to screen
void writeUsers(char*); //saves users in file

#endif // USER_H_INCLUDED
