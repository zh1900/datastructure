/*
 * the function to count times which the cars park for
 *
 * @param (int) n, (struct record *) records, (long long int *) car_id,
 *        (int *) park_time, (int *) change_car_num, (int *) cur_car_num
 * @return (int) car_num
 */
int countParkTime(int n, struct record *records, long long int *car_id,
                  int *park_time, int *change_car_num, int *cur_car_num)
{
    /* initialize park_time[i] = 0 */
    int i;
    for (i = 0; i < N_MAX; i ++) {
        park_time[i] = 0;
    }

    int last_status;
    int car_num = -1;

    for (i = 0; i < n; i ++) {
        /* check if record[i] is a new (different) car */
        if (i == 0 || records[i].plate_number != records[i - 1].plate_number) {
            /* car_id[k] = the plate number of k-th car */
            car_id[++ car_num] = records[i].plate_number;
            last_status = status_out;
            /*set last status as out */
        }

        /* check if it is a legal pair by last_status */
        char illegal = 0;
        if (records[i].status == last_status || records[i].status == status_in) {
            illegal = 1;
        }
        last_status = records[i].status;
        if (illegal) {
            continue;
        }

        /* calculate time the car park for */
        park_time[car_num] += records[i].moment.data - records[i - 1].moment.data;

        /* the number of cars is enhanced at the moment when the car comes in */
        change_car_num[records[i - 1].moment.data] ++;
        /* the number of cars is reduced at the moment when the car comes out */
        change_car_num[records[i].moment.data] --;
    }
    /*
     * because the array is 0-index, the number of
     * different cars should be car_num + 1
     */
    car_num ++;

    /* the number of cars at the time t is sum [i = 0 to t] {change_car_num[i]} */
    cur_car_num[0] = change_car_num[0];
    for (i = 1; i < TIME_SEC_MAX; i ++) {
        cur_car_num[i] = cur_car_num[i - 1] + change_car_num[i];
    }

    return car_num;
}

