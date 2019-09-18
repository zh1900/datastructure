/*
 * the function to get the best path
 *
 * @param struct graph *G,
 *        struct path *P,
 *        int *best_path_next_vertex,
 *        int starting_vertex,
 *        int sent,
 *        int back
 *
 * path P is the shortest path from strarting_vertex to all vertexs of graph G
 * if best_path_next_vertex[i] = -1, that means vertex i is an ending vertex on the path
 *
 * @return struct pair result
 */
struct pair getBestPath(
    struct graph *G,
    struct path *P,
    int *best_path_next_vertex,
    int starting_vertex,
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
        return makePair(cur_sent, cur_back);
    }

    struct pair result = makePair(INF, INF);

    list i;
    for (i = P->next_vertex[starting_vertex]->next; i != NULL ; i = i->next) {
        struct pair cur_result = getBestPath(G, P, best_path_next_vertex, i->data, cur_sent, cur_back);

        if (comparePair(cur_result, result)) {
            result = cur_result;
            best_path_next_vertex[starting_vertex] = i->data;
        }
    }

    return result;
}
