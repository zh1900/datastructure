void inputData(struct graph *G)
{
    int edge_num, i, j;
    scanf("%d%d%d%d",
          &G->maximum_capacity,
          &G->vertex_number,
          &G->problem_station,
          &edge_num
    );

    /* there are totally N + 1 vertexs (0 is the starting vertex and vertex 1 ~ N) */
    G->vertex_number += 1;

    /*
     * define the current number of bikes at
     * station 0 (starting vertex) as [G->maximum_capacity / 2]
     */
    G->current_bike[0] = G->maximum_capacity / 2;
    for (i = 1; i < G->vertex_number; i ++) {
        scanf("%d", &G->current_bike[i]);
    }

    /* define the weight between vertexs which are not connected as infinite (INF) */
    for (i = 0; i < G->vertex_number; i ++) {
        for (j = 0; j < G->vertex_number; j ++) {
            G->weight[i][j] = INF;
        }
    }

    for (i = 0; i < edge_num; i ++) {
        int vertex_1, vertex_2, edge_weight;
        scanf("%d%d%d", &vertex_1, &vertex_2, &edge_weight);
        G->weight[vertex_1][vertex_2] = edge_weight;
        G->weight[vertex_2][vertex_1] = edge_weight;
    }
}

void outputSolution(struct pair result, int *best_path_next_vertex, int starting_vertex)
{
    printf("%d %d", result.sent, starting_vertex);

    int i = best_path_next_vertex[starting_vertex];
    /*
     * if best_path_next_vertex[i] = -1,
     * that means vertex i is an ending vertex on the path
     */
    for (; i != -1; i = best_path_next_vertex[i]) {
        printf("->%d", i);
    }

    printf(" %d\n", result.back);
}
