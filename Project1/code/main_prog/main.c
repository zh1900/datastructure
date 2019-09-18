#include <stdio.h>
#include <time.h>

/**
 * define the function to calculate power.
 * @param double x, int n
 * @require x is a real number,
 *          n is an integer and n >= 0
 * @return double x ^ n
 */
double calculatePower(double x, int n);

int main()
{
    const double x = 1.0001;
    int iterations, n, i;

    scanf( "%d", &iterations);
    scanf( "%d", &n);

    clock_t start = clock(), stop; /** measure the performance of the function */

    /** run the function for "iterations" times */
    for (i = 0; i < iterations; i ++) {
        calculatePower(x, n);
    }

    stop = clock();

    int ticks = stop - start;
    double total_time = (double)ticks / CLOCKS_PER_SEC;
    double duration = total_time / iterations;
    printf("iterations = %d, ticks = %d, total_time = %lf, duration = %e\n", iterations, ticks, total_time, duration);
    return 0;
}
double calculatePower(double x, int n)
{
    double sq = x, result = 1.0;
    int i;
    /**
     * traverse all bits of n.
     * the for loop runs and multiplys log_2(n) times.
     */
    for (i = 0; (1 << i) <= n; i ++) {
        /**
         * if the i th bit of n is '1',
         * then multiplys result by x ^ (2 ^ i).
         */
        if ((1 << i) & n) {
            /** sq = x ^ (2 ^ i) */
            result *= sq;
        }
        /** x ^ (2 ^ (i + 1)) = (x ^ (2 ^ i)) ^ 2 */
        sq *= sq;
    }
    return result;
}
