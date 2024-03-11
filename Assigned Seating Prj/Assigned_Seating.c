#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_OF_ROWS 4

typedef struct Reservation
{

    char *name;     //   Start and end of the reservation
    int start, end; //   Name of the person who reserved this range

} Reservation;

typedef struct Row
{

    Reservation *array;   //    The array of reservations
    int max_reservations; //    the spots in the array
    // using in
    int num_reservations; //     occupied spots in the array

} Row;

typedef struct Theater
{

    Row *row; //    The array of rows in the theater

} Theater;

int buy(Theater movies, int row, int start, int end, char *person);
int lookup(Theater movies, int row, int seat);

//   need functions for lookup (search) And Buy
//   lookup takes 2 args and buy takes 4 args
//  for buy function set function to int to return 0 or 1 for pass or fail on buy

int main(void)
{

    // TODO: NEED PRINT FUNCTION IN MAIN
    // TODO NEED FREE FUNCTION FOR MALLOC

    char command[20];
    Theater movie_theater;                                           //  this variable enables me to access the different variables within the struct
    movie_theater.row = (Row *)malloc(sizeof(Row) * NUMBER_OF_ROWS); //

    for (int i = 0; i < NUMBER_OF_ROWS; i++)
    {
        movie_theater.row[i].max_reservations = 1;                                   //  sets the max res to 1 to have space to add the reservations
        movie_theater.row[i].num_reservations = 0;                                   //  presets the reservations to 0
        movie_theater.row[i].array = (Reservation *)malloc(sizeof(Reservation) * 1); // Allocated a space for potential reservations
    }

    while (1)
    {

        scanf("%s", command);
        if (strcmp(command, "LOOKUP") == 0)
        {
            int isle, chair;

            scanf("%d %d", &isle, &chair);
            lookup(movie_theater, isle, chair);
        }

        else if (strcmp(command, "BUY") == 0)
        {
            char name[50];
            int row, start, end;

            scanf("%d %d %d %s", &row, &start, &end, name);
            if (buy(movie_theater, row, start, end, name) == 1)
            {
                printf("FAILURE\n");
            }
            else
            {
                printf("SUCCESS\n");
            }
        }

        else
        {
            break;
        }
    }
    free(movie_theater.row);
    return 0;
}

int buy(Theater movies, int row, int start, int end, char *person)
{
    // int num_seat = end - start; //     an algorithim for the number of seats on person reservation
    if (movies.row[row - 1].num_reservations >= movies.row[row - 1].max_reservations)
    {                                                                                                             //  the algorithim for continuously reallocing memory
        movies.row[row - 1].array = realloc(movies.row[row - 1].array, movies.row[row - 1].max_reservations * 2); //  if the number of reservations plus the total number of seats is greater than or eqaul to the max num of reservations then double the total memory
        movies.row[row - 1].max_reservations *= 2;
    }

    for (int i = 0; i < movies.row[row - 1].num_reservations; i++)
    {

        if (start >= movies.row[row - 1].array[i].start && start <= movies.row[row - 1].array[i].end)
        { ///   The Algorithim to check if any reservations ovelap with other reservations start
            return 1;
        }
        if (end >= movies.row[row - 1].array[i].start && end <= movies.row[row - 1].array[i].end)
        { ///   The Algorithim to check if any reservations ovelap with other reservations end
            return 1;
        }
    }
    //  copying the start seats to he reservations start
    movies.row[row - 1].array[movies.row[row - 1].num_reservations].start = start;

    //  copying the end seats to he reservations end
    movies.row[row - 1].array[movies.row[row - 1].num_reservations].end = end;

    //  allocates the memory in order to copy the name into the reservation
    movies.row[row - 1].array[movies.row[row - 1].num_reservations].name = ((char *)malloc(sizeof(char) * (strlen(person))) + 1);

    //  the line of code that actually copies the reservation from the person
    strcpy(movies.row[row - 1].array[movies.row[row - 1].num_reservations].name, person);

    //  cycling the number of reservation or the counter for the reservation array
    movies.row[row - 1].num_reservations++;
    printf("%d\n", movies.row[row - 1].num_reservations);

    free(movies.row[row - 1].array[movies.row[row - 1].num_reservations].name);
    return 0;
}

int lookup(Theater movies, int row, int seat)
{
    // for looop for going thru all the reservations
    for (int i = 0; i < movies.row[row - 1].num_reservations; i++)
    {

        // if(start <= seat && end >= seat) printf(reservation->name);
        if (movies.row[row - 1].array[i].start <= seat && movies.row[row - 1].array[i].end >= seat)
        {                                                      //  if statement for finding the seats selected between the start and end a reservation
            printf("%s\n", movies.row[row - 1].array[i].name); //    printing the name of the reservation if found
            return 0;
        }
    }
    printf("No one"); //    printing no one if no reservation was found
    return 0;
}