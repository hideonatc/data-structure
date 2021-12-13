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
char ctab[1001][1001];
char ktab[1001];
int tablen = 0;
int minweight = 0;
int comp(char ak,int af,int acom,char bk,int bf,int bcom){
	if(af>bf) return 1;
	if(af<bf) return 0;
	if(acom!=bcom) return acom;
	return ak>bk;
}
char com_name(char ak,int af,char bk,int bf){
	if(af>bf) return bk;
	if(af<bf) return ak;
	return ak>bk?ak:bk;
}
void insert(map* m,char c,int t,tree* rt,int cm){
	for(int i=0;i<m->size&&!cm;i++)
		if(m->key[i]==c){
			m->val[i]++;
			m->root[i]->fre++;
			while(i>0&&comp(m->key[i],m->val[i],m->com[i],m->key[i-1],m->val[i-1],m->com[i-1])){
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
		while(i>0&&comp(m->key[i],m->val[i],m->com[i],m->key[i-1],m->val[i-1],m->com[i-1])){
			int tmp=m->val[i];m->val[i]=m->val[i-1];m->val[i-1]=tmp;
			char tp=m->key[i];m->key[i]=m->key[i-1];m->key[i-1]=tp;
			tmp=m->com[i];m->com[i]=m->com[i-1];m->com[i-1]=tmp;
			tree* t=m->root[i];m->root[i]=m->root[i-1];m->root[i-1]=t;
			i--;
		}
		return;
}
void combine(map* m){
	char sc = com_name(m->key[m->size-1],m->val[m->size-1],m->key[m->size-2],m->val[m->size-2]);
	int tim = m->val[m->size-1]+m->val[m->size-2];
	tree* rt = newnode(sc,tim);
	rt->right = comp(m->key[m->size-1],m->val[m->size-1],m->com[m->size-1],m->key[m->size-2],m->val[m->size-2],m->com[m->size-1])?m->root[(m->size)-1]:m->root[(m->size)-2];
	rt->left = comp(m->key[m->size-1],m->val[m->size-1],m->com[m->size-1],m->key[m->size-2],m->val[m->size-2],m->com[m->size-1])?m->root[(m->size)-2]:m->root[(m->size)-1];
	m->size=m->size-2;
	insert(m,sc,tim,rt,1);
	printf("\n");
	for(int i=0;i<m->size;i++){
		printf("m[%d] key:%c val:%d com:%d\n",i,m->key[i],m->val[i],m->com[i]);
	}
	printf("\n");
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
		/*printf("key:%c fre:%d code:",r->ch,r->fre);
		for(int i=0;i<strlen(str);i++)
			printf("%c",str[i]);
		printf("\n");*/
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
	mymap->key = (char*)malloc(sizeof(char)*1001);
	mymap->val = (int*)malloc(sizeof(int)*1001);
	mymap->com = (int*)malloc(sizeof(int)*1001);
	mymap->root = (tree**)malloc(sizeof(tree*)*1001);
	mymap->size=0;
	char c;
	char sv[1001];
	int count = 0;
	while(scanf("%c",&c)!=EOF){
		//if(c=='\n')break;
		tree* root = newnode(c,1);
		sv[count++]=c;
		insert(mymap,c,1,root,0);
	}
	while(mymap->size>1){
		combine(mymap);
	}
	char sl[]="";
	char first=sv[0],second=sv[1],third=sv[2];
	travel(mymap->root[0],sl);
	sv[0]=first;sv[1]=second;sv[2]=third;
	printf("> ");
	for(int i=0;i<count;i++){
		for(int j=0;j<tablen;j++){
			if(ktab[j]==sv[i]){
				for(int k=0;k<strlen(ctab[j]);k++)
					printf("%c",ctab[j][k]);
			}
		}
		/*printf("(%c)",sv[i]);*/
	}
	printf("\n> %d\n",minweight);
	return 0;
}