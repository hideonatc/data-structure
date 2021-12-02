#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	char ch;
	int fre;
	struct tree *left;
	struct tree *right;
}tree;
typedef struct{
	char *key;
	int *val;
	int size;
	int *com;
	tree **root;
}map;
struct tree* newnode(char c,int d){
	tree* c_node = (tree*)malloc(sizeof(tree));
	c_node->left = NULL;
	c_node->right = NULL;
	c_node->ch = c;
	c_node->fre = d;
	return c_node;
}
char ctab[9999][9999];
char ktab[9999];
int tablen = 0;
int minweight = 0;
void insert(map* m,char c,int t,tree* rt,int cm){
	for(int i=0;i<m->size&&!cm;i++)
		if(m->key[i]==c){
			m->val[i]++;
			m->root[i]->fre++;
			while(i>0&&((m->val[i]>m->val[i-1])||(m->val[i]==m->val[i-1]&&m->key[i]>m->key[i-1]))){
				int tmp=m->val[i];m->val[i]=m->val[i-1];m->val[i-1]=tmp;
				char tp=m->key[i];m->key[i]=m->key[i-1];m->key[i-1]=tp;
				tree* t=m->root[i];m->root[i]=m->root[i-1];m->root[i-1]=t;
				i--;
			}
			return;
		}
		m->key[m->size] = c;
		m->val[m->size] = t;
		m->com[m->size] = cm;
		m->root[m->size++] = rt;
		int i = m->size-1;
		while(i>0&&((m->val[i]>m->val[i-1])||(m->val[i]==m->val[i-1]&&m->key[i]>m->key[i-1]))){
			int tmp=m->val[i];m->val[i]=m->val[i-1];m->val[i-1]=tmp;
			char tp=m->key[i];m->key[i]=m->key[i-1];m->key[i-1]=tp;
			tmp=m->com[i];m->com[i]=m->com[i-1];m->com[i-1]=tmp;
			tree* t=m->root[i];m->root[i]=m->root[i-1];m->root[i-1]=t;
			i--;
		}
		return;
}
void combine(map* m){
	char sc = m->key[m->size-1];
	int tim = m->val[m->size-1]+m->val[m->size-2];
	tree* rt = newnode(sc,tim);
	rt->right = m->root[(m->size)-2];
	rt->left = m->root[(m->size)-1];
	m->size=m->size-2;
	insert(m,sc,tim,rt,1);
	return;
}
void travel(tree* r,char* str){
	char one[]="1";
	char zero[]="0";
	if(r->right==NULL){
		ktab[tablen]=r->ch;
		for(int i=0;i<strlen(str);i++)
			ctab[tablen][i]=str[i];
		tablen++;
		minweight+=r->fre*strlen(str);
		return;
	}
	strcat(str,one);
	travel(r->right,str);
	str[strlen(str)-1] = '\0';
	if(r->left==NULL)
		return;
	strcat(str,zero);
	travel(r->left,str);
	str[strlen(str)-1] = '\0';
	return;
}
int main(){
	map* mymap = (map*)malloc(sizeof(map));
	mymap->key = (char*)malloc(sizeof(char)*10000);
	mymap->val = (int*)malloc(sizeof(int)*10000);
	mymap->com = (int*)malloc(sizeof(int)*10000);
	mymap->root = (tree**)malloc(sizeof(tree*)*10000);
	mymap->size=0;
	char c;
	char sv[10000];
	int count = 0;
	while(scanf("%c",&c)!=EOF){
		if(c=='\n')break;
		tree* root = newnode(c,1);
		sv[count++]=c;
		insert(mymap,c,1,root,0);
	}
	/*if(mymap->val[0]==count){
		printf("> ");
		for(int i=0;i<count;i++)
			printf("0");
		printf("\n> %d\n",count);
		return 0;
	}*/
	while(mymap->size>1){
		combine(mymap);
	}
	char sl[]="";
	char first=sv[0],second=sv[1];
	travel(mymap->root[0],sl);
	sv[0]=first;sv[1]=second;
	printf("> ");
	for(int i=0;i<count;i++){
		for(int j=0;j<tablen;j++){
			if(ktab[j]==sv[i]){
				for(int k=0;k<strlen(ctab[j]);k++)
					printf("%c",ctab[j][k]);
			}
		}
	}
	printf("\n> %d\n",minweight);
	return 0;
}