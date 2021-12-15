#include<stdio.h>
#include<stdlib.h>
int map[27][27];
int prim(int n){
	int vis[27]={0},len=0,min,t;
	vis[0]=1;
	for(int i=0;i<n;i++){
		min=1e7;
		t=-1;
		for(int j=0;j<n;j++){
			if(vis[j]){
				for(int k=0;k<n;k++){
					//printf("%d %d %d\n",i,j,k);
					//printf("check %d vis=%d map[%d][%d]=%d\n",k,vis[k],j,k,map[j][k]);
					if(!vis[k]&&map[j][k]&&(map[j][k]<min||(map[j][k]==min&&j<t))){
						min=map[j][k];
						t=k;
						//printf("update min:%d at %d,%d\n",min,j,k);
					}
				}
			}
		}
		if(t==-1)continue;
		vis[t]=1;
		len+=min;
		//printf("add %d len=%d\n",t,len);
	}
	for(int i=0;i<n;i++)
		if(!vis[i]) return -1;
	return len;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&map[i][j]);
	int ans=prim(n);
	if(ans==-1)
		printf("> NO connected");
	else
		printf("> %d",ans);
}