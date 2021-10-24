#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
typedef struct{
	int row;
	int col;
	int val;
}mx;
int str_to_int(char *c){
	int rt=0,idx=0;
	bool m=0;
	if(c[idx]=='-'){
		m=1;
		idx++;
	}
	while(idx<strlen(c))
		rt=rt*10+((int)(c[idx++]-'0'));
	if(m)
		rt=-1*rt;
	return rt;
}
void transpose(mx a[], mx b[],int cl,int v){
    int idx = 0;
    for (int i = 0; i < cl; i++) {
        for (int j = 0; j < v; j++) {
            if (a[j].col == i)	{
                b[idx].row = a[j].col;
                b[idx].col = a[j].row;
                b[idx].val = a[j].val;
                idx++;
            }
        }
    }
    return;
}
int main(){
	int r,c,total_cnt=0;
	mx dm[10001];
	scanf("%d %d\n",&r,&c);
	char str[10000];
	int r_cnt=0,c_cnt=0;
	while(scanf("%[^\n]%*c",str)!=EOF){
		r_cnt++;
		if(r_cnt>r)
			break;
		char *ptr = strtok(str, " ");
		c_cnt=0;
		while(ptr != NULL){
			c_cnt++;
			int p=str_to_int(ptr);
			if(p!=0){
				dm[total_cnt].row=r_cnt-1;
				dm[total_cnt].col=c_cnt-1;
				dm[total_cnt++].val=p;
			}
			ptr = strtok(NULL, " ");
		}
		if(c_cnt!=c)
			break;
	}
	if(r_cnt!=r||c_cnt!=c){
		printf("Input matrix has wrong size. Please input again.\n");
	}
	else{
		printf("Sparse matrix by triplet form:\n");
		printf("%d %d %d\n",r,c,total_cnt);
		for(int i=0;i<total_cnt;i++)
			printf("%d %d %d\n",dm[i].row,dm[i].col,dm[i].val);
		mx new_dm[10001];
		transpose(dm,new_dm,c,total_cnt);
		printf("Transpose of the sparse matrix:\n");
		printf("%d %d %d\n",c,r,total_cnt);
		for(int i=0;i<total_cnt;i++){
			printf("%d %d %d\n",new_dm[i].row,new_dm[i].col,new_dm[i].val);
		}
	}
}