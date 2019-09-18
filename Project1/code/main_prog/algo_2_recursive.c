#include "main.c"

/**
 * the recursive version of the alogrithm 2 to calculate power
 * @param double x, int n
 * @require x is a real number,
 *          n is an integer and n >= 0
 * @return double x ^ n
 */
double calculatePower(double x, int n)
{
    if (n == 0) {
        /** x ^ 0 = 1 */
        return 1.0;
    }
    if (n == 1) {
        return x;
    /**
     * to determinate wether n is an odd number
     * n & 1 = n % 2
     */
    } else if (n & 1) {
        /**
         * n >> 1 = n / 2
         */
        double sq = calculatePower(x, n >> 1);

        /**
         * x ^ n = (x ^ ((n - 1) / 2)) ^ 2 * x
         * (x is an odd number)
         */
        return sq * sq * x;
    } else {
        double sq = calculatePower(x, n >> 1);

        /**
         * x ^ n = (x ^ (n / 2)) ^ 2
         * (x is an even number)
         */
        return sq * sq;
    }
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
