#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) /*, int sortCriteria*/
{
    // Sort contacts based on the chosen criteria
    for(int i=0;i<addressBook->contactCount;i++){
        printf("%-20s%-15s%-20s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    } 
    printf("\nPress enter key to continue...");
    getchar();
    getchar();
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
   loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    int choice;
    char sname[50];
    char snumber[20];
    char smail[50];
    printf("\n---creating new contact---\n");

printf("Enter name : ");
getchar();
scanf("%[^\n]",sname);
getchar();

number:
printf("Enter Number : ");
scanf("%s",snumber);
int val=1;
if(strlen(snumber)!=10)
val=0;
else{
    for(int j=0;j<10;j++){
        if(snumber[j]<'0'||snumber[j]>'9'){
            val=0;
            break;
        }
    }
}
if(!val){
    printf("Invalid number\n");
    goto number;
  }
  for(int i=0;i<addressBook->contactCount;i++){
    if((strcmp(addressBook->contacts[i].phone,snumber)==0)){
        printf("\nThe given mobile number already exist!\n");
        goto number;
    }
}

mail:
printf("Enter Mail : ");
scanf("%s",smail);
if(strstr(smail,"@")==NULL || strstr(smail,".com")==NULL || strstr(smail," ")!=NULL){
    printf("\nInvalid email\n");
 goto mail;
}

for(int i=0;i<addressBook->contactCount;i++){
    if((strcmp(addressBook->contacts[i].email,smail)==0)){
        printf("\nThe given email already exist!\n");
        goto mail;
    }
}

int j=addressBook->contactCount;
    strcpy(addressBook->contacts[j].name,sname);
    strcpy(addressBook->contacts[j].phone,snumber);
    strcpy(addressBook->contacts[j].email,smail);
   addressBook->contactCount++;
   printf("\nContact created successfully\n");
}

void searchContact(AddressBook *addressBook) 
{
    int choice;
    char sname[50];
    char snumber[20];
    char smail[50];
    int flag;
    search:
        printf("\n---Search Contact---\n");
        printf("1. Search By Name\n");
        printf("2. Search By Number\n");
        printf("3. Search By Email\n");
        printf("Enter your choice:");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
            name:
                printf("Enter the name to search : ");
                getchar();
                scanf("%[^\n]",sname);
                char *p;
                flag=0;
                int n=1;
                for(int i=0;i<addressBook->contactCount;i++){
                    if((p=strcasestr(addressBook->contacts[i].name,sname))!=NULL){
                        printf("%d.%-20s%-15s\t%-30s\n",n,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        n++;
                        flag=1;
                    }
                    
                }
                getchar();
                
                if(!flag){
                    printf("\n---Name not found---\n");
                    goto name;
                }
                printf("Press enter key to continue...");
               if(getchar())
                break;

            case 2:
                num:
                printf("Enter Number to search : ");
                scanf("%s",snumber);
                flag=0;
                for(int i=0;i<addressBook->contactCount;i++){
                    if((strcmp(addressBook->contacts[i].phone,snumber))==0){
                        printf("1.%-20s%-15s\t%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        getchar();
                        flag=1;
                        break;
                    }
                }
                
                if(!flag){
                    printf("\n---Contact not found---\n");
                    goto num;
                }
                printf("Press enter key to continue...");
               if(getchar())
                break;

            case 3:
            mail:
                printf("Enter Mail to search : ");
                scanf("%s",smail);
                flag=0;
                for(int i=0;i<addressBook->contactCount;i++){
                    if((strcmp(addressBook->contacts[i].email,smail))==0){
                        printf("1.%-20s%-15s\t%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        getchar();
                        flag=1;
                    }
                }
                
                if(!flag){
                    printf("---Email not found---\n");
                    goto mail;
                   
                }
                printf("Press enter key to continue...");
               if(getchar())
                break;
                
            default:
                printf("\nInvalid choice. Please try again.\n");
                goto search;
}
}

void editContact(AddressBook *addressBook)
{
	 int choice;
    char sname[50];
    char snumber[20];
    char smail[50];
    int found[100];
    int flag,foundcount=0;
    int index =0;
    opt:
        printf("\nSearch Contact\n");
        printf("1. Search By Name\n");
        printf("2. Search By Number\n");
        printf("3. Search By Email\n");
        printf("Enter the choice :");
        scanf("%d", &choice);
        if(choice>3||choice<1)
        {
            printf("\nInvalid choice\n");
            goto opt;
        }
        
        switch (choice) {
            case 1:
            name:
                printf("Enter the name to search : ");
                getchar();
                scanf("%[^\n]",sname);
                char *p;
                
                flag=0;
                int n=1;
                for(int i=0;i<addressBook->contactCount;i++){
                    if((p=strcasestr(addressBook->contacts[i].name,sname))!=NULL){
                        printf("%d.%-20s%-15s\t%-30s\n",n,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    n++;
                        flag=1;
                        found[foundcount++]=i;

                    }
                }
                
                if(!flag){
                    printf("\n---Name not found---\n");
                    goto name;

                }
                if(foundcount>1){
                    printf("Choose the contact to edit :");
                    scanf("%d",&index);
                    index=found[index-1];
                }
                else index=found[0];

                break;

            case 2:
            num1:
                printf("Enter Number to search : ");
                scanf("%s",snumber);
                flag=0;
                for(int i=0;i<addressBook->contactCount;i++){
                    if((strcmp(addressBook->contacts[i].phone,snumber))==0){
                        printf("1.%-20s%-15s\t%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    
                        flag=1;
                        index=i;
                    }
                }
                
                if(!flag){
                    printf("\n---Contact not found---\n");
                    goto num1;
                }
                break;

            case 3:
                mail1:
                printf("Enter Mail to search : ");
                scanf("%s",smail);
                flag=0;
                for(int i=0;i<addressBook->contactCount;i++){
                    if((strcmp(addressBook->contacts[i].email,smail))==0){
                        printf("1.%-20s%-15s\t%-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        flag=1;
                        index=i;
                    }
                }
                if(!flag){
                    printf("\n---Email not found---\n");
                    goto mail1;
                   
                }
                break;
                
            default:
                printf("\nInvalid choice. Please try again.\n");

}
char nname[50];
char nnumber[20];
char nmail[20];
int choice1;
opt1:
printf("1.Edit the name\n");
printf("2.Edit the number\n");
printf("3.Edit the email\n"); 
printf("Enter the choice :");
scanf("%d",&choice1);
if(choice>3||choice<1)
        {
            printf("\n---Invalid choice---\n");
            goto opt1;
        }

switch(choice1){
    case 1:
    printf("Enter the new name :");
    getchar();
    scanf("%[^\n]",nname);
    getchar();
    strcpy(addressBook->contacts[index].name,nname);
    printf("\n---Updated successfully---\n");
    break;

    case 2:
    number:
    printf("Enter the new number :");
    scanf("%s",nnumber);
int val=1;
if(strlen(nnumber)!=10)
val=0;
else{
    for(int j=0;j<10;j++){
        if(nnumber[j]<'0'||nnumber[j]>'9'){
            val=0;
            break;
        }
    }
}
if(!val){
    printf("\n---Invalid number---\n");
    goto number;
  }
  for(int i=0;i<addressBook->contactCount;i++){
    if((strcmp(addressBook->contacts[i].phone,nnumber)==0)){
        printf("\nThe given mobile number already exist!\n");
        goto number;
    }
}
    strcpy(addressBook->contacts[index].phone,nnumber);
    printf("\n---Updated successfully---\n");
    break;

    case 3:
     mail:
    printf("Enter the new email :");
    scanf("%s",nmail);
   
if(strstr(nmail,"@")==NULL || strstr(nmail,".com")==NULL || strstr(nmail," ")!=NULL){
    printf("\n---Invalid email---\n");
 goto mail;
}

for(int i=0;i<addressBook->contactCount;i++){
    if((strcmp(addressBook->contacts[i].email,nmail)==0)){
        printf("\n---The given email already exist!---\n");
        goto mail;
    }
}
    strcpy(addressBook->contacts[index].email,nmail);
    printf("\n---Updated successfully---\n");
    break;
}
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice;
    char sname[50];
    char snumber[20];
    char smail[50];
    int new[100];
    int flag,del;
    int n=1,i,j,count=0;
    opt:
        printf("\nSearch Contact\n");
        printf("1. Search By Name\n");
        printf("2. Search By Number\n");
        printf("3. Search By Email\n");
        printf("Enter the choice :");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            name:
                printf("Enter the name to search : ");
                getchar();
                scanf("%[^\n]",sname);
                char *p;
                flag=0;

                for(i=0;i<addressBook->contactCount;i++){
                    if((p=strcasestr(addressBook->contacts[i].name,sname))!=NULL){
                        new[count++]=i;
                        printf("%d.%-20s%-15s%-30s\n",n,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        n++;
                        flag++;
                    }
                }
                
                if(flag>0){
                    select:
                    printf("Select contact to delete :");
                    scanf("%d",&del);
                    if(del>=n || del<=0){
                    printf("\n---Invalid choice---\n");
                    goto select;
                    }
                    int k=new[del-1];
                    for(j=k;j<addressBook->contactCount-1;j++){
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                    }
                    addressBook->contactCount--;
                    printf("\n---Contact deleted---\n");
                }
                else{
                    printf("\n---Contact not found---\n");
                    goto name;
                }
                break;

            case 2:
            num:
                printf("Enter Number to search : ");
                scanf("%s",snumber);
                flag=0;
                for(i=0;i<addressBook->contactCount;i++){
                    if((strcmp(addressBook->contacts[i].phone,snumber))==0){
                        printf("%s\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    
                        flag=1;
                        break;
                    }
                }
                
                if(flag){
                    select1:
                    printf("Select contact to delete :");
                    scanf("%d",&del);
                    if(del!=1){
                    printf("\n---Invalid choice---\n");
                    goto select1;
                    }
                    for(j=i;j<addressBook->contactCount-1;j++){
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                    }
                    addressBook->contactCount--;
                    printf("\n---Contact deleted---\n");
                    
                }
                else{
                    printf("\n---Contact not found\n---");
                    goto num;
                }
                break;

            case 3:
            mail:
                printf("Enter Mail to search : ");
                scanf("%s",smail);
                flag=0;
                for(i=0;i<addressBook->contactCount;i++){
                    if((strcmp(addressBook->contacts[i].email,smail))==0){
                        printf("%s\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        flag=1;
                        break;
                    }
                }
                if(flag){
                    select2:
                    printf("Select contact to delete :");
                    scanf("%d",&del);
                    if(del!=1){
                    printf("\n---Invalid choice---\n");
                    goto select2;
                    }
                    for(j=i;j<addressBook->contactCount-1;j++){
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                    }
                    addressBook->contactCount--;
                    printf("\n---Contact deleted---\n");
                }
                else{
                    printf("\n---Contact not found---\n");
                    goto mail;
                }
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
                goto opt;
}

   
}
