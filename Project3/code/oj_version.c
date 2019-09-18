#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 10005
#define TIME_SEC_MAX 86400

/* define status_out = 0, status_in = 1 */
enum { status_out, status_in };

/* define the structure of time format */
struct time_format
{
    int data;
};

/* define the structure of input record */
struct record
{
    long long int plate_number;
    struct time_format moment;
    char status;
};

/* the function to determine the sign of a long long int
 *
 * @param (long long int) x
 * @return (int) y = 0,  if x = 0
 *                 = 1,  if x > 0
 *                 = -1, if x < 0
 */
int sgn(long long int x)
{
    return x == 0 ? 0 : (x < 0 ? -1 : 1);
}

/* the function for qsort to compare two records
 *
 * the rule of comparing two records:
 * 1. compare the alphabet order of plate numbers of two records
 * 2. compare the time of two records
 */
int compareRecord(const void *a, const void *b)
{
    struct record *A = (struct record*)a;
    struct record *B = (struct record*)b;
    return (A->plate_number == B->plate_number) ?
           sgn(A->moment.data - B->moment.data) :
           sgn(A->plate_number - B->plate_number);
}

/*
 * convert plate number (string type) to integer
 *
 * @param (char) *str
 * @return (long long int) hash of the plate number
 *
 * because plate number has 7 character
 * 36 ^ 7 = 78364164096 > 2147483647 (maximum of 32 bit integer)
 * we have to use a long long int (64 bit integer) to save the plate number
 */
long long int convertPlateNumToInt(char *str)
{
    int i;
    long long int result = 0;
    for (i = 0; str[i]; i ++) {
        result *= 36;
        if (str[i] >= '0' && str[i] <= '9') {
            /* map '0' ~ '9' to 0 ~ 9 */            
            result += str[i] - '0';
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            /* map 'A' ~ 'Z' to 10 ~ 35 */
            result += str[i] - 'A' + 10;
        }
    }
    return result;
}

/* convert integer to plate number (directly output) */
void convertIntToPlateNum(long long int p)
{
    long long int i;
    for (i = 1; i <= p; i *= 36);
    for (i /= 36; i; i /= 36) {
        int c = (p / i) % 36;
        if (c < 10) {
            /* map 0 ~ 9 to '0' ~ '9' */            
            c = c + '0';
        } else {
            /* map 10 ~ 35 to 'A' ~ 'Z' */
            c = c - 10 + 'A';
        }
        putchar(c);
    }
}

/*
 * convert time format from "HH:MM:SS" (string) to second
 * 
 * @param (char) *str
 * @return (int) second
 *
 * string: HH:MM:SS
 * index:  01 34 67
 *
 * hour   = str[0] * 10 + str[1]
 * minute = str[3] * 10 + str[4]
 * second = str[6] * 10 + str[7]
 */
int convertToSecond(char *str)
{
    int h = (str[0] - '0') * 10 + (str[1] - '0');
    int m = (str[3] - '0') * 10 + (str[4] - '0');
    int s = (str[6] - '0') * 10 + (str[7] - '0');
    return (h * 60 + m) * 60 + s;
}

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

