/* the function to get input data */
void getData(struct record *records, int num)
{
    int i;
    char buf1[100], buf2[100], buf3[100];

    for (i = 0; i < num; i ++) {
        scanf("%s%s%s", buf1, buf2, buf3);

        /* convert plate number (string) to integer */
        records[i].plate_number = convertPlateNumToInt(buf1);

        /* convert time format from "HH:MM:SS" to second */
        records[i].moment.data = convertToSecond(buf2);

        /* convert "in", "out" to (int) 1, 0 */
        if (strcmp(buf3, "in") == 0) {
            records[i].status = status_in;
            /* status_in =  1 */
        } else if (strcmp(buf3, "out") == 0) {
            records[i].status = status_out;
            /* status_out = 0 */
        }
    }
}

/* the function to output the total number of cars parking on campus at a time */
void outputNumberOfCars(int k, int *cur_car_num)
{
    int i;
    char buf[100];
    for (i = 0; i < k; i ++) {
        scanf("%s", buf);

        /* convert time format from "HH:MM:SS" to second */
        int park_time = convertToSecond(buf);
        printf("%d\n", cur_car_num[park_time]);
    }
}

/*
 * the function to output the plate number of the car that has parked for
 * the longest time period, and the corresponding time length.
 */
void outputLongestTime(int car_num, int *park_time, long long int *car_id)
{
    int i, max_park_time = 0;

    /* calculate the maximum number of park time period */
    for (i = 0; i < car_num; i ++) {
        if (max_park_time < park_time[i]) {
            max_park_time = park_time[i];
        }
    }

    /*
     * output all the plate number of cars which has
     * parked for the longest time period
     */
    for (i = 0; i < car_num; i ++) {
        if (park_time[i] == max_park_time) {
            convertIntToPlateNum(car_id[i]);
            putchar(' ');
        }
    }
    /* output the time length */
    printf("%02d:%02d:%02d\n",
           max_park_time / 3600, (max_park_time / 60) % 60, max_park_time % 60);
}

