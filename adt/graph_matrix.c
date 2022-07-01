#include <stdlib.h>

#define GRAPH_WEIGHT_T int
#define GRAPH_WEIGHT_SUM(a, b) (a + b)
#define GRAPH_WEIGHT_LESS(a, b) (a < b)
#define GRAPH_WEIGHT_INF 2147483647

typedef struct
{
    unsigned from, to;
    GRAPH_WEIGHT_T weight;
} Edge;

typedef struct
{
    GRAPH_WEIGHT_T **edges;
    unsigned V, E;
} Graph;

Graph G_init(unsigned numberOfVertices)
{
    Graph g = {.V = numberOfVertices, .E = 0};
    g.edges = malloc(sizeof(GRAPH_WEIGHT_T *) * g.V);
    for (unsigned i = 0; i < g.V; i++)
    {
        g.edges[i] = malloc(sizeof(GRAPH_WEIGHT_T) * g.V);
        for (unsigned j = 0; j < g.V; j++)
            g.edges[i][j] = GRAPH_WEIGHT_INF;
    }
    return g;
}

void G_free(Graph g)
{
    for (unsigned i = 0; i < g.V; i++)
        free(g.edges[i]);
    free(g.edges);
}

void G_insert(Graph *g, Edge e)
{
    if (e.from > g->V || e.to > g->V)
        return;

    g->E += (g->edges[e.from][e.to] == GRAPH_WEIGHT_INF);
    g->edges[e.from][e.to] = e.weight;
}

int G_numberOfEdges(Graph g)
{
    return g.E;
}

int G_numberOfVertices(Graph g)
{
    return g.V;
}

void G_components(Graph g, int start, int components[][])
{
    if (components[start] < 0)
        components[start] = start;
    for (unsigned i = 0; i < g.V; i++)
        if (g.edges[start][i] != GRAPH_WEIGHT_INF && components[i] < 0)
        {
            unsigned mn = (i < components[start] ? i : components[start]);
            components[start] = mn;
            components[i] = mn;
            G_components(g, i, components);
        }
}

void G_transitiveClosure(Graph g, int transitive[][2001])
{
    for (unsigned i = 0; i < g.V; i++)
    {
        for (unsigned j = 0; j < g.V; j++)
            transitive[i][j] = g.edges[i][j] != GRAPH_WEIGHT_INF;
        transitive[i][i] = 1;
    }

    for (unsigned i = 0; i < g.V; i++)
        for (unsigned j = 0; j < g.V; j++)
            if (transitive[j][i] == 1)
                for (unsigned k = 0; k < g.V; k++)
                    if (transitive[i][k] == 1)
                        transitive[j][k] = 1;
}

short G_bestPathBF(Graph g, int start, int *cameFrom, GRAPH_WEIGHT_T *dist)
{
    short *onQueue = malloc(sizeof(short) * g.V);
    for (int i = 0; i < g.V; i++)
        cameFrom[i] = -1, dist[i] = GRAPH_WEIGHT_INF, onQueue[i] = 0;
    cameFrom[start] = start;
    dist[start] = 0;

    Queue q = Q_init();
    Q_push(&q, start);
    onQueue[start] = 1;

    const int sentinel = g.V;
    int k = 0;
    Q_push(&q, sentinel);

    while (!Q_empty(q))
    {
        int v = Q_pop(&q);
        if (v < sentinel)
        {
            for (int i = 0; i < g.V; i++)
            {
                if (g.edges[v][i] == GRAPH_WEIGHT_INF)
                    continue;

                if (GRAPH_WEIGHT_LESS(GRAPH_WEIGHT_SUM(dist[i], g.edges[v][i].weight), dist[i]))
                {
                    dist[i] = GRAPH_WEIGHT_SUM(dist[i], g.edges[v][i].weight);
                    cameFrom[i] = v;
                    if (!onQueue[i])
                    {
                        Q_push(&q, i);
                        onQueue[i] = 1;
                    }
                }
            }
        }
        else
        {
            if (Q_empty(q))
                return 1;
            if (++k >= g.V)
                return 0;
            Q_push(&q, v);
            for (int i = 0; i < g.V; i++)
                onQueue[i] = 0;
        }
    }

    free(onQueue);
}

GRAPH_WEIGHT_T G_dijkstra(Graph g, unsigned start, unsigned end)
{
    short *visited = calloc(g.V, sizeof(*visited));
    PriorityQueue pq = PQ_init(16384);
    PQ_insert(&pq, (PQ_T){.first = 0, .second = start});
    while (!PQ_isEmpty(pq))
    {
        PQ_T top = PQ_extractTop(&pq);
        if (top.second == end)
            return top.first;

        for (unsigned i = 0; i < g.V; i++)
        {
            if (g.edges[top.second][i] != GRAPH_WEIGHT_INF && !visited[i])
                PQ_insert(&pq, (PQ_T){.first = top.first + g.edges[top.second][i], .second = i});
        }

        visited[top.second] = 1;
    }

    return GRAPH_WEIGHT_INF;
}
