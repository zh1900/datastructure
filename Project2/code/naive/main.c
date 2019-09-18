#include <stdio.h>
#include <stdlib.h>

#define VERTEX_MAX 505
#define INF 1000000000

#include "define_structures.c"
#include "io.c"
#include "get_best_path.c"

int main(void)
{
    const int starting_vertex = 0;
    struct graph *G = (struct graph*)malloc(sizeof(struct graph));
    int best_path_next_vertex[VERTEX_MAX];

    inputData(G);
    bool vis[VERTEX_MAX];
    initVis(vis);
    struct three_int result =
        getBestPath(G, vis, best_path_next_vertex, starting_vertex, 0, 0, 0);
    if (result.dis == INF) {
        puts("There is no shortest path!");
        return 0;
    }
    outputSolution(result, best_path_next_vertex, starting_vertex);
    return 0;
}
