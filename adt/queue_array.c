#define QUEUE_T int

typedef struct
{
    QUEUE_T *data;
    unsigned start, size, capacity;
} Queue;

Queue Q_init(unsigned capacity)
{
    Queue q = (Queue) {.capacity = capacity, .size = 0, .start = 0};
    q.data = malloc(capacity * sizeof(QUEUE_T));
    return q;
}

void Q_free(Queue q)
{
    free(q.data);
}

int Q_empty(Queue q)
{
    return q.size == 0;
}

int Q_full(Queue q)
{
    return q.size == q.capacity;
}

QUEUE_T Q_front(Queue q)
{
    return q.data[q.start];
}

QUEUE_T Q_back(Queue q)
{
    return q.data[(q.start + q.size - 1) % q.capacity];
}

void Q_push(Queue *q, QUEUE_T value)
{
    q->data[(q->start + q->size++) % q->capacity] = value;
}

QUEUE_T Q_pop(Queue *q)
{
    QUEUE_T front = Q_front(*q);
    q->start = (q->start + 1) % q->capacity;
    q->size--;
    return front;
}
