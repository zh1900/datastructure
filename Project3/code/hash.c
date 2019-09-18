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

