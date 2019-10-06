#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxHash 64

//Declare the Structure of a linked list node.
struct node{

    char *key;
    int count;

    struct node *next;
};
typedef struct node Node;

//Declare the Structure of a Binary Search Tree.
struct tree{
    char data[32];
    int number;

    struct tree *left;
    struct tree *right;
};
typedef struct tree Tree;

//Analyze the stdin command.
void capture(char line[], char command[], char input[]){

    char *ptr, *qtr;

    //Collect the first parameter from stdin.
    ptr = line;
    qtr = command;
    while (*ptr != '\t' && *ptr != '\n' && *ptr != ' ')
        *qtr++ = *ptr++;
    *qtr = '\0';

    //If stdin only has one parameter.
    if ((strcmp("insert", command) != 0) && (strcmp("delete", command) != 0) && (strcmp("query", command) != 0))
        return;
    //Collect the second parameter from stdin.
    else{
        ptr++;
        qtr = input;
        while (*ptr != '\t' && *ptr != '\n' && *ptr != ' ')
            *qtr++ = *ptr++;
        *qtr = '\0';
        return;
    }
}

//Declare the hash function.
unsigned int hashfunction(char *key){

    unsigned int value = 0;
    int i, len;

    len = strlen(key);

    //Add the ASCII code of all characters in the string.
    for (i = 0; i < len; i++)
        value = value + key[i];

    return value;
}

//Initialize the Hash table.
void initial(Node **hashtable){

    for (int i = 0; i < MaxHash; i++)
        hashtable[i] = NULL;
}

//Finding specific key in the Hash table.
Node *find(Node **hashtable, char *key){

    unsigned int hashvalue;
    Node *lptr;

    //Find out where a particular key is in a hash table.
    hashvalue = hashfunction(key) % MaxHash;
    lptr = hashtable[hashvalue];

    //Compare whether there is a target key in it.
    while (lptr != NULL){
        if (strcmp(lptr->key, key) == 0)
            return lptr;
        lptr = lptr->next;
    }

    //If it cannot be found , return NULL.
    return NULL;
}

//Insert new key into the hash table.
void insert(Node **hashtable, char *key){

    unsigned int hashvalue;
    int len=strlen(key);
    Node *lptr = NULL, *last = NULL;

    //Use hash function to determine where the key is inserted.
    hashvalue = hashfunction(key) % MaxHash;

    //If that place already has the same key, count adds one.
    if ((lptr = find(hashtable, key)) != NULL)
        lptr->count++;

    else{
        lptr = hashtable[hashvalue];
        //Finding where we can insert a new linked list.
        while (lptr != NULL){
            last = lptr;
            lptr = lptr->next;
        }

        //Create a new linked list.
        Node *new = (Node *)malloc(sizeof(Node));
        new->key=malloc(len+1);
        strcpy(new->key, key);
        new->count = 1;

        //The place to insert is at the head
        if (last == NULL)
            hashtable[hashvalue] = new;
        //The place to insert is at the end
        else
            last->next = new;
    }
}

//Reduce the count on the established linked list.
void delete (Node **hashtable, char *key){

    Node *lptr = NULL;

    //We do that if we find it.
    if ((lptr = find(hashtable, key)) != NULL)
        lptr->count--;
}

//Add node to binary search tree.
Tree *sortinsert(Tree *root, Node *hashnode){

    //If the new root node is NULL then add a new node from input tree.
    if (root == NULL){
        Tree *new = (Tree *)malloc(sizeof(Tree));
        strcpy(new->data, hashnode->key);
        new->number = hashnode->count;
        new->left = NULL;
        new->right = NULL;
        return new;
    }

    //If the root node is the same as the input number , according to data decided to add node to the left subtree or right subtree.
    else if (root->number == hashnode->count)
        if (strcmp(root->data, hashnode->key) < 0)
            root->right = sortinsert(root->right, hashnode);
        else
            root->left = sortinsert(root->left, hashnode);

    //Use recursive to add data to the right subtree or left subtree.
    else if (root->number > hashnode->count)
        root->right = sortinsert(root->right, hashnode);

    else if (root->number < hashnode->count)
        root->left = sortinsert(root->left, hashnode);

    return root;
}

//Create a binary search tree using the data in the hash table.
void sort(Tree *root, Node **hashtable){

    int i = 0;
    Node *ptr = NULL;

    //Visit each valid data in the hash table.
    for (i = 0; i < MaxHash; i++){
        if ((ptr = hashtable[i]) != NULL)
            while (ptr != NULL){
                root = sortinsert(root, ptr);
                ptr = ptr->next;
            }
    }
}

//Print the binary search tree by using inorder
void inorder(Tree *root){

    //If the root node is NULL then do nothing.
    if (root == NULL)
        return;

    inorder(root->left);
    //print root's number and data(must be large than 0).
    if (root->number > 0)
        printf("%d\t%s\n", root->number, root->data);
    inorder(root->right);
    return;
}

//The function to calculate the number of key occurrences and sort it.
void count(Node **hashtable){

    //Build the root node of a new tree , as a basis for all inserts.
    Tree *root = (Tree *)malloc(sizeof(Tree));
    strcpy(root->data, "sortroot");
    root->left = NULL;
    root->right = NULL;
    root->number = 0;

    //Create a new, sorted binary search tree
    sort(root, hashtable);

    //Print the new binary search tree by using inorder
    inorder(root);
}

int main(){

    char line[64] = {0}, command[16] = {0}, input[32] = {0};
    Node *hashtable[MaxHash];
    Node *ptr;

    initial(hashtable);

    while (fgets(line, 64, stdin)){

        capture(line, command, input);

        if (strcmp("insert", command) == 0)
            insert(hashtable, input);

        if (strcmp("delete", command) == 0)
            delete (hashtable, input);

        if (strcmp("query", command) == 0){
            printf("----------\n");
            ptr = find(hashtable, input);
            //There are two output methods whether the specific key in the hash table .
            if (ptr != NULL && ptr->count > 0)
                printf("%s\t%d\n", ptr->key, ptr->count);
            else
                printf("Not found!\n");
            printf("----------\n");
        }

        if (strcmp("count", command) == 0){
            printf("----------\n");
            count(hashtable);
            printf("----------\n");
        }
    }

    return 0;
}