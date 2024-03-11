#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_GROUPTOTAL 1001  // Max group size

typedef struct Group {
    double angle;
    int size;
} Group;

int compare_group(const void *a, const void *b) {
    return ((Group *)a)->angle - ((Group *)b)->angle;
}

unsigned int problem_one(Group *list, int size, int default_angle) {
    unsigned int current_minimum = MAX_GROUPTOTAL;
    int left = 0;
    int right = 0;
    int inside_grouptotal = 0;

    while (left < size) {
        double ending_angle = list[left].angle + default_angle;

        while (list[right].angle <= ending_angle && right < size) {
            inside_grouptotal += list[right].size;
            right++;
        }

        current_minimum = (inside_grouptotal < current_minimum) ? inside_grouptotal : current_minimum;
        inside_grouptotal -= list[left].size;
        left++;
    }

    return current_minimum;
}

double find_largest_non_overlapping_angle(Group *list, int size) {
    double largest_non_overlapping_angle = 0.0;
    int left = 0;
    int right = 0;

    while (left < size) {
        double ending_angle = list[left].angle + largest_non_overlapping_angle;

        while (list[right].angle <= ending_angle && right < size) {
            largest_non_overlapping_angle = list[right].angle - list[left].angle;
            right++;
        }

        left++;
    }

    return largest_non_overlapping_angle;
}

int main() {
    int default_angle;
    int people_present;
    Group *listofgroups;

    scanf("%d %d", &people_present, &default_angle);
    listofgroups = (Group *)malloc(sizeof(Group) * people_present);

    if (listofgroups == NULL) {
        printf("MEMORY ALLOCATION FAILED");
        return 1;
    }

    for (int i = 0; i < people_present; i++) {
        int x, y, group_total;
        scanf("%d %d %d", &x, &y, &group_total);
        double radians = atan2(y, x);
        listofgroups[i].angle = radians * 180.0 / M_PI;
        listofgroups[i].size = group_total;
    }

    qsort(listofgroups, people_present, sizeof(Group), compare_group);

    unsigned int min_people_in_projection = problem_one(listofgroups, people_present, default_angle);
    double largest_non_overlapping_angle = find_largest_non_overlapping_angle(listofgroups, people_present);

    printf("%u\n", min_people_in_projection);
    printf("%.4lf\n", largest_non_overlapping_angle);

    free(listofgroups);
    return 0;
}

