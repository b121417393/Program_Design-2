#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Define the content of the linked list
struct words{
    char data[40];
    int number;

    struct words *next;
};
typedef struct words Words;

//Insert new node into linked list.
Words *insert( Words *head , char *input ){  

    int count=1;
    Words *new = (Words *)malloc(sizeof(Words));  //Create a new node
    Words *last;
    Words *current;

    strcpy(new->data,input);  //Set data
    
    //If the linked list is empty then the new node is the new header.
    if(head == NULL){
        new->number=1;  //This date first appeared in the linked list
        new->next=NULL;
        return new;
    }

    //Connect the new node to the back of the linked list
    else{
        last=NULL;
        current=head;
        while(current!=NULL){  //Calculate how many times this data has appeared in the linked list
            if(strcmp(current->data,input)==0)
                count++;
            last=current;
            current=current->next;
        }
        last->next=new;
        new->number=count;  //This data has appeared count-1 times
        new->next=NULL;
        return head;
    }
}

////Delete the node from the linked list.
Words *delete (Words *head , char *key){

    Words *last , *current;

    // Delete all qualified nodes in the linked list.

    //When the target node is the head in the linked list
    while(strcmp(head->data,key)==0){  
        head=head->next;
		if(head==NULL)  //When the linked list is cleared
				return NULL;
	}

    last=NULL;
    current=head;

    //When the target node is in the middle of the linked list.
    while(current!=NULL){
        if(strcmp(current->data,key)==0){
            last->next=current->next;
            current=current->next;
        }
        else{
            last=current;
            current=current->next;
        }
    }
    return head;
}

//Main program
int main(){  

    Words *head=NULL ;
    Words *current ;
    char line[1024] ;
    int len=0,max=0;

    //If there is data input, continue the loop
    while(fgets(line,1024,stdin)){
        len=strlen(line);
        if(line[len-1]=='\n')
        	line[len-1]='\0';
        head=insert(head,line);  //insert the node.
    }

    //Print the linked list node according to the number of occurrences.
	while(head!=NULL){  

        max=head->number;
		strcpy(line,head->data);

        //Finding the most frequently appearing data in the linked list
        for(current=head;current!=NULL;current=current->next)
            if(current->number>max){
                max=current->number;
                strcpy(line,current->data);
			}

        //Print the most frequently appearing data according to size.
        for(current=head;current!=NULL;current=current->next)
            if(current->number==max && strcmp(line,current->data)>0 )
                	strcpy(line,current->data);
        
        printf("%d %s\n",max,line);
        head=delete(head,line);  //Delete the printed data from the linked list.

	}
    return 0;
}
