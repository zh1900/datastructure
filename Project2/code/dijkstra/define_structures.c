/* define boolean variable */
typedef char bool;

/* false = 0, true = 1 */
enum { false, true };

/* define pair */
struct pair { int sent, back; };

/*
 * the function to make pair
 * @param int s, int b
 * @return struct pair (sent = s, back = b)
 */
struct pair makePair(int s, int b)
{
    struct pair p;
    p.sent = s;
    p.back = b;
    return p;
}

/*
 * the function to compare two pairs
 *
 * @param struct pair a, struct pair b
 * @return bool a < b
 *
 * The rule of comparing two pairs :
 * 1. If there are more than one shortest path, the one that requires
 * the least number of bikes sent from PBMC will be chosen.
 *
 * 2. Note that if such a path is not unique, output the one that
 * requires minimum number of bikes that we must take back to PBMC.
 */
bool comparePair(struct pair a, struct pair b)
{
    return (bool)(a.sent == b.sent ? a.back < b.back : a.sent < b.sent);
}

/* define element of linked list */
struct node
{
    int data;
    struct node *next;
};

/* list is a pointer of struct node */
typedef struct node *list;

/*
 * the function to insert a integer into the list
 * @param list l, int D
 */
void insertIntoList(list L, int D)
{
    list new_node = (list)malloc(sizeof(struct node));
    new_node->data = D;
    new_node->next = L->next;
    L->next = new_node;
}

/*
 * the function to malloc and initialize a dummy head 
 * @return list dummy_head
 */
list makeDummyHead(void)
{
    list dummy_head = (list)malloc(sizeof(struct node));
    dummy_head->data = 0;
    dummy_head->next = NULL;
    return dummy_head;
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

/* define the path structure of this problem */
struct path
{
    int vertex_number;
    list next_vertex[VERTEX_MAX];
    /*
     * next_vertex[i] is a list
     * each element in it is next probable vertex of i on the shortest path
     */
};

/* the function to initialize a path structure */
void initPath(struct path *P, int vertex_number)
{
    int i;
    P->vertex_number = vertex_number;
    for (i = 0; i < P->vertex_number; i ++) {
        P->next_vertex[i] = makeDummyHead();
    }
}
