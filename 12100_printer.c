#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    unsigned int initial_position:8;
    unsigned int priority:4;
    struct node * next;
}node;

typedef struct queue {
 node * front, * rear;
}queue;

bool isempty(queue q)
{
    if(q.front == NULL)
        return true;

    return false;
}

int get_high_pri(node *list)
{
    int max = -1;
    node * tmp = list;
    while(tmp){
        if(tmp->priority > max)
            max = tmp->priority;
        tmp = tmp->next;
    }
    return max;
}

void destroy_queue(queue *q)
{
    if(q == NULL) return;

    node *tmp = q->front;
    node *next;
    while(tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    q->front = NULL;
    q->rear = NULL;
}

void pop(queue *q)
{
    if(q == NULL) return;
    node *next_front;
    node * tmp = q->front;
    if(tmp) {
        next_front = tmp->next;
        free(tmp);
        q->front = next_front;
    }
}

void push(queue *q, int initial_position, int priority)
{
    node * q_front;
    if(q == NULL) return;
    q_front = q->front;
    node * tmp = (node *)calloc(1, sizeof(node));
    if(tmp == NULL) return;
    tmp->initial_position = initial_position;
    tmp->priority = priority;
    tmp->next = NULL;
    if(q_front == NULL){
        q->front = tmp;
        q->rear = tmp;
    }
    else {
        q->rear->next = tmp;
        q->rear = tmp;
    }
}

int main()
{
    queue q;
    q.front = NULL;
    q.rear = NULL;
    int num_tc;
    scanf("%d", &num_tc);
    while(num_tc--) {
        int i, n,m, time = 0;
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; ++i) {
            int pri;
            scanf("%d", &pri);
            push(&q, i, pri);
        }
        while(!isempty(q)) {
            int high_pri;
            node *top = q.front;
            high_pri = get_high_pri(q.front);
            if(top->priority == high_pri) {
                ++time;
                if(top->initial_position == m) {
                    printf("%d\n", time);
                    break;
                }
                else {
                    pop(&q);
                }
            }
            else {
                int init_pos = top->initial_position;
                int pri = top->priority;
                pop(&q);
                push(&q, init_pos, pri);
            }
        }
        destroy_queue(&q);
    }
    return 0;
}