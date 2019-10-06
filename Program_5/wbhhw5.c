#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//Add node to binary search tree.
Tree *insert(Tree *root, char *input){

    //If the root node is NULL then add a new node.
    if (root == NULL){
        Tree *new = (Tree *)malloc(sizeof(Tree));
        strcpy(new->data, input);
        new->left = NULL;
        new->right = NULL;
        new->number = 1;
        return new;
    }

    //If the root node is the same as the input data , then number+1.
    else if (strcmp(root->data, input) == 0){
        root->number++;
        return root;
    }

    //Use recursive to add data to the right subtree.
    else if (strcmp(root->data, input) < 0)
        root->right = insert(root->right, input);

    //Use recursive to add data to the left subtree.
    else if (strcmp(root->data, input) > 0)
        root->left = insert(root->left, input);

    return root;
}

void delete (Tree *root, char *input){

    //If the root node is NULL then do nothing.
    if (root == NULL)
        return;

    //If the root node is the same as the input data , then number-1 (Can't be less than 0).
    else if (strcmp(root->data, input) == 0){
        if (root->number > 0)
            root->number--;
        return;
    }

    //Use recursive to delete data to the right subtree.
    else if (strcmp(root->data, input) < 0)
        delete (root->right, input);

    //Use recursive to delete data to the left subtree.
    else if (strcmp(root->data, input) > 0)
        delete (root->left, input);

    return;
}

//Searching for binary search tree , Find the matching data then print it's data and number(must be large than 0).
void query(Tree *root, char *input){

    //If the root node is NULL then do nothing.    
    if (root == NULL)
        return;

    //If the root node is the same as the input data , print it's data and number(must be large than 0).
    else if (strcmp(root->data, input) == 0){
        if (root->number > 0)
            printf("%s\t%d\n", root->data, root->number);
        return;
    }

    //Use recursive to serch data to the right subtree.
    else if (strcmp(root->data, input) < 0)
        query(root->right, input);

    //Use recursive to serch data to the left subtree.
    else if (strcmp(root->data, input) > 0)
        query(root->left, input);

    return;
}

//Print the binary search tree by using inorder
void inorder(Tree *root){

    //If the root node is NULL then do nothing.
    if (root == NULL)
        return;
    
    //Use recursive to print data to the left subtree.    
    inorder(root->left);
    //print root's data and number(must be large than 0).
    if (root->number > 0)
        printf("%s\t%d\n", root->data, root->number);
    //Use recursive to print data to the right subtree. 
    inorder(root->right);

    return;
}

//Add node to new binary search tree from input tree.
Tree *sortinsert(Tree *sortroot, Tree *input){

    //If the new root node is NULL then add a new node from input tree.
    if (sortroot == NULL){
        Tree *new = (Tree *)malloc(sizeof(Tree));
        strcpy(new->data, input->data);
        new->left = NULL;
        new->right = NULL;
        new->number = input->number;
        return new;
    }

    //If the root node is the same as the input number , according to data decided to add node to the left subtree or right subtree.
    else if (sortroot->number == input->number)
        if (strcmp(sortroot->data, input->data) < 0)
            sortroot->right = sortinsert(sortroot->right, input);
        else
            sortroot->left = sortinsert(sortroot->left, input);

    //Use recursive to add data to the right subtree or left subtree.    
    else if (sortroot->number > input->number)
        sortroot->right = sortinsert(sortroot->right, input);

    else if (sortroot->number < input->number)
        sortroot->left = sortinsert(sortroot->left, input);

    return sortroot;
}

//Insert old binary search tree as input into new binary search tree
void sort(Tree *root, Tree *sortroot){

    if (root == NULL)
        return;

    //Use inorder to do traversal
    sort(root->left, sortroot);
    sortinsert(sortroot, root);
    sort(root->right, sortroot);

    return;
}

//Print the new binary search tree by using inorder
void sortinorder(Tree *sortroot){

    if (sortroot == NULL)
        return;

    sortinorder(sortroot->left);
    //print root's number and data(must be large than 0).
    if (sortroot->number > 0)
        printf("%d\t%s\n", sortroot->number, sortroot->data);
    sortinorder(sortroot->right);
    return;
}

//Printed it according to the data's number of binary search trees
void count(Tree *root){

    //Build the root node of a new tree , as a basis for all inserts.
    Tree *sortroot = (Tree *)malloc(sizeof(Tree));
    strcpy(sortroot->data, "sortroot");
    sortroot->left = NULL;
    sortroot->right = NULL;
    sortroot->number = 0;

    //Create a new, sorted binary search tree
    sort(root, sortroot);
    //Print the new binary search tree by using inorder
    sortinorder(sortroot);
}

int main(void){

    char line[64] = {0}, command[16] = {0}, input[32] = {0};
    Tree *root = NULL;

    while (fgets(line, 64, stdin)){

        capture(line, command, input);

        if (strcmp("insert", command) == 0)
            root = insert(root, input);

        else if (strcmp("delete", command) == 0)
            delete (root, input);

        else if (strcmp("query", command) == 0){
            printf("----------\n");
            query(root, input);
            printf("----------\n");
        }

        else if (strcmp("inorder", command) == 0){
            printf("----------\n");
            inorder(root);
            printf("----------\n");
        }

        else if (strcmp("count", command) == 0){
            printf("----------\n");
            count(root);
            printf("----------\n");
        }
    }

    return 0;
}