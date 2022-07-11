#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PQ_T Pair
#define key(x) (x.first)
#define less(a, b) (key(a) > key(b))  // min-heap
#define swap(a, b)                                                                                                     \
    {                                                                                                                  \
        PQ_T t = a;                                                                                                    \
        a = b;                                                                                                         \
        b = t;                                                                                                         \
    }

typedef struct
{
    long long first;
    unsigned second;
} Pair;

typedef struct
{
    PQ_T *heap;
    size_t size, capacity;
} PriorityQueue;

void HEAP_fixup(PQ_T *heap, unsigned i)
{
    for (; i > 1 && less(heap[i / 2], heap[i]); i /= 2)
        swap(heap[i], heap[i / 2]);
}

void HEAP_fixdown(PQ_T *heap, size_t size, unsigned i)
{
    for (unsigned larger = i * 2; i * 2 <= size; i = larger, larger = i * 2)
    {
        if (larger < size && less(heap[larger], heap[larger + 1]))
            larger++;

        if (!less(heap[i], heap[larger]))
            break;

        swap(heap[i], heap[larger]);
    }
}

PriorityQueue PQ_init(size_t capacity)
{
    PriorityQueue pq = {.capacity = capacity, .size = 0};
    pq.heap = malloc((capacity + 1) * sizeof(PQ_T));
    return pq;
}

void PQ_free(PriorityQueue pq)
{
    free(pq.heap);
}

int PQ_isEmpty(PriorityQueue pq)
{
    return pq.size == 0;
}

void PQ_ensureCapacity(PriorityQueue *pq, size_t newCapacity)
{
    if (newCapacity <= pq->capacity)
        return;

    pq->capacity *= 4;
    pq->heap = realloc(pq->heap, (pq->capacity + 1) * sizeof(PQ_T));
}

void PQ_insert(PriorityQueue *pq, PQ_T x)
{
    PQ_ensureCapacity(pq, pq->size + 1);
    pq->heap[++pq->size] = x;
    HEAP_fixup(pq->heap, pq->size);
}

PQ_T PQ_getTop(PriorityQueue pq)
{
    PQ_T top;
    if (!PQ_isEmpty(pq))
        top = pq.heap[1];
    return top;
}

PQ_T PQ_extractTop(PriorityQueue *pq)
{
    PQ_T top = PQ_getTop(*pq);
    if (!PQ_isEmpty(*pq))
    {
        pq->heap[1] = pq->heap[pq->size--];
        HEAP_fixdown(pq->heap, pq->size, 1);
    }
    return top;
}

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

Pair *G_searchPath(Graph g, unsigned start, unsigned end)
{
    short *visited = calloc(g.V, sizeof(*visited));
    Pair *cameFrom = calloc(g.V, sizeof(*cameFrom));
    PriorityQueue pq = PQ_init(g.V);
    PQ_insert(&pq, (PQ_T){.first = 0, .second = start});
    while (!PQ_isEmpty(pq))
    {
        PQ_T top = PQ_extractTop(&pq);
        if (top.second == end)
            return cameFrom;

        for (unsigned i = 0; i < g.V; i++)
        {
            if (g.edges[top.second][i] != GRAPH_WEIGHT_INF && !visited[i])
            {
                PQ_insert(&pq, (PQ_T){.first = g.edges[top.second][i], .second = i});
                cameFrom[i] = (Pair){.first = g.edges[top.second][i], .second = top.second};
            }
        }

        visited[top.second] = 1;
    }

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
