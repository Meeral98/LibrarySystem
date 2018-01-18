#include "user.h"
#include <string.h>
#include <stdio.h>
user Users[MAX_USERS_SIZE];
int USERS_SIZE=0;

address constructAddress(int building,char*street,char*city)
{
    address a;
    a.building=building;
    strcpy(a.street,street);
    strcpy(a.city,city);
    return a;
}

user constructUser(char*firstN,char*lastN,int ID,address a,long phone,int age,char*email)
{
    user u;
    u.ID=ID;
    u.a=a;
    u.phone_number=phone;
    u.age=age;
    u.borrows=0;
    strcpy(u.first_name,firstN);
    strcpy(u.last_name,lastN);
    strcpy(u.email,email);
    return u;
}

address getAddress()
{
    char building[10];
    char street[100];
    char city[100];
    printf("Enter Address:\nBuilding No: ");
    fgets(building,sizeof(building),stdin);
    printf("Street Name: ");
    fgets(street,sizeof(street),stdin);
    street[strlen(street)-1]=0;
    printf("City: ");
    fgets(city,sizeof(city),stdin);
    city[strlen(city)-1]=0;
    return constructAddress(atoi(building),street,city);
}

void addUser()
{
    char firstN[100], lastN[100], email[100];
    char ID[11],age[11];
    char phoneN[13];
    printf("Enter your ID: ");
    fgets(ID,sizeof(ID),stdin);
    ID[strlen(ID)-1]=0;
    fflush(stdin);
    if(findUser(atoi(ID))!=-1)
    {
        do
        {
            printf("ID already exists, please enter another ID ");
            fgets(ID,sizeof(ID),stdin);
            ID[strlen(ID)-1]=0;
            fflush(stdin);
        }while(findUser(atoi(ID))!=-1);
    }
    printf("Enter your first name: ");
    fgets(firstN,sizeof(firstN),stdin);
    firstN[strlen(firstN)-1]=0;
    fflush(stdin);
    printf("Enter your last name: ");
    fgets(lastN,sizeof(lastN),stdin);
    lastN[strlen(lastN)-1]=0;
    fflush(stdin);
    printf("Enter your email address: ");
    fgets(email,sizeof(email),stdin);
    fflush(stdin);
    printf("Enter your age: ");
    fgets(age,sizeof(age),stdin);
    age[strlen(age)-1]=0;
    fflush(stdin);
    printf("Enter your phoneNumber: ");
    fgets(phoneN,sizeof(phoneN),stdin);
    phoneN[strlen(phoneN)-1]=0;
    fflush(stdin);
    Users[USERS_SIZE]=constructUser(firstN,lastN,atoi(ID),getAddress(),atoi(phoneN),atoi(age),email);
    USERS_SIZE++;
}
void readUsers(char fileName[])
{
    FILE*f=fopen(fileName,"r");
    char b1[256];
    char*b2;
    int counter=0;
    while(fgets(b1,256,f))
    {
        //break down line into data
        int i=0,prev=0,data=0;
        char fn[256],ln[256],st[256],c[256],m[256];
        int id,b,pn,age;
        while(b1[i])
        {
            if(b1[i]==',')
            {
                b2=strtok(b1+prev,",");
                prev=i+2;
                switch(data)
                {
                    case 0:strcpy(ln,b2);
                    case 1:strcpy(fn,b2);
                    case 2:id=atoi(b2);
                    case 3:b=atoi(b2);
                    case 4:strcpy(st,b2);
                    case 5:strcpy(c,b2);
                    case 6:pn=atoi(b2);
                    case 7:age=atoi(b2);
                }
                data++;
            }
            i++;
        }
        strcpy(m,b1+prev);
        //construct address and user
        address a=constructAddress(b,st,c);
        Users[counter]=constructUser(fn,ln,id,a,pn,age,m);
        counter++;
    }
    fclose(f);
    USERS_SIZE=counter;
}
void printUser(int i)
{
    printf("%s, %s, %d, %d, %s, %s, %ld, %d, %s",Users[i].last_name,Users[i].first_name,Users[i].ID,Users[i].a.building,Users[i].a.street,Users[i].a.city,Users[i].phone_number,Users[i].age,Users[i].email);
}
void printUsers()
{
    int i;
    for(i=0;i<USERS_SIZE;i++)
        printUser(i);
}
void writeUsers(char fileName[])
{
    FILE*f=fopen(fileName,"w");
     int i;
    for(i=0;i<USERS_SIZE;i++)
        fprintf(f,"%s, %s, %d, %d, %s, %s, %ld, %d, %s",Users[i].last_name,Users[i].first_name,Users[i].ID,Users[i].a.building,Users[i].a.street,Users[i].a.city,Users[i].phone_number,Users[i].age,Users[i].email);

    fclose(f);
}

int deleteUser(int ID)
{
    int index=findUser(ID);
    if(index==-1)
        return -1;
    int i;
    if(Users[index].borrows>0)
        return 0;
    Users[index]=Users[USERS_SIZE-1];
    USERS_SIZE--;
    return 1;
}

int findUser(int ID)
{
    int i;
    for(i=0;i<USERS_SIZE;i++)
        if(Users[i].ID==ID)
            break;
    if(i==USERS_SIZE)
        return -1;
    return i;
}
