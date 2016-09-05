#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int unq_no;
	struct node * next;
}node;

typedef struct queue {
	node * front, * rear;
}queue;

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

int main()
{
	queue q;
	int ncase = 0;
	while(1) {
		int P, C, minP;
		q.front = NULL;
		q.rear = NULL;
		scanf("%d %d", &P, &C);
		if((P == 0) && (C == 0)) break;
		minP = (P < 1000) ? P : 1000;
		while(minP--) {
			if(q.rear == NULL){
				q.rear = malloc(sizeof(node));
				(q.rear)->unq_no = (minP+1);
				(q.rear)->next = NULL;
				q.front = q.rear;
			}
			else {
				node * tmp = malloc(sizeof(node));
				tmp->unq_no = (minP+1);
				tmp->next = q.front;
				q.front = tmp;
			}
		}
		char cmd[13];
		fprintf(stdout, "Case %d:\n", ++ncase);
		getc(stdin);
		while(C--){
			int unq_no;
			memset(cmd, 0, 13);
			fscanf(stdin, "%13[0-9A-Z ]s", cmd);
			getc(stdin);
			if(cmd[0] == 'N')
			{
				node *tmp1 = q.front, *tmp2 = q.rear;
				unq_no = (q.front)->unq_no;
				if((q.front)->next != NULL) {
					q.front = (q.front)->next;
					tmp1->next = NULL;
					tmp2->next = tmp1;
					q.rear = tmp1;
				}
				printf("%d\n", unq_no);
			}
			else
			{
				node *prev = NULL, *next = NULL, *tmp;
				unq_no = atoi(&cmd[2]);
				/*search and bring to front of q*/
				for(tmp = (q.front); tmp != NULL; tmp = tmp->next){
					next = tmp->next;
					if(tmp->unq_no == unq_no)
						break;
					prev = tmp;
				}
				if(tmp && (tmp != q.front)){
					prev->next = next;
					tmp->next = q.front;
					q.front = tmp;
					if(tmp == q.rear)
						q.rear = prev;
				}
				else {
					if(tmp == NULL){
						tmp = malloc(sizeof(node));
						tmp->unq_no = unq_no;
						tmp->next = q.front;
						q.front = tmp;
						if(q.rear == NULL)
							q.rear = tmp;
					}	
				}
			}
		}
		destroy_queue(&q);	
	}
    return 0;
}
