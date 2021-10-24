#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
struct stack{
	float *it;
	int top;
	int mx;
};
struct stack* newStack(int cap){
    struct stack *ptr = (struct stack*)malloc(sizeof(struct stack));
    ptr->mx = cap;
    ptr->top = -1;
    ptr->it = (float*)malloc(sizeof(float) * cap);
    return ptr;
}
float cal(float a,char c,float b){
	if(c=='+')
		return a+b;
	if(c=='-')
		return a-b;
	if(c=='*')
		return a*b;
	return a/b;
}
int pre(char c){
	if(c=='+')return 11;
	if(c=='-')return 12;
	if(c=='*')return 13;
	return 14;
}
char pos(float n){
	n=(int)(n+0.5);
	if(n==11)return '+';
	if(n==12)return '-';
	if(n==13)return '*';
	return '/';
}
bool biggerorequal(char a,char b){
	if(a=='*'||a=='/')
		return 1;
	if((a=='+'||a=='-')&&(b=='+'||b=='-'))
		return 1;
	return 0;
}
bool isempty(struct stack *ptr){
	return ptr->top==-1;
}
bool isfull(struct stack *ptr){
	return ptr->top==ptr->mx-1;
}
void push(struct stack *ptr,float n){
	if(isfull(ptr))
		return;
	ptr->it[++ptr->top]=n;
	return;
}
void pop(struct stack *ptr){
	if(isempty(ptr))
		return;
	ptr->top--;
	return;
}
float gettop(struct stack* ptr){
	if(isempty(ptr))
		return ' ';
	return ptr->it[ptr->top];
}
int main(){
	struct stack *ep=newStack(10000);
	struct stack *cp=newStack(10000);
	char c;
	printf(">");
	while(scanf("%c",&c)!=EOF){
		if(c=='\n')break;
		if(isdigit(c)){
			push(cp,(int)(c-'0'));
			printf(" %c",c);
		}
		else if(c=='(')
			push(ep,10);
		else if(c==')'){
			while(gettop(ep)!=10){
				printf(" %c",pos(gettop(ep)));
				float i,j=gettop(cp);
				pop(cp);
				i=gettop(cp);
				pop(cp);
				push(cp,cal(i,pos(gettop(ep)),j));
				pop(ep);
			}
			pop(ep);
		}
		else{
			if(!isempty(ep)&&gettop(ep)>10&&biggerorequal(pos(gettop(ep)),c)){
				printf(" %c",pos(gettop(ep)));
				float i,j=gettop(cp);
				pop(cp);
				i=gettop(cp);
				pop(cp);
				push(cp,cal(i,pos(gettop(ep)),j));
				pop(ep);
			}
			push(ep,pre(c));
		}
	}
	while(!isempty(ep)){
		printf(" %c",pos(gettop(ep)));
		float i,j=gettop(cp);
		pop(cp);
		i=gettop(cp);
		pop(cp);
		push(cp,cal(i,pos(gettop(ep)),j));
		pop(ep);
	}
	printf("\n> %d\n",(int)(gettop(cp)+(gettop(cp)>=0?0.5:-0.5)));
}