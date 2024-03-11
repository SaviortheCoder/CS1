#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define RAD2_DEGREES (180l / M_PI)
#define MAX_GROUPTOTAL 50000001


//struct deffinitions and alliases
typedef struct group

{

    double angle;
    int size;

} group;

void mergee(group *list, int left, int right, int middle);
void mergesortt(group *list, int left, int right);
double maximum_angle(group* list, int list_size);             
int problem_one(group* list, int size, int default_angle);


//start at x
//add all sizes of every group between x and x+ proj_angle
//if the sum is less than current min than update
//move to next starting group

int problem_one(group* list, int size, int default_angle){

    double starting_angle;
    double ending_angle;
    int inside_grouptotal = 0;  //group number inside the meassured angle
    int current_minimum = MAX_GROUPTOTAL;    


    //projector and then, using that starting point go through
    //every group remaining in the link in order to find which selection
    //of location  for the projector angle encompasses the fewest people
    for(int i = 0; i < size; i++){
        starting_angle = list[i].angle;
        ending_angle = default_angle + starting_angle;

        if(ending_angle >= 360){ //suppose to be given >360
            ending_angle -= 360;
        }
    
        //command x
        for(int j = 0; j < size; j++){
            if(list[j].angle >= starting_angle && list[j].angle <= ending_angle){
                if(list[j].angle != starting_angle){
                    inside_grouptotal += list[j].size;
                }
            }
        }
        
        if(inside_grouptotal < current_minimum){
            current_minimum = inside_grouptotal;
        }
        inside_grouptotal = 0;
    }
    return current_minimum; 
}


//maximum function
double maximum_angle(group* list, int list_size){ //helps solves number 2 because the list to arrays is already sorted
    double ret = list[1].angle - list[0].angle;



    for(int i = 0; i < list_size - 1; i++){
        if(list[i+1].angle - list[i].angle > ret){
            ret =list[i+1].angle - list[i].angle;

        }
    }
    if(list[list_size-1].angle - list[0].angle > ret){  //Special case for the end of the array
        ret = list[list_size-1].angle - list[0].angle;
    }

    return ret;     //ret = the largest angle of projection without any obstuction
}


//  Merge the sorted arrrays:
void mergee(group *list, int left, int right, int middle)
{

    int left_subarray_index, right_subarray_index, mergedarr_index;
    int left_subarr_size = middle - left + 1;
    int right_subarr_size = right - middle;

    //  Allocate temporary arrays for copying into:
    group *left_temp = (group *)malloc(sizeof(group) * left_subarr_size);
    group *right_temp = (group *)malloc(sizeof(group) * right_subarr_size);

    //  fill temporary arrays with data
    for (left_subarray_index = 0; left_subarray_index < left_subarr_size; left_subarray_index++)
    {
        left_temp[left_subarray_index] = list[left + left_subarray_index];
    }
    for (right_subarray_index = 0; right_subarray_index < right_subarr_size; right_subarray_index++)
    {
        right_temp[right_subarray_index] = list[right + right_subarray_index]; 
    }

    //  We merge the temporary arrays back into the original at appropriate locations:
    left_subarray_index = right_subarray_index = 0;
    mergedarr_index = left;

    // merge the temp arrays into the merged sorted array
    while (left_subarray_index < left_subarr_size && right_subarray_index < right_subarr_size)
    {
        
        // if and else is asking which is smaller and throwing that value inside the main sorted array
        //in other words mergin the temporary array with the orignal at the appropriate locations
        if (left_temp[left_subarray_index].angle <= right_temp[right_subarray_index].angle)
        {

            list[mergedarr_index] = left_temp[left_subarray_index];
            left_subarray_index++;
        }
        else
        {
            list[mergedarr_index] = right_temp[right_subarray_index];
            right_subarray_index++;
        }
        mergedarr_index++; // after each loop adding one element to the sorted array
    }

    //2 while loops to take care of any extre elements in the array
    while (left_subarray_index < left_subarr_size)
    {
        list[mergedarr_index] = left_temp[left_subarray_index];
        left_subarray_index++;
        mergedarr_index++;
    }
    while (right_subarray_index < right_subarr_size)
    {
        list[mergedarr_index] = right_temp[right_subarray_index];
        right_subarray_index++;
        mergedarr_index++;
    }

    //clean uppp:
    free(left_temp);
    free(right_temp);
}
// Merge the sort using recursion
void mergesortt(group *list, int left, int right)

{

    if (right <= left)return; //  base case

     //Calculate middle and then determine if we have more to divide:
    int middle = left + (right - left) / 2; // function for middle for our recursice call

    //Recursively call sort on each half:
    mergesortt(list, left, middle);         // left spit then sort
    mergesortt(list, middle + 1, right);    // right spit then sort

    //finally, merge the two halves
    mergee(list, left, right, middle);      // merge sorted arrays
}


int main(void)
{
    int default_angle;  // N
    int people_present; // A
    int x_coordinates, y_coordinates;
    int group_total; // the number of people in a given group
    double radians;
    group *listofgroups;

    scanf("%d %d", &people_present, &default_angle);
    listofgroups = (group *)malloc(sizeof(group) * people_present);

    if (listofgroups == NULL)
    {
        printf("MEMORY ALLOCATION FAILED");
        return 1;
    }

    for (int i = 0; i < people_present; i++)
    {

        scanf("%d %d %d", &x_coordinates, &y_coordinates, &group_total);

        radians = atan2(((double)y_coordinates), ((double)x_coordinates));
        listofgroups[i].angle = radians * RAD2_DEGREES; // atan2 is in rad must change to degree
        listofgroups[i].size = group_total;

    }

    mergesortt(listofgroups, 0, people_present - 1);
    printf("%d\n", problem_one(listofgroups, people_present, default_angle));
    printf("%lf\n", maximum_angle(listofgroups, people_present));
    free(listofgroups);
    return 0;
}