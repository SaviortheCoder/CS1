#include <stdio.h>
#include <stdlib.h>

typedef struct customer
{ // struct the represents an individual person

    char *name[50];
    // 30 + 8*5 = 70 seconds
    int arr_time;   // the arrival time in seconds
    int cus_ticket; // the total amount of tickets a customer buys
    int q_posiion;  // the position of the customers in line

} customer;

typedef struct node
{ // reprresents a customers plus the next and data pointer

    customer *data;
    node *next;
    node *prev;

} node;

typedef struct queue
{ // building a list of customers using queue to store the customers

    node *front;
    node *back;
    int size; // size of queue
    int current_size;
    int booth_num;

} queue;

customer *create_customer(char *name, int time, int ticket, int position); // prototype
void enqueue(queue *que, char *name, int arrival, int ticket_num);
customer *dequeue(queue *que);
void process_customer(queue *que, int queue_num, int booth_num); // todo

int calc_Q(char *name);     // todo
customer *peek(queue *que); // todo
int empty(queue *que);
int size(queue *que);
int current_size(queue *que);

customer *create_customer(char *name, int time, int ticket, int position)
{

    customer *ret = malloc(sizeof(customer));
    strcpy(ret->name, name);
    ret->arr_time = time;
    ret->cus_ticket = ticket;
    ret->q_posiion = position;

    return ret;
}

int calc_Q(char *name)
{
    char first_letter = name[0]; // first letter equals p in p%13

    return (int)first_letter % 13;
}

void enqueue(queue *que, char *name, int arrival, int ticket_num)
{ //  Insert Queue function

    int calc_name = calc(name);
    customer *cust = create_customer(name, arrival, ticket_num, 0); // created a customer
    node *new_node = (node *)malloc(sizeof(node));                  // allocate memory for new node
    new_node->next = NULL;                                          // set the new_node to Null as default
    new_node->prev = NULL;
    new_node->data = cust; // connecting the customer to the node   jusut drrew the box without connecting the arroows

    if (que->back == NULL)
    {
        que->back = new_node;
        que->front = new_node;
    }

    else
    {
        new_node->next = que->back; // connecting the new node to the back of the queue
        que->back->prev = new_node;
        que->back = new_node; // connected the new back of the line equal to the new node.... making the new node the new back
    }
    que->size++;
    que->current_size++;
}

customer *dequeue(queue *que)
{ // dequeue = delete function

    node *temp = que->front; //  we set the front of a queue to a a temp variable we have broken down the list into old front and we will no longer be able to access to the node in order to free
    customer *cus = que->front->data;
    que->front->prev->next = NULL;
    que->front = que->front->prev;

    que->current_size--;
    free(temp);
    return cus;
}

void process_customer(queue *que, int queue_num, int amount_of_booths)
{
    
    int total_t;
    customer* cus;
    int checkout_time;
    int min; 
    int queues_per_booth = 12/amount_of_booths;
    int extra_queues = 12%amount_of_booths;


    

    //
    for (int i = 0; i < 12; i++)
    {
        que[i].booth_num = i % amount_of_booths + 1;
    }

    /*this for loop works on creating one customer for each of the booth
    using the minimum funciton customer to go through the queue*/
    for (int j = 0; j < amount_of_booths; j++)
    {
        total_t = 0;
    
        min = minimum_time(que, amount_of_booths);
        printf("Booth %d\n", j + 1);
        cus = dequeue(&que[min]);  // this might be wrong
        checkout_time = 30 + cus->cus_ticket *5 + cus->arr_time;
        printf("%s from line %d checks out at time %d", cus->name, min+1,checkout_time);
        
    }

}

/* */
int minimum_time(queue* que, int booth_numm){   

    int current_min = 1000000001;
    int ret;

    for(int i=0; i< 12; i++){
        if(que[i].booth_num == booth_numm){
            if(que[i].front->data->arr_time < current_min){
                ret = i;
                current_min = que[i].front->data->arr_time;
            }
        }
    }

    return ret;
}

int empty(queue *que)
{
    return empty(que) == 1 ? 1 : 0;
}

int size(queue *que)
{
    return que->size;
}

int current_size(queue *que)
{
    return que->current_size;
}

customer *peak(queue *que)
{
    return que->front->data;
}

int main(void)
{
    int number_of_customers;
    int num_of_booths;
    char name[50];
    int number_of_tickets;
    int arrival_t;
    queue arr[12];
    queue sorted_arr[12];
    int queue_num;

    for (int i = 0; i < 12; i++)
    { // setting up the queue from the potential customers
        arr[i].current_size = 0;
        arr[i].back = NULL;
        arr[i].front = NULL;
        arr[i].size = 0;
    }

    scanf("%d %d", &number_of_customers, &num_of_booths);

    for (int i = 0; i < number_of_customers; i++)
    {
        scanf("%s %d %d", name, &number_of_tickets, &arrival_t);
        queue_num = calc_Q(name);

        if (queue_num == 0)
        { // come back later to finish this had to do with the (P % 13)
            int cur_min = 0;

            for (int i = 0; i < 12; i++)
            {
                if (arr[i].size < arr[cur_min].size)
                {
                    cur_min = i;
                }
            }
        }
        else
        {
            enqueue(&arr[queue_num - 1], name, arrival_t, number_of_tickets);
        }

        for (int i = 0; i < 12; i++)
        {
            sorted_arr[i] = arr[i];
        }

        for (int i = 0; i < 12; i++)
        {
            int min = i;
            queue temp;
            int j;

            for (j = 0; j < 11; i++)
            {
                if (sorted_arr[i].size < sorted_arr[min].size) // algorithim for finding the smallest thingin the array
                {
                    min = j;
                }
            }
            temp = sorted_arr[i];   //   array sort function
            sorted_arr[i] = sorted_arr[j];
            sorted_arr[j] = temp;
        }
    }

    return 0;
}
