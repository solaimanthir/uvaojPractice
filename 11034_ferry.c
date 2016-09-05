#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    unsigned int clen;
    bool pos;
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

void push(queue *q, unsigned int len, bool pos)
{
    node * q_front;
    if(q == NULL) return;
    q_front = q->front;
    node * tmp = (node *)calloc(1, sizeof(node));
    if(tmp == NULL) return;
    tmp->clen = len;
    tmp->pos = pos;
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
    queue l_q;
    queue r_q;
    l_q.front = NULL;
    l_q.rear = NULL;
    r_q.front = NULL;
    r_q.rear = NULL;
    int num_tc;
    scanf("%d", &num_tc);
    while(num_tc--) {
        int i, flen,m, turns = 0;
        bool pos = 0;
        scanf("%d %d", &flen, &m);
        flen *= 100;
        for(i = 0; i < m; ++i) {
            unsigned int clen;
            char cpos[5];
            scanf("%d %s", &clen, cpos);
            if(cpos[0] == 'l')
                push(&l_q, clen, 0);
            else
                push(&r_q, clen, 1);
        }
        while(!isempty(l_q) || !isempty(r_q)) {
           if(pos == 0){
                int clsum = 0;
                while(!isempty(l_q)){
                    node * top = l_q.front;
                    if((clsum+top->clen) <= flen){
                        clsum = (clsum+top->clen);
                        pop(&l_q);
                    }
                    else
                        break;
                }
            }
            else{
                int clsum = 0;
                while(!isempty(r_q)){
                    node * top = r_q.front;
                    if((clsum+top->clen) <= flen){
                        clsum = (clsum+top->clen);
                        pop(&r_q);
                    }
                    else
                        break;
                }
            }
            pos ^= 1;
            ++turns;
        }
        printf("%d\n", turns);
        destroy_queue(&l_q);
        destroy_queue(&r_q);
    }
    return 0;
}