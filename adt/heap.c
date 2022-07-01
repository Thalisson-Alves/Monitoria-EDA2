#include <stdlib.h>

#define PQ_T unsigned
#define key(x) (x)
#define less(a, b) (key(a) < key(b))
#define swap(a, b)                                                                                                     \
    {                                                                                                                  \
        PQ_T t = a;                                                                                                    \
        a = b;                                                                                                         \
        b = t;                                                                                                         \
    }

typedef struct
{
    PQ_T *heap;
    size_t size, capacity;
} PriorityQueue;

void HEAP_fixup(PQ_T *heap, int i)
{
    for (; i > 1 && less(heap[i / 2], heap[i]); i /= 2)
        swap(heap[i], heap[i / 2]);
}

void HEAP_fixdown(PQ_T *heap, size_t size, int i)
{
    for (int larger = i * 2; i * 2 <= size; i = larger, larger = i * 2)
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
