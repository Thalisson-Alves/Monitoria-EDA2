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

typedef struct G_N
{
    GRAPH_WEIGHT_T weight;
    unsigned vertice;
    struct G_N *next;
} GraphNode;

typedef struct
{
    GraphNode **edges;
    unsigned V, E;
} Graph;

Graph G_init(unsigned vertices)
{
    Graph g = {.V = vertices, .E = 0};
    g.edges = malloc(sizeof(GraphNode *) * g.V);
    for (unsigned i = 0; i < g.V; i++)
        g.edges[i] = NULL;
    return g;
}

void G_free(Graph g)
{
    for (unsigned i = 0; i < g.V; i++)
    {
        GraphNode *cur = g.edges[i];
        while (cur)
        {
            GraphNode *toRemove = cur;
            cur = cur->next;
            free(toRemove);
        }
    }
}

void G_insert(Graph *g, Edge e)
{
    if (e.from > g->V || e.to > g->V)
        return;

    GraphNode *node = malloc(sizeof(GraphNode));
    *node = (GraphNode){.next = g->edges[e.from], .weight = e.weight, .vertice = e.to};
    g->edges[e.from] = node;
    g->E++;
}

void G_components(Graph g, int start, int components[])
{
    if (components[start] < 0)
        components[start] = start;
    for (GraphNode *cur = g.edges[start]; cur; cur = cur->next)
        if (components[cur->vertice] < 0)
        {
            unsigned mn = (cur->vertice < components[start] ? cur->vertice : components[start]);
            components[start] = mn;
            components[cur->vertice] = mn;
            G_components(g, cur->vertice, components);
        }
}

void G_transitiveClosure(Graph g, int **transitive)
{
    for (unsigned i = 0; i < g.V; i++)
    {
        for (GraphNode *cur = g.edges[i]; cur; cur = cur->next)
            transitive[i][cur->vertice] = 1;
        transitive[i][i] = 1;
    }

    for (unsigned i = 0; i < g.V; i++)
        for (unsigned j = 0; j < g.V; j++)
            if (g.edges[j][i] != GRAPH_WEIGHT_INF)
                for (unsigned k = 0; k < g.V; k++)
                    if (g.edges[i][k] != GRAPH_WEIGHT_INF)
                        transitive[j][k] = 1;
}
