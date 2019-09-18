#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VERTEX_MAX 505
#define INF 1000000000

#include "define_structures.c"
#include "io.c"
#include "get_best_path.c"

/* convert string (C style) to integer (positive) */
int toInt(char *str)
{
    int result = 0, i;
    for (i = 0; str[i]; i ++) {
        result = result * 10 + str[i] - '0';
    }
    return result;
}

int main(int argc, char **argv)
{
    char *iterations_str = argv[1];

    const int starting_vertex = 0;
    struct graph *G = (struct graph*)malloc(sizeof(struct graph));
    struct three_int result;
    int best_path_next_vertex[VERTEX_MAX];

    inputData(G);

    /** measure the performance of the function */
    clock_t start = clock(), stop;

    /** run the functions (without I/O function) for "iterations" times */
    int iterations = toInt(iterations_str), i;
    for (i = 0; i < iterations; i ++) {
        bool vis[VERTEX_MAX];
        initVis(vis);
        result = getBestPath(G, vis, best_path_next_vertex, starting_vertex, 0, 0, 0);
        if (result.dis == INF) {
            puts("There is no shortest path!");
            return 0;
        }
    }
    stop = clock();
    
    /* output the solution to stdout */
    outputSolution(result, best_path_next_vertex, starting_vertex);

    /* calculate running time of the functions */
    long long int ticks = stop - start;
    double total_time = (double)ticks / CLOCKS_PER_SEC;
    double duration = total_time / iterations;
    
    /* output the test result to file "test_result.txt" */
    FILE *test_result = fopen("test_result.txt", "a");
    fprintf(test_result, "%d, %e\n", G->vertex_number - 1, duration);
    return 0;
}
