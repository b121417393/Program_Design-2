#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 1024

//Define the content of the structure
struct student{
    int studentID;
    char name[15];
    char phone[15];
    char email[40];
};

//Initialize the structure
void initialize (struct student *a,int count){
    int i=0;
    for(i=0;i<count;i++){  //Total number of structures declared
        a[i].studentID=0;
        a[i].name[0]='\0';
        a[i].phone[0]='\0';
        a[i].email[0]='\0';
    }
}

//Looking for the existence of the same ID in the structure
int search(struct student *a,int count ,int id){
    int i=0,flag=0;
    for (i=0;i<count;i++){  //Total number of structures used
        if(a[i].studentID == id){
            flag=1;  
            break;
        }
    }
    return flag; //Return 1 if found , 0 otherwise.
}

//Main program
int main(){  

    struct student address[max];
    char line[max] ,find[20];
    char *ptr = malloc(sizeof(char)) ; 
    char *qtr = malloc(sizeof(struct student));
    int i=0,j=0,count=0,id=0;

    initialize(address,max);  //Initialize all structures

    //Print system messages
    printf("Please input command(i/d/u/f/l/q) and data :\n");
    printf("Insert the record : i studentID\\tname\\tphone\\temail\n");
    printf("Delete the record : d studentID\n");
    printf("Update the record : u studentID\\tname\\tphone\\temail\n");
    printf("Find the record : f [string]\n");
    printf("List the record : l\n");
    printf("Quit : q\n");

    //If there is data input, continue the loop
    while(fgets(line,max,stdin)){

        if(line[0]=='i'){  //Insert mode
            ptr = strstr(line,"studentID:") ;  //Finding the ID number in the input message
            ptr = ptr + 10 ;
            id = atoi(ptr) ;
            
            //If this ID is not found in the structure
            if(search(address,count,id) != 1 ){

                address[i].studentID = id;  //Set ID

                ptr=strstr(line,"name:");  //Use pointer setting name
                ptr=ptr+5;
                qtr=address[i].name;
                while(*ptr!='\t')
                    *qtr++=*ptr++;
                *qtr='\0'; 

                ptr=strstr(line,"phone:");  //Use pointer setting phone
                ptr=ptr+6;
                qtr=address[i].phone;
                while(*ptr!='\t')
                    *qtr++=*ptr++;
                *qtr='\0';
            
                ptr=strstr(line,"email:");  //Use pointer setting email
                ptr=ptr+6;
                qtr=address[i].email;
                while(*ptr!='\t' && *ptr!='\n' && *ptr!=' ')  //Set break point
                    *qtr++=*ptr++;
                *qtr='\0';

                count++;
                i++;
                printf("Insert successful!\n");
            }
            else
                printf("Insert error! studentID is exists!\n");
        }

        if(line[0]=='d'){  //Delete mode
            ptr = strstr(line,"studentID:") ;  //Finding the ID number in the input message
            ptr = ptr + 10 ;
            id = atoi(ptr) ;

            //If this ID is found in the structure
            if(search(address,count,id) == 1 ){  
                for(j=0;j<count;j++)  
                    if(address[j].studentID == id){  //Find this ID's location and eliminate it
                        address[j].studentID=0;
                        break;
                    }
                printf("delete successful!\n");
            }
            else
                printf("Delete error! studentID not exists!\n");
        }

        if(line[0]=='u'){  //Update mode
            ptr = strstr(line,"studentID:") ;  //Finding the ID number in the input message
            ptr = ptr + 10 ;
            id = atoi(ptr) ;

            //If this ID is found in the structure
            if(search(address,count,id) == 1 ){
                for(j=0;j<count;j++)
                    if(address[j].studentID == id)  //Find this ID's location
                        break;

                ptr=strstr(line,"name:");  //Use pointer setting name
                ptr=ptr+5;
                qtr=address[j].name;
                while(*ptr!='\t')
                    *qtr++=*ptr++;
                *qtr='\0'; 

                ptr=strstr(line,"phone:");  //Use pointer setting phone
                ptr=ptr+6;
                qtr=address[j].phone;
                while(*ptr!='\t')
                    *qtr++=*ptr++;
                *qtr='\0';
            
                ptr=strstr(line,"email:");  //Use pointer setting email
                ptr=ptr+6;
                qtr=address[j].email;
                while(*ptr!='\t' && *ptr!='\n' && *ptr!=' ')
                    *qtr++=*ptr++;
                *qtr='\0';

                printf("Update successful!\n");
            }
            else
                printf("Update error! studentID not exists!\n");
         }


        if(line[0]=='f'){  //Find mode

            int flag=0;  //Whether the string exists

            *ptr=line[2];  //Pointer to input string
            qtr=find;  //Pointer to keyword string
            while(*ptr!='\n')  //Copy keyword string to *qtr
                *qtr++=*ptr++;
            *qtr='\0';

            for(j=0;j<count;j++)  //Finding whether there is a keyword string in the structure
                if(strstr(address[j].name,find)!=NULL || strstr(address[j].phone,find)!=NULL || strstr(address[j].email,find)!=NULL)
                    printf("studentID:%d\tname:%s\tphone:%s\temail:%s\n",address[j].studentID,address[j].name,address[j].phone,address[j].email),flag=1;
            
            if(flag==0)
                printf("Find error! Not exists!\n");
        }

        if(line[0]=='l'){  //List mode
            for(j=0;j<count;j++)
                if(address[j].studentID != 0)  //If the ID is not 0 then print out
                     printf("studentID:%d\tname:%s\tphone:%s\temail:%s\n",address[j].studentID,address[j].name,address[j].phone,address[j].email);
        }

        if(line[0]=='q'){  //Quit mode
            printf("Thanks for your using!\n");
            break;
        }
    }
    return 0;
}
