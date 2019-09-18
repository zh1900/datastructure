#include "main.c"

/**
 * the alogrithm 1 to calculate power
 * @param double x, int n
 * @require x is a real number,
 *          n is an integer and n >= 0
 * @return double x ^ n
 */
double calculatePower(double x, int n)
{
    double result = 1.0;
    int i;

    /** the for loop runs and multiplys n (contains 0) times. */
    for (i = 0; i < n; i ++) {
        result *= x;
    }
    return result;
}