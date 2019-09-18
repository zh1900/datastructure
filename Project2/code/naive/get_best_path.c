/*
 * the function to get the best path
 *
 * @param struct graph *G,
 *        bool *vis,
 *        int *best_path_next_vertex,
 *        int starting_vertex,
 *        int sent,
 *        int back
 *
 * if best_path_next_vertex[i] = -1, that means vertex i is an ending vertex on the path
 *
 * @return struct pair result
 */
struct three_int getBestPath(
    struct graph *G,
    bool *vis,
    int *best_path_next_vertex,
    int starting_vertex,
    int dis,
    int sent,
    int back
) {
    int cur_sent = sent;
    int cur_back = back + G->current_bike[starting_vertex] - G->maximum_capacity / 2;

    if (cur_back < 0) {
        cur_sent += -cur_back;
        cur_back = 0;
    }

    if (starting_vertex == G->problem_station) {
        best_path_next_vertex[starting_vertex] = -1;
        return makeThreeInt(dis, cur_sent, cur_back);
    }

    vis[starting_vertex] = true;

    struct three_int result = makeThreeInt(INF, INF, INF);

    int i;
    for (i = 0; i < G->vertex_number; i ++) {
        /*
         * check if the vertex i :
         *   is connected to starting_vertex
         *   is not the starting_vertex itself
         *   has not been visited
         */
        if (G->weight[i][starting_vertex] == INF ||
            i ==starting_vertex ||
            vis[i]
        ) {
            continue;
        }

        int cur_dis = G->weight[i][starting_vertex] + dis;
        struct three_int cur_result =
            getBestPath(G, vis, best_path_next_vertex, i, cur_dis, cur_sent, cur_back);

        if (compareThreeInt(cur_result, result)) {
            result = cur_result;
            best_path_next_vertex[starting_vertex] = i;
        }
    }

    vis[starting_vertex] = false;
    return result;
}

/*
 * initialize the array vis
 * set vis[i] = false (i = 0 to VERTEX_MAX - 1)
 */
void initVis(bool *vis)
{
    int i;
    for (i = 0; i < VERTEX_MAX - 1; i ++) {
        vis[i] = false;
    }
}