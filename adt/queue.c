#include <stdio.h>
#include <stdlib.h>

#define QUEUE_T int

typedef struct Q_I
{
    QUEUE_T val;
    struct Q_I *next;
} QueueItem;

typedef struct
{
    size_t size;
    QueueItem *head;
    QueueItem *tail;
} Queue;

Queue Q_init()
{
    return (Queue){.head = NULL, .tail = NULL, .size = 0};
}

void Q_clear(Queue *q)
{
    while (!Q_empty(*q))
        Q_pop(q);
}

QUEUE_T Q_front(Queue q)
{
    QUEUE_T front;
    if (!Q_empty(q))
        front = q.head->val;
    return front;
}

QUEUE_T Q_back(Queue q)
{
    QUEUE_T back;
    if (!Q_empty(q))
        back = q.tail->val;
    return back;
}

void Q_push(Queue *q, QUEUE_T value)
{
    QueueItem *qi = malloc(sizeof(QueueItem));
    qi->val = value;
    qi->next = NULL;

    if (Q_empty(*q))
    {
        q->head = qi;
        q->tail = qi;
    }
    else
    {
        q->tail->next = qi;
        q->tail = qi;
    }
    q->size++;
}

QUEUE_T Q_pop(Queue *q)
{
    QUEUE_T value = Q_front(*q);
    if (!Q_empty(*q))
    {
        QueueItem *toRemove = q->head;
        q->head = toRemove->next;
        if (!q->head)
            q->tail = NULL;
        free(toRemove);
        q->size--;
    }
    return value;
}

int Q_empty(Queue q)
{
    return q.size == 0;
}
