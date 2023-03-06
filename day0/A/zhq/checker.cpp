#include<bits/stdc++.h>
using namespace std;

const int MAXN=200200;
int w[MAXN];
struct Edge{
	int to;
	int nxt;
}edge[MAXN*2];
int frm[MAXN];
int cnt_e;
void insert_e(int u,int v){
	cnt_e++;
	edge[cnt_e].to=v;
	edge[cnt_e].nxt=frm[u];
	frm[u]=cnt_e;
}

int n;
int mxh,vised;
void init(){
	memset(w,0,sizeof(w));
	cnt_e=0;mxh=vised=0;
	memset(frm,0,sizeof(frm));
}

void dfs(int x,int ff,int dep){
	vised++;
	mxh=max(mxh,dep);
	for(int i=frm[x];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==ff)continue;
		dfs(v,x,dep+1);
	}
}

void work(int T){
	init();
	string file_name_in=std::to_string(T)+".in";
	string file_name_out=std::to_string(T)+".ans";
	freopen(file_name_in.c_str(),"r",stdin);
	
	cout<<T<<":\n";
	scanf("%d",&n);
	int mxw=0;for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);
		assert(w[i]>=0&&w[i]<=200000); 
		mxw=max(mxw,w[i]);
	}
	printf("%d\n",mxw);
	for(int i=2;i<=n;i++){
		int ff;
		scanf("%d",&ff);
		insert_e(ff,i);
		assert(ff>=1&&ff<=n);
	}
	dfs(1,1,1);
	assert(vised==n);
	printf("%d %d\n",vised,mxh);
	fclose(stdin);
	freopen(file_name_out.c_str(),"r",stdin);
	long long anss;scanf("%lld",&anss);
	printf("%lld\n",anss);
	puts("");
}

int main(){
	freopen("ch_ck.out","w",stdout);
	for(int i=1;i<=23;i++){
		work(i);
	}
}
