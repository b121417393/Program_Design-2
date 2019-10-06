#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxHash 64

//Declare the Structure of a linked list node.
struct node
{
    char key[64];
    struct node *next;
};
typedef struct node Node;

//Declare the hash function.
unsigned int hashfunction(char *key)
{
    unsigned int value = 0;
    int i, len;

    len = strlen(key);

    //Add the ASCII code of all characters in the string.
    for (i = 0; i < len; i++)
        value = value + key[i];

    return value;
}

//Initialize the Hash table.
void initial(Node **hashtable)
{
	int i=0;
    for (i = 0; i < MaxHash; i++)
        hashtable[i] = NULL;
}

//Finding specific key in the Hash table.
Node *find(Node **hashtable, char *key)
{
    unsigned int hashvalue;
    Node *lptr;

    //Find out where a particular key is in a hash table.
    hashvalue = hashfunction(key) % MaxHash;
    lptr = hashtable[hashvalue];

    //Compare whether there is a target key in it.
    while (lptr != NULL)
    {
        if (strcmp(lptr->key, key) == 0)
            return lptr;
        lptr = lptr->next;
    }

    //If it cannot be found , return NULL.
    return NULL;
}

//Insert new key into the hash table.
void insert(Node **hashtable, char *key)
{
    unsigned int hashvalue;
    Node *lptr = NULL, *last = NULL;

    //Use hash function to determine where the key is inserted.
    hashvalue = hashfunction(key) % MaxHash;

    lptr = hashtable[hashvalue];
    //Finding where we can insert a new linked list.
    while (lptr != NULL)
    {
        last = lptr;
        lptr = lptr->next;
    }

    //Create a new linked list.
    Node *new = (Node *)malloc(sizeof(Node));
    strcpy(new->key, key);

    //The place to insert is at the head
    if (last == NULL)
        hashtable[hashvalue] = new;
    //The place to insert is at the end
    else
        last->next = new;
}

int main(int argc, char *argv[])
{
    char vocabulary[64] = {0}, line[1024] = {0}, key[10] = {0};
    char *ptr;
    int i = 0, len = 0;
    Node *hashtable[MaxHash], *point;
    FILE *fp;

    initial(hashtable);

    fp = fopen(argv[1], "r+");
    //Create a hash of the dictionary file
    while (fgets(vocabulary, 64, fp))
    {
        len = strlen(vocabulary);
        vocabulary[len - 1] = '\0';
        insert(hashtable, vocabulary);
    }
    fclose(fp);

    //When the input is from stdin
    if (argc == 2)
    {
        while (fgets(line, 1024, stdin))
        {
            len = strlen(line);
            ptr = line;
            //When the string has other data than "\n"
            while (len > 1)
            {
                //Positive long words first method for Chinese word segmentation (<=5)
                for (i = 15; i > 0; i = i - 3)
                {
                    strncpy(key, ptr, i);
                    key[i] = '\0';
                    point = find(hashtable, key);
                    //Find the corresponding string in the hash
                    if (point != NULL)
                    {
                        printf("%s\n", key);
                        len = len - i;
                        break;
                    }
                    //When only one Chinese character is left in the matching string
                    else if (i == 3)
                    {
                        printf("%s\n", key);
                        len = len - 3;
                        break;
                    }
                    else
                        continue;
                }
                ptr = ptr + i;
            }
        }
    }

    //the input is from file
    else
    {
        fp = fopen(argv[2], "r+");
        while (fgets(line, 1024, fp))
        {
            len = strlen(line);
            ptr = line;
            while (len > 1)
            {
                //Positive long words first method for Chinese word segmentation (<=5)
                for (i = 15; i > 0; i = i - 3)
                {
                    strncpy(key, ptr, i);
                    key[i] = '\0';
                    point = find(hashtable, key);
                    ////Find the corresponding string in the hash
                    if (point != NULL)
                    {
                        printf("%s\n", key);
                        len = len - i;
                        break;
                    }
                    //When only one Chinese character is left in the matching string
                    else if (i == 3)
                    {
                        printf("%s\n", key);
                        len = len - 3;
                        break;
                    }
                    else
                        continue;
                }
                ptr = ptr + i;
            }
        }
        fclose(fp);
    }

    return 0;
}
