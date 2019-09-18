/* define boolean variable */
typedef char bool;

/* false = 0, true = 1 */
enum { false, true };

/* define the structure of three integers */
struct three_int { int dis, sent, back; };

/*
 * the function to make three_int
 * @param int d, int s, int b
 * @return struct three_int (dis = d, sent = s, back = b)
 */
struct three_int makeThreeInt(int d, int s, int b)
{
    struct three_int t;
    t.dis = d;
    t.sent = s;
    t.back = b;
    return t;
}

/*
 * the function to compare two three_int
 *
 * @param struct three_int a, struct three_int b
 * @return bool a < b
 *
 * The rule of comparing two pairs :
 *
 * 1. Choose the shortest path.
 *
 * 2. If there are more than one shortest path, the one that requires
 * the least number of bikes sent from PBMC will be chosen.
 *
 * 3. Note that if such a path is not unique, output the one that
 * requires minimum number of bikes that we must take back to PBMC.
 */
bool compareThreeInt(struct three_int a, struct three_int b)
{
    return (bool)(
        a.dis == b.dis ?
        (a.sent == b.sent ? a.back < b.back : a.sent < b.sent) :
        a.dis < b.dis
    );
}

/* define the graph structure of this problem */
struct graph
{
    int maximum_capacity, vertex_number, problem_station;
    int current_bike[VERTEX_MAX];
    /* current_bike[i] is the current number of bikes at station i */
    int weight[VERTEX_MAX][VERTEX_MAX];
    /* weight[i][j] is the time wiil be taken to move betwen stations i and j */
};
