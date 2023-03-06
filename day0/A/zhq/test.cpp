#include<algorithm>
#include<iostream> 
#include<cstring>
#include<cstdio>
using std::sort;

const int MAXN=400400;
int n;
int w[MAXN];

struct Edge{
	int to;
	int nxt;
}edge[MAXN];
int frm[MAXN];
int cnt_e;
int siz[MAXN];
int V[MAXN];

void insert_e(int u,int v){
	cnt_e++;
	edge[cnt_e].to=v;
	edge[cnt_e].nxt=frm[u];
	frm[u]=cnt_e;
}

void dfs(int x,int ff,int dep){ 
	siz[x]=1;
	for(int i=frm[x];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==ff)continue;
		dfs(v,x,dep+1);
		siz[x]+=siz[v];
	}
	V[x]=(siz[x]-1)-dep-w[x];
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);
	}
	for(int i=2;i<=n;i++){
		int fa;scanf("%d",&fa);
		insert_e(fa,i);
		insert_e(i,fa); 
	}
	dfs(1,1,0);
	sort(V+1,V+n+1);
	long long ans=0;
	for(int i=n;i>=1;i-=2)ans+=V[i];
	printf("%lld\n",ans);
}
