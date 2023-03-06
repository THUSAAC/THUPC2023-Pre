#include<bits/stdc++.h>
using namespace std;

const int MAXN=200200;
int w[MAXN];
struct Edge{
	int to;
	int nxt;
}edge[MAXN];
int frm[MAXN];
int cnt_e;
void insert_e(int u,int v){
	cnt_e++;
	edge[cnt_e].to=v;
	edge[cnt_e].nxt=frm[u];
	frm[u]=cnt_e;
}
bool cmp(int x,int y){return x>y;}

int n;
int siz[MAXN];
int val[MAXN];

void dfs(int x,int dep){
	siz[x]=1;
	for(int i=frm[x];i;i=edge[i].nxt){
		int v=edge[i].to;
		dfs(v,dep+1);
		siz[x]+=siz[v];
	}
	val[x]=(siz[x]-1)-dep-w[x];
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);
	}
	for(int i=2;i<=n;i++){
		int ff;
		scanf("%d",&ff);
		insert_e(ff,i);
	}
	dfs(1,0);
	sort(val+1,val+n+1,cmp);
	long long ans=0;
	for(int i=1;i<=n;i+=2){
		ans+=val[i]; 
	}
	printf("%lld\n",ans);
}
