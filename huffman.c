#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	char ch;
	int fre;
	struct ll *left;
	struct ll *right;
}tree;
typedef struct{
	char *key;
	int *val;
	int size;
	int *com;
	tree **root;
}map;
tree* newnode(char c,int d){
	tree* c_node = (tree*)malloc(sizeof(tree));
	c_node->left = NULL;
	c_node->right = NULL;
	c_node->ch = c;
	c_node->fre = d;
	return c_node;
}
void swapint(int *a,int *b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
	return;
}
void swapchar(char *a,char *b){
	char tmp=*a;
	*a=*b;
	*b=tmp;
	return;
}
void swaptree(tree *a,tree *b){
	tree tmp=*a;
	*a=*b;
	*b=tmp;
	return;
}
void insert(map* m,char c,int t,tree* rt,int cm){
	for(int i=0;i<m->size;i++)
		if(m->key[i]==c){
			m->val[i]++;
			while(i>=0&&((m->val[i]>m->val[i-1])||(m->val[i]==m->val[i-1]&&m->key[i]>m->key[i-1]))){
				swapint(m->val[i],m->val[i-1]);
				swapchar(m->key[i],m->key[i-1]);
				i--;
			}
			return;
		}
		m->key[m->size] = c;
		m->val[m->size] = t;
		m->com[m->size] = cm;
		m->root[++m->size] = rt;
		int i = m->size;
		while(i>=0&&((m->val[i]>m->val[i-1])||(m->val[i]==m->val[i-1]&&m->key[i]>m->key[i-1]))){
			swapint(m->val[i],m->val[i-1]);
			swapchar(m->key[i],m->key[i-1]);
			swapint(m->com[i],m->com[i-1]);
			swaptree(m->root[i],m->root[i-1]);
			i--;
		}
		return;
}
void combine(map* m){
	tree* rt = newnode(m->key[m->size-1],m->val[m->size-1]+m->val[m->size-2]);
	rt->right = m->root[m->size-2];
	rt->left = m->root[m->size-1];
	char sc = m->key[m->size-1];
	int tim = m->val[m->size-1]+m->val[m->size-2];
	m->size--;
	insert(m,sc,tim,rt,1);
	return;
}
void travel(tree* r,char* str){
	char *one="1";
	char *zero="0";
	if(r->right==NULL){
		printf("char:%c fre:%d encoded:%s\n",r->ch,r->fre,str);
		return;
	}
	char *cp = str;
	strcat(str,one);
	travel(r->right,str);
	str = cp;
	strcat(str,zero);
	travel(r->left,str);
	str = cp;
	return;
}
int main(){
	map* mymap = (map*)malloc(sizeof(map));
	mymap->size=0;
	char c;
	char str[100];
	int con = 0;
	while(scanf("%c",&str[con])!=EOF){
		tree* root = newnode(con,1);
		insert(mymap,str[con++],1,root,0);
	}
	while(mymap->size>1)
		combine(mymap);
	char *sl="";
	//tree *ft = mymap->root[0];
	travel(mymap->root[0],sl);
}