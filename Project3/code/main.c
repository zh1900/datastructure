#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 10005
#define TIME_SEC_MAX 86400

#include "define_structures.c"
#include "hash.c"
#include "count_park_time.c"
#include "io.c"

int main(void)
{
    struct record records[N_MAX];
    int change_car_num[TIME_SEC_MAX], cur_car_num[TIME_SEC_MAX];
    int park_time[N_MAX];
    long long int car_id[N_MAX];
    int car_num;

    int n, k;
    int i;
    scanf("%d%d", &n, &k);

    getData(records, n);
    qsort(records, n, sizeof(struct record), compareRecord);
    car_num = countParkTime(n, records, car_id,
                            park_time, change_car_num, cur_car_num);
    outputNumberOfCars(k, cur_car_num);
    outputLongestTime(car_num, park_time, car_id);
    return 0;
}

