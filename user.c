#include "user.h"
#include <string.h>

extern usersFile[];
extern user u[100];
extern int n;
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
    int building;
    char street[1024];
    char city[1024];
    char dummy;
    printf("Enter Address:Building No:");
    scanf("%d",&building);
    scanf("%c",&dummy);
    printf("Street Name:");
    gets(street);
    printf("City:");
    gets(city);
    return constructAddress(building,street,city);
}

void addUser()
{
    char firstN[1024], lastN[1024], email[1024],dummy;
    int ID,age;
    long phoneN;
    printf("Enter your ID:");
    scanf("%d",&ID);
    if(findUser(ID)!=-1)
    {
        do
        {
            printf("ID already exists, please enter another ID ");
            scanf("%d",&ID);
        }while(findUser(ID)!=-1);
    }
    scanf("%c",&dummy);
    printf("Enter your name (FirstName LastName)");
    scanf("%s %s",firstN,lastN);
    scanf("%c",&dummy);
    printf("Enter your email address:");
    scanf("%s",email);
    strcat(email,"\n");
    printf("Enter your age:");
    scanf("%d",&age);
    printf("Enter your phoneNumber:");
    scanf("%ld",&phoneN);
    u[n]=constructUser(firstN,lastN,ID,getAddress(),phoneN,age,email);
    n++;
}
void fgetUsers(char fileName[])
{
    FILE*f=fopen(fileName,"r");
    char b1[256];
    char*b2;
    int counter=0;
    while(fgets(b1,256,f))
    {
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
        address a=constructAddress(b,st,c);
        u[counter]=constructUser(fn,ln,id,a,pn,age,m);
        counter++;
    }
    fclose(f);
    n=counter;
}
void printUser()
{
    int i;
    for(i=0;i<n;i++)
        printf("%s, %s, %d, %d, %s, %s, %ld, %d, %s",u[i].last_name,u[i].first_name,u[i].ID,u[i].a.building,u[i].a.street,u[i].a.city,u[i].phone_number,u[i].age,u[i].email);
}

void fprintUser(FILE*d)
{
    int i;
    for(i=0;i<n;i++)
        fprintf(d,"%s, %s, %d, %d, %s, %s, %ld, %d, %s",u[i].last_name,u[i].first_name,u[i].ID,u[i].a.building,u[i].a.street,u[i].a.city,u[i].phone_number,u[i].age,u[i].email);
}

void saveUsers(char fileName[])
{
    FILE*f=fopen(fileName,"w");
    fprintUser(f);
    fclose(f);
}

int deleteUser(int ID)
{
    int i,f=-1;
    for(i=0;i<n;i++)
    {
        if(u[i].ID==ID)
        {
            f=0;
            int j;
            for(j=i;j<n-1;j++)
                u[j]=u[j+1];
            break;
        }
    }
    if(f==0)
        n--;
    return f;
}

int findUser(int ID)
{
    int i;
    for(i=0;i<n;i++)
        if(u[i].ID==ID)
            break;
    if(i==n)
        return -1;
    return i;
}
