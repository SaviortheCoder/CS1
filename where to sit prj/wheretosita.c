#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct people{

    char name[20];  // names of the people in the list
    int popcorn_boolean; //whether or not they get popcorn

}people;


void swap(people* p1, people* p2);
int permutation(people* arr, int left, int right);


void swap(people* p1, people* p2){
    people temp;

    temp.popcorn_boolean = p1->popcorn_boolean;
    strcpy(temp.name, p1->name);

    p1->popcorn_boolean = p2->popcorn_boolean;
    strcpy(p1->name, p2->name);

    p2->popcorn_boolean = temp.popcorn_boolean;
    strcpy(p2->name, temp.name);
    
}

int permutation(people* arr, int left, int right){

    int ret;

    for(int i= left; i <= right; i++){
        swap(&arr[left], &arr[i]);
        ret += permutation(arr, left + 1, right);
        swap(&arr[left], &arr[i]);
    }
    return ret;
}

int main(void){

    int movie_attendee_total;  
    int pairs_of_people;  ///the pairs of peole that dont want to sit next to each other


    people* people_list = (people*)malloc(sizeof(people) * movie_attendee_total);
    people* p1 = (people*)malloc(sizeof(people));

    scanf("%d %d", &movie_attendee_total, &pairs_of_people);

    for(int i=0; i<movie_attendee_total; i++){
        scanf("%s %d", people_list[i].name, &people_list[i].popcorn_boolean);
    }

    
    int counterrr = 0;
    permutation(people_list, 0, movie_attendee_total-1);
    printf("%d\n", counterrr);
    free(people_list);
    return 0;
}