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

