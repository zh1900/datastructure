/*
 * the function to get shortest path by Dijkstra's algorithm
 *
 * @param struct graph *G, struct path *P, int starting_vertex
 * @return bool (if the shortest path exist)
 */
bool getShortestPath(struct graph *G, struct path *P, int starting_vertex)
{
    int i, j;
    int *dis = (int*)malloc(sizeof(int) * G->vertex_number);
    /* dis[i] = the shortest distance between starting vertex (vertex 0) and vertex i */
    bool *vis = (bool*)malloc(sizeof(bool) * G->vertex_number);
    /* vis[i] = weather vertex i has been visited */

    /* define dis[starting_vertex] = 0 and dis[i] at first */
    dis[starting_vertex] = 0;
    for (i = 1; i < G->vertex_number; i ++) {
        dis[i] = INF;
    }

    /* set vis[i] = false (all vertexs have not been visited) */
    for (i = 0; i < G->vertex_number; i ++) {
        vis[i] = 0;
    }

    /* Dijkstra's algorithm */
    while (true) {
        /*
         * find the vertex which has the minimun distance
         * to starting_vertex and has not been visited
         */
        int min_v = -1;
        for (j = 0; j < G->vertex_number; j ++) {
            if (!vis[j] && (min_v == -1 || dis[j] < dis[min_v])) {
                min_v = j;
            }
        }
        /* if the vertex could not be found (all vertexs are visited) */
        if (min_v == -1) {
            break;
        }

        /* set status of vertex min_v as visited */
        vis[min_v] = true;

        /* update distance between all vertexs and starting vertex */
        for (j = 0; j < G->vertex_number; j ++) {
            if (dis[min_v] + G->weight[min_v][j] < dis[j]) {
                dis[j] = dis[min_v] + G->weight[min_v][j];
            }
        }
    }
    
    /* if there is no shortest path */
    if (dis[G->problem_station] == INF) {
        return false;
    }

    /* put the shortest path into the struct path P */
    for (i = 0; i < G->vertex_number; i ++) {
        for (j = 0; j < G->vertex_number; j ++) {
            if (dis[i] + G->weight[i][j] == dis[j]) {
                insertIntoList(P->next_vertex[i], j);
            }
        }
    }
    return true;
}
