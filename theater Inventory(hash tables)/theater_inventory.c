#include <stdio.h>  ///standard input output
#include <stdlib.h> //dynamically allocation +++
#include <string.h>

// study text parsing more

#define MAXLEN 19
#define TABLESIZE 300007

typedef struct item
{

    char name[MAXLEN + 1];
    int quantity;
    int saleprice;

} item;

typedef struct node
{

    item *iPtr;
    struct node *next;

} node;

typedef struct hashtable
{

    node **lists;
    int size;

} hashtable;

// prototypes
int hashfunc(char *word, int size);
void createtable(hashtable *table);
node *createnode(item *a_item);
item *createitem(char name[], int quantity, int saleprice);
void buy(hashtable *hashPtr, int *total_movie_cash, char *item_name, int quantity, int totalprice, int *num_ops);
void display(hashtable *table);
void sell(hashtable *table, int *total_movie_cash, char *item_name, int quantity,int *num_ops);
void change_price(hashtable *table, char item_name[], int new_price,int *num_ops);

//the given hash function
//
int hashfunc(char *word, int size)
{
    int len = strlen(word);
    int ret = 0;
    for (int i = 0; i < len; i++)
    {
        ret = (1151 * ret + (word[i] - 'a')) % size;
    }
    return ret;
}


void createtable(hashtable *table)
{
    table->lists = (node **)malloc(sizeof(node *) * TABLESIZE);
    table->size = TABLESIZE;
    for (int i = 0; i < TABLESIZE; i++)
    {
        table->lists[i] = NULL;
    }
}

//creates the linkk list nodes
//set the item pointer to the item being past in, the next linklist to NULL and returning the node pointer

node *createnode(item *a_item)
{
    node *ret = (node *)malloc(sizeof(node));
    ret->iPtr = a_item;
    ret->next = NULL;
    return ret;
}

item *createitem(char name[], int quantity, int saleprice)
{
    item *ret = (item *)malloc(sizeof(item));
    strcpy(ret->name, name); // need strcpy to copy strings
    ret->quantity = quantity;
    ret->saleprice = saleprice;
    return ret;
}

void buy(hashtable *hashPtr, int *total_movie_cash, char *item_name, int quantity, int totalprice, int *num_ops)
{ 
   //used the hash table to create an index in the table
    int index = hashfunc(item_name, TABLESIZE);
    node *current_node = hashPtr->lists[index];

    // checking if the item is in the list
    while (current_node != NULL)
    {
        (*num_ops)++;
        // we found the item
        if (strcmp(item_name, current_node->iPtr->name) == 0)
        {
            // update the quantity and the price
            current_node->iPtr->quantity += quantity;
            // current_node->iPtr->saleprice += saleprice;
            *total_movie_cash -= totalprice;
            printf("%s %d %d\n", item_name, quantity, *total_movie_cash);
            return;
        }
        current_node = current_node->next;
    }
    (*num_ops)++;
    // traversal of the linked list
    item *item_ptr = createitem(item_name, quantity, 1);
    node *new_node = createnode(item_ptr);
    new_node->next = hashPtr->lists[index];
    hashPtr->lists[index] = new_node;
    *total_movie_cash -= totalprice;
    printf("%s %d %d\n", item_name, quantity, *total_movie_cash);
}

void display(hashtable *table)
{
    for (int i = 0; i < TABLESIZE; i++)
    {
        if (table->lists[i] != NULL)
        {
            node *current = table->lists[i];
            while (current != NULL)
            {
                printf("%s %d %d\n", current->iPtr->name, current->iPtr->quantity, current->iPtr->saleprice);
                current = current->next;
            }
        }
    }
}


void sell(hashtable *table, int *total_movie_cash, char *item_name, int quantity, int *num_ops)
{
    //used the hash table to create an index in the table
    int index = hashfunc(item_name, TABLESIZE);
    node *current_node = table->lists[index]; // hashPtr

    while (current_node != NULL)
    {
        (*num_ops)++;
        // we found it
        if (strcmp(item_name, current_node->iPtr->name) == 0)
        {
            // if the stock of the item in question is less than the quantity requested, then just sell all of the available quantity of that item
            if (quantity > current_node->iPtr->quantity)
            {
                *total_movie_cash += current_node->iPtr->quantity * current_node->iPtr->saleprice;
                current_node->iPtr->quantity = 0;
                printf("%s %d %d\n", item_name, current_node->iPtr->quantity, *total_movie_cash);
            }
            else
            {
                current_node->iPtr->quantity -= quantity;
                *total_movie_cash += quantity * current_node->iPtr->saleprice;
                printf("%s %d %d\n", item_name, current_node->iPtr->quantity, *total_movie_cash);
            }
            return;
        }
        current_node = current_node->next;

    }
}

void change_price(hashtable *table, char item_name[], int new_price, int *num_ops)
{
    //used the hash table to create an index in the table
    int index = hashfunc(item_name, TABLESIZE);
    node *current_node = table->lists[index];

    while (current_node != NULL)
    {
        //increase the number of operations
        (*num_ops)++;

        // found item
        if (strcmp(item_name, current_node->iPtr->name) == 0)
        {
            // change price in struct then return
            current_node->iPtr->saleprice = new_price;
            return;
        }
        current_node = current_node->next;
    }
}

int main(void)
{

    hashtable table;
    int num_of_command;
    char *text_line;
    char quantity[7];
    int quanitity_size;
    int num_totalprice;
    char total_price[8];
    char *item;
    int new_price;
    char newprice_char[15];
    char *command;
    int total_cash = 100000;
    int i, j, k, p;
    int total_ops = 0;

    
    createtable(&table);
    //takes the number of commands from the user
    scanf("%d", &num_of_command);

    while (getchar() != '\n');          // takes care of the leftovers new line
    fflush(stdin); // flushing the characters out

    printf("%d\n", num_of_command);

    //dynmaically 
    text_line = (char *)malloc(sizeof(char) * 50);
    command = (char *)malloc(sizeof(char) * 20);
    item = (char *)malloc(sizeof(char) * 20);

    // string intialization
    for (int g = 0; g < 50; g++)
    {
        text_line[g] = '\0';
    }
    for (int g = 0; g < 20; g++)
    {
        command[g] = '\0';
    }
    for (int g = 0; g < 20; g++)
    {
        item[g] = '\0';
    }
    
    //creating a loop to go through the complete number of commands 
    for (int index = 0; index < num_of_command; index++)
    {   
        //gets the entire line of input from the user
        fgets(text_line, 49, stdin); // stdin is keyboard

        // parsing the name of the command and the item name for all the possible commands
        for (i = 0; text_line[i] != ' '; i++)
        {
            command[i] = text_line[i];
        }
        command[++i] = '\0';

        for (j = i; text_line[j] != ' ' && text_line[j] != '\n'; j++)
        {
            item[j - i] = text_line[j];
        }
        item[j - i] = '\0';

        //
        if (strcmp(command, "buy") == 0)
        {
            // string parsing for quantity field in the buy function
            for (k = j + 1; text_line[k] != ' ' && text_line[k] != '\n'; k++)
            {
                quantity[k - j - 1] = text_line[k];
            }
            quantity[k - j - 1] = '\0';
            quanitity_size = strtol(quantity, NULL, 10);

            //string parsing for the total price field for the buy function
            for (p = k + 1; text_line[p] != ' ' && text_line[p] != '\n'; p++)
            {
                total_price[p - k - 1] = text_line[p];
            }
            total_price[p - k - 1] = '\0';
            num_totalprice = strtol(total_price, NULL, 10);

            //after we break apart our string we use the varibale we saved the input in to call the function
            buy(&table, &total_cash, item, quanitity_size, num_totalprice, &total_ops);
        }
        
        //the 3 if statements compare the input string to the name of the commands and excutes accordingly
        if (strcmp(command, "sell") == 0)
        {
            // string parsing for quantity field inthe sell function
            for (k = j + 1; text_line[k] != ' ' && text_line[k] != '\n'; k++)
            {
                quantity[k - j - 1] = text_line[k];
            }
            quantity[k - j - 1] = '\0';
            quanitity_size = strtol(quantity, NULL, 10);

           //after we break apart our string we use the varibale we saved the input in to call the function
            sell(&table, &total_cash, item, quanitity_size, &total_ops);
        }

        if (strcmp(command, "change_price") == 0)
        {
            //sting parsing for the new price in the change_price function
            for (k = j + 1; text_line[k] != ' ' && text_line[k] != '\n'; k++)
            {
                newprice_char[k - j - 1] = text_line[k];
            }
            newprice_char[k - j - 1] = '\0';
            new_price = strtol(newprice_char, NULL, 10);

            //after we break apart our string we use the varibale we saved the input in to call the function
            change_price(&table, item, new_price, &total_ops);
        }

        for (int g = 0; g < 20; g++)
        {
            command[g] = '\0';
        }
        for (int g = 0; g < 50; g++)
        {
            text_line[g] = '\0';
        }
        for (int g = 0; g < 20; g++)
        {
            item[g] = '\0';
        }
    }
    //print the total cash of the threater plus the total amount of operatioons
    printf("%d\n %d\n", total_cash, total_ops);

    //freeing the dynmaic memory
    free(text_line);
    free(command);
    free(item);

    // display(&table);
}