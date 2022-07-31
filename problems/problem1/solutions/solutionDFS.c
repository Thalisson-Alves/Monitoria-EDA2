#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    long long first;
    unsigned second;
} Pair;

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
    unsigned vertex;
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
    // TODO - modify this to keep the linked list sorted by weight
    if (e.from > g->V || e.to > g->V)
        return;

    GraphNode *node = malloc(sizeof(GraphNode));
    *node = (GraphNode){.next = g->edges[e.from], .weight = e.weight, .vertex = e.to};
    g->edges[e.from] = node;
    g->E++;
}

int G_numberOfEdges(Graph g)
{
    return g.E;
}

int G_numberOfVertices(Graph g)
{
    return g.V;
}

void G_dfs(Graph g, unsigned start, unsigned *visited, Pair *cameFrom)
{
    visited[start] = 1;
    for (GraphNode *cur = g.edges[start]; cur; cur = cur->next)
    {
        if (!visited[cur->vertex])
        {
            cameFrom[cur->vertex] = (Pair){.first = cur->weight, .second = start};
            G_dfs(g, cur->vertex, visited, cameFrom);
        }
    }
}

Pair *G_searchPath(Graph g, unsigned start, unsigned end)
{
    short *visited = calloc(g.V, sizeof(*visited));
    Pair *cameFrom = calloc(g.V, sizeof(*cameFrom));

    G_dfs(g, start, visited, cameFrom);
    free(visited);

    return cameFrom;
}

void solve()
{
    int s, e, n, m;
    scanf(" %d %d %d %d", &s, &e, &n, &m);

    Graph g = G_init(n);
    for (int i = 0, v, w, p; i < m; i++)
    {
        scanf(" %d %d %d", &v, &w, &p);
        G_insert(&g, (Edge){.from = v, .to = w, .weight = p});
        G_insert(&g, (Edge){.from = w, .to = v, .weight = p});
    }

    Pair *cameFrom = G_searchPath(g, s, e);

    long long total = 0;
    unsigned *path = malloc(sizeof(*path) * g.V);
    for (int i = e; i != s; i = cameFrom[i].second)
        total += cameFrom[i].first, path[cameFrom[i].second] = i;

    free(cameFrom);

    printf("%lld\n", total);
    for (int i = s; i != e; i = path[i])
        printf("%d -> ", i);
    printf("%d\n", e);
}

int main()
{
    solve();

    return 0;
}
