#include "main.c"

/**
 * the iterative version of the alogrithm 2 to calculate power
 * @param double x, int n
 * @require x is a real number,
 *          n is an integer and n >= 0
 * @return double x ^ n
 */
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
