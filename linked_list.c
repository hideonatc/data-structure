#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int data;
	struct ll *next;
}ll;
ll* newNode(ll* now,int d){
	ll* newll = (ll*)malloc(sizeof(ll));
	now->next = newll;
	newll->data = d;
	newll->next = NULL;
	return newll;
}
ll* reverse(ll* hd){
	ll* prev = NULL;
    ll* current = hd->next;
    ll* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    ll* newhead = (ll*)malloc(sizeof(ll));
    newhead->next=prev;
	return newhead;
}
void travel(ll* hd){
	printf(">");
	ll* now;
	ll* ptr;
	now = hd;
	while(now->next != NULL){
		ptr = now->next;
		now=ptr;
		printf(" %d",now->data);
	}
	printf("\n");
	return;
}
int main(){
	int listLen = 0;
	ll *head;
	ll *now;
	head = (ll*)malloc(sizeof(ll));
	now = head;
	now->next = NULL;
	int n;
	while(scanf("%d",&n)!=EOF){
		listLen++;
		now = newNode(now,n);
	}
	ll *mid;
	mid = head;
	for(int i=1;i<(listLen+(listLen%2?1:2))/2;i++){
		mid = mid->next;
	}
	travel(mid);
	ll* rev = reverse(head);
	travel(rev);
}