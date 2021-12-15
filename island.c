#include<stdio.h>
#include<stdlib.h>
int mp[101][101],m,n;
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int legal(int x,int y,int d){
	if(x+dir[d][0]>=m||x+dir[d][0]<0||y+dir[d][1]>=n||y+dir[d][1]<0)
		return 0;
	return 1;
}
void go(int x,int y){
	mp[x][y]=0;
	for(int i=0;i<4;i++)
		if(legal(x,y,i)&&mp[x+dir[i][0]][y+dir[i][1]]==1)
			go(x+dir[i][0],y+dir[i][1]);
	return;
}
int travel(){
	int is=0;
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			if(mp[i][j]){
				go(i,j);
				is++;
			}
	return is;
}
int main(){
	scanf("%d %d",&m,&n);
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&mp[i][j]);
	printf("> %d",travel(m,n));
}