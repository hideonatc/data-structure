#include<stdio.h>
#include<stdlib.h>
typedef struct{
	int *item;
	int size;
	int head;
	int tail;
}queue;
queue* newQ(int sz){
	queue *ptr = (queue*)malloc(sizeof(queue));
    ptr->size = sz;
    ptr->head = 0;
    ptr->tail = 0;
    ptr->item = (int*)malloc(sizeof(int) * sz);
    return ptr;
}
void enqueue(queue* q,int n){
	q->item[q->tail++]=n;
	return; 
}
int gethead(queue* q){
	return q->item[q->head];
}
void dequeue(queue* q){
	q->head++;
	return;
}
int isempty(queue* q){
	if(q->head == q->tail)
		return 1;
	return 0;
}
int main(){
	queue* myQ = newQ(9999);
	int is;
	printf(">");
	while(scanf("%d",&is)!=-1){
		if(is==1){
			scanf("%d",&is);
			enqueue(myQ,is);
		}
		else if(is==2){
			if(isempty(myQ)){
				printf(" -2");
				continue;
			}
			printf(" %d",gethead(myQ));
		}
		else if(is==3){
			if(isempty(myQ)){
				printf(" -3");
				continue;
			}
			dequeue(myQ);
		}
	}
	printf("\n");
}