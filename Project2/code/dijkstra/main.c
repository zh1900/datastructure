#include <stdio.h>
#include <stdlib.h>

#define VERTEX_MAX 505
#define INF 1000000000

#include "define_structures.c"
#include "io.c"
#include "get_shortest_path.c"
#include "get_best_path.c"

int main(void)
{
    const int starting_vertex = 0;
    struct graph *G = (struct graph*)malloc(sizeof(struct graph));
    struct path *P = (struct path*)malloc(sizeof(struct path));
    int best_path_next_vertex[VERTEX_MAX];

    inputData(G);
    initPath(P, G->vertex_number);
    if (!getShortestPath(G, P, 0)) {
        puts("There is no shortest path!");
        return 0;
    }
    struct pair result = getBestPath(G, P, best_path_next_vertex, starting_vertex, 0, 0);
    outputSolution(result, best_path_next_vertex, starting_vertex);
    return 0;
}
