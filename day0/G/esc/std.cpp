#include<cstdio>
#include<algorithm>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io
{
	int F()
	{
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G()
	{
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
const int maxn = 200002;
const int treesize = 3800003;
const int N=7700004,M=22000000;
struct st{
	int no;
	st *lc, *rc;
}t[treesize],*root[maxn],*pt=t;
int now;
struct edge{
	int to;
	int next;
}e[N+M+2];
int pe=N+1;
void insert(int a,int to){
	e[pe]=(edge){to,e[a].next};
	e[a].next=pe++;
}
void addedge(int a,int to){
	insert(a,to);
	insert(to^1,a^1);
}
int dfc,pb;
int dfn[N],low[N],bl[N],s[N];
int ts;
int pl[maxn][5];
struct po{
	int l,r;
	int no;
}p[maxn];
int pp;
bool operator <(const po &x, const po &y){
	return x.r<y.r;
}
int pno;
st* insert(st* o, int l, int r, int p, int no){
	st* ret = pt++;
	*ret = (st){pno,o->lc,o->rc};
	pno+=2;
	if(l==r){
		addedge(ret->no,no);
		return ret;
	}
	int mid=l+r>>1;
	if(p<=mid){
		ret->lc=insert(o->lc,l,mid,p,no);
	}
	else{
		ret->rc=insert(o->rc,mid+1,r,p,no);
	}
	addedge(ret->no,ret->lc->no);
	addedge(ret->no,ret->rc->no);
	return ret;
}
void insert(st* o, int l, int r, int ll, int rr, int fr){
	if(o==t){
		return;
	}
	if(ll<=l&&rr>=r){
		addedge(fr,o->no);
		return;
	}
	int mid=l+r>>1;
	if(ll<=mid){
		insert(o->lc,l,mid,ll,rr,fr);
	}
	if(rr>mid){
		insert(o->rc,mid+1,r,ll,rr,fr);
	}
}
void dfs(int o){
	low[o]=dfn[o]=++dfc;
	s[++ts]=o;
	for(int p=e[o].next;p;p=e[p].next){
		if(!dfn[e[p].to]){
			dfs(e[p].to);
			cmin(low[o],low[e[p].to]);
		}
		else if(!bl[e[p].to]){
			cmin(low[o],dfn[e[p].to]);
		}
	}
	if(low[o]==dfn[o]){
		++pb;
		do{
			bl[s[ts]]=pb;
		}
		while(s[ts--]!=o);
	}
}
char ans[maxn];
int main()
{
	int n=io::F();
	for(int i=1;i<=4*n;++i){
		int a=io::F();
		pl[a][++pl[a][0]]=i;
	}
	for(int i=1;i<=n;++i){
		p[++pp]=(po){pl[i][1],pl[i][2],pno};
		p[++pp]=(po){pl[i][3],pl[i][4],pno};
		p[++pp]=(po){pl[i][1],pl[i][3],pno+1};
		p[++pp]=(po){pl[i][2],pl[i][4],pno+1};
		pno+=2;
	}
	std::sort(p+1,p+pp+1);
	*pt=(st){pno,t,t};
	pno+=2;
	root[0]=pt++;
	for(int i=1;i<=4*n;++i){
		insert(root[now],1,4*n,p[i].l,4*n,p[i].no);
		root[now+1]=insert(root[now],1,4*n,p[i].l,p[i].no^1);
		++now;
	}
	for(int i=0;i<pno;++i){
		if(!dfn[i]){
			dfs(i);
		}
	}
	for(int i=0;i<pno;i+=2){
		if(bl[i]==bl[i+1]){
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	for(int i=1;i<=4*n;++i){
		if(bl[p[i].no]<bl[p[i].no^1]){
			ans[p[i].l]='0';
			ans[p[i].r]='1';
		}
	}
	puts(ans+1);
	return 0;
}