#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int data;
	struct ll *left;
	struct ll *right;
}btree;
btree* newnode(int d){
	btree* c_node = (btree*)malloc(sizeof(btree));
	c_node->left = NULL;
	c_node->right = NULL;
	c_node->data = d;
	return c_node;
}
void preorder(btree* root){
	printf(" %d",root->data);
	if(root->left!=NULL)
		preorder(root->left);
	if(root->right!=NULL)
		preorder(root->right);
	return;
}
int post[210],cnt=0;
void postorder(btree* root){
	post[cnt++]=root->data;
	if(root->right!=NULL)
		postorder(root->right);
	if(root->left!=NULL)
		postorder(root->left);
	return;
}
int main(){
	int n,in;
	btree* rt;
	btree* now;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&in);
		if(i==0)
			rt = newnode(in);
		else{
			now = rt;
			while(1){
				if(now->data>=in){
					if(now->left == NULL){
						btree* nw = newnode(in);
						now->left = nw;
						break;
					}
					now = now->left;
					continue;
				}
				else{
					if(now->right == NULL){
						btree* nw = newnode(in);
						now->right = nw;
						break;
					}
					now = now->right;
					continue;
				}
			}
		}
	}
	printf("> Preorder:");
	preorder(rt);
	printf("\n> Postorder:");
	postorder(rt);
	for(int i=cnt-1;i>=0;i--)
		printf(" %d",post[i]);
	printf("\n");
}