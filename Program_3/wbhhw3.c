#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 1024

//Define the contents of the linked list.
struct student{
    int studentID;
    char name[15];
    char phone[15];
    char email[40];

    struct student *next;
};
typedef struct student Student;


//Looking for the existence of the same ID in the linked list.
int search (Student *head , int id){
    int flag=0;
    for ( ; head!=NULL ; head=head->next ){
        if(head->studentID == id){
            flag=1;  
            break;
        }
    }
    return flag; //Return 1 if found , 0 otherwise.
}


//Insert a node into the linked list.
Student *insert(Student *head , char *input , int id){  

    char *ptr , *qtr , temp[40]; 
    Student *new = (Student *)malloc(sizeof(Student));  //Create a new node
    Student *current;
    Student *last;

    new->studentID = id;  //Set ID

    ptr=strstr(input,"name:");  //Use pointer setting name
    ptr=ptr+5;
    qtr=temp;
    while(*ptr!='\t')
        *qtr++=*ptr++;
    *qtr='\0';
    strcpy(new->name,temp) ;

    ptr=strstr(input,"phone:");  //Use pointer setting phone
    ptr=ptr+6;
    qtr=temp;
    while(*ptr!='\t')
        *qtr++=*ptr++;
    *qtr='\0';
    strcpy(new->phone,temp) ;
            
    ptr=strstr(input,"email:");  //Use pointer setting email
    ptr=ptr+6;
    qtr=temp;
    while(*ptr!='\t' && *ptr!='\n' && *ptr!=' ')  //Set break point
        *qtr++=*ptr++;
    *qtr='\0';
    strcpy(new->email,temp) ;

    //If the linked list is empty then the new node is the new header.
    if(head == NULL){
        new->next=NULL;
        return new;
    }

    //Otherwise, insert new nodes according to the number size sort.
    else{
        last=NULL;
        current=head;
        while(current!=NULL && current->studentID < id){
            last=current;
            current=current->next;
        }

        //When the new node is minimum.
        if(last==NULL){
            new->next=head;
            return new;
        }

        //The new node is inserted in the middle of the linked list.
        else{
            new->next=last->next;
            last->next=new;
            return head;
        }
    }
}

//Delete the node from the linked list.
Student *delete (Student *head , int id){

    Student *last , *current;

    //When the node to delete is the head of the linked list.
    if(head->studentID==id)
        return head->next;

    //When the node to delete is in the middle of the linked list (Include the last one)
    else{
        current=head;
        while(current->studentID!=id){
            last=current;
            current=current->next;
        }
        last->next=current->next;
        return head;
    }
}

//Update the node from the linked list.
void update(Student *head ,char *input , int id){

    //Finding the location of the node that needs to be updated.
    while(head->studentID!=id)
        head=head->next;
    
    char *ptr , *qtr , temp[40]; 

    ptr=strstr(input,"name:");  //Use pointer setting name.
    ptr=ptr+5;
    qtr=temp;
    while(*ptr!='\t')
        *qtr++=*ptr++;
    *qtr='\0';
    strcpy(head->name,temp) ;

    ptr=strstr(input,"phone:");  //Use pointer setting phone.
    ptr=ptr+6;
    qtr=temp;
    while(*ptr!='\t')
        *qtr++=*ptr++;
    *qtr='\0';
    strcpy(head->phone,temp) ;
            
    ptr=strstr(input,"email:");  //Use pointer setting email.
    ptr=ptr+6;
    qtr=temp;
    while(*ptr!='\t' && *ptr!='\n' && *ptr!=' ')  //Set break point.
        *qtr++=*ptr++;
    *qtr='\0';
    strcpy(head->email,temp) ;
}

//Find the key string in the node of the linked list.
void find(Student *head , char *line){

    int flag=0 , i=0;
    char temp[40];

    //Copy keyword string out to temp
    for(i=0;line[i+2]!='\n';i++)
        temp[i]=line[i+2];
    temp[i]='\0';

    //Use the loop to compare node and print if it matches
    while(head!=NULL){
        if(strstr(head->name,temp)!=NULL || strstr(head->phone,temp)!=NULL || strstr(head->email,temp)!=NULL){
            printf("studentID:%d\tname:%s\tphone:%s\temail:%s\n",head->studentID,head->name,head->phone,head->email);
            flag=1;
        }
        head=head->next;
    }

    if(flag==0)
        printf("Find error! Not exists!\n");
}


//Main program
int main(){  

    Student *head=NULL ;
    Student *current ;
    char line[max] ,*ptr =malloc(sizeof(char)) ;
    int id=0;

    //Print system messages
    printf("Please input command(i/d/u/f/l/q) and data:\n");
    printf("Insert the record:i studentID\\tname\\tphone\\temail\n");
    printf("Delete the record:d studentID\n");
    printf("Update the record:u studentID\\tname\\tphone\\temail\n");
    printf("Find the record:f [string]\n");
    printf("List the record:l\n");
    printf("Quit:q\n");

    //If there is data input, continue the loop
    while(fgets(line,max,stdin)){

        if(line[0]=='i'){  //Insert mode
            ptr = strstr(line,"studentID:") ;  //Finding the ID number in the input message.
            ptr = ptr + 10 ;
            id = atoi(ptr) ;
            
            //If this ID is not found in the linked list.
            if(search(head,id) != 1 ){
                head=insert(head,line,id);
                printf("Insert successful!\n");
            }
            else
                printf("Insert error! studentID is exists!\n");
        }

        if(line[0]=='d'){  //Delete mode
            ptr = strstr(line,"studentID:") ;  //Finding the ID number in the input message
            ptr = ptr + 10 ;
            id = atoi(ptr) ;

            //If this ID is found in the linked list.
            if(search(head,id) == 1 ){  
                head=delete(head,id);
                printf("delete successful!\n");
            }
            else
                printf("Delete error! studentID not exists!\n");
        }

        if(line[0]=='u'){  //Update mode
            ptr = strstr(line,"studentID:") ;  //Finding the ID number in the input message
            ptr = ptr + 10 ;
            id = atoi(ptr) ;

            //If this ID is found in the linked list
            if(search(head,id) == 1 ){
                update(head,line,id);
                printf("Update successful!\n");
            }
            else
                printf("Update error! studentID not exists!\n");
        }

        if(line[0]=='f'){  //Find mode

            find(head,line);
        }

        if(line[0]=='l'){  //List mode

            current=head;
            while(current!=NULL){
                printf("studentID:%d\tname:%s\tphone:%s\temail:%s\n",current->studentID,current->name,current->phone,current->email);
                current=current->next;
                }
        }

        if(line[0]=='q'){  //Quit mode
            printf("Thanks for your using!\n");
            break;
        }
    }
    return 0;
}