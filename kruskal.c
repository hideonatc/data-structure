#include<stdio.h>
#include<stdlib.h>
int map[101][101];
int used[101][101];
int vis[101]={0};
int c=0;
void cycle(int x,int y,int n,int s){
	if(x!=-1&&s==y){
		c=1;
		return;
	}
	for(int i=0;i<n;i++){
		if(used[y][i]&&i!=x)
			cycle(y,i,n,s);
		if(c) return;
	}
	return;
}
int r=0,d=0;
void legal(int x,int n){
	//printf("legal(%d,%d,%d)\n",x,n,d);
	++d;
	vis[x]=1;
	if(d==n){
		r=1;
		return;
	}
	for(int i=0;i<n;i++){
		//printf("check %d,%d used=%d vis=%d\n",x,i,used[x][i],vis[i]);
		if(used[x][i]&&!vis[i])
			legal(i,n);
		if(r) return;
	}
	return;
}
int kruskal(int n){
	int len=0,time=n-1;
	while(time--){
		int min=1e9,a,b;
		for(int i=0;i<n;i++)
			for(int j=i;j<n;j++)
				if(!used[i][j]&&map[i][j]&&map[i][j]<min){
					used[i][j]=used[j][i]=1;
					c=0;
					cycle(-1,i,n,i);
					if(c){
						used[i][j]=used[j][i]=0;
						continue;
					}
					used[i][j]=used[j][i]=0;
					a=i;
					b=j;
					min=map[i][j];
				}
		len+=min;
		used[a][b]=used[b][a]=1;
		//printf("add %d,%d len=%d\n",a,b,len);
	}
	legal(0,n);
	if(r) return len;
	return -1;
}
int main(){
	int n,l;
	scanf("%d %d",&n,&l);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			map[i][j]=used[i][j]=0;
	int a,b,d;
	for(int i=0;i<l;i++){
		scanf("%d %d %d",&a,&b,&d);
		map[a][b]=map[b][a]=d;
	}
	int ans=kruskal(n);
	if(ans==-1)
		printf("> NO connected\n");
	else
		printf("> %d\n",ans);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(j>0) printf(" ");
			printf("%d",map[i][j]);
		}
		if(i!=n-1) printf("\n");
	}
	//printf("\n");
}
/*
9 14
0 1 4
0 7 8
1 7 11
1 2 8
7 6 1
7 8 7
2 8 2
8 6 6
6 5 2
2 5 4
2 3 7
3 5 14
3 4 9
5 4 10
*/