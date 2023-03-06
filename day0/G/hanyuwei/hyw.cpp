//Love and Freedom.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<stack>
#include<cassert>
#define ll long long
#define inf 20021225
#define N 10000010
#define M 50010
using namespace std;
int read()
{
    int s=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')    f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9')    s=s*10+ch-'0',ch=getchar();
    return s*f;
}
struct edge{int to,lt;}e[N*3]; int in[N],cnt,rt[N];
void add(int x,int y){e[++cnt].to=y; e[cnt].lt=in[x]; in[x]=cnt;}
void addedge(int x,int y){add(x,y); add(y^1,x^1);}
stack<int> stk; int dfn[N],tms,low[N],col[N],c; bool ins[N];
void tarjan(int x)
{
	stk.push(x); dfn[x]=low[x]=++tms; ins[x]=1;
	for(int i=in[x];i;i=e[i].lt)
	{
		int y=e[i].to;
		if(ins[y])	low[x]=min(low[x],dfn[y]);
		else if(!dfn[y])	tarjan(y),low[x]=min(low[x],low[y]);
	}
	if(low[x]==dfn[x])
	{
		int w; ++c;
		do
		{
			w=stk.top(); stk.pop();
			col[w]=c; ins[w]=0;
		}while(w!=x);
	}
}
#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define mid (l+r>>1)
struct node{int id,son[2];}t[N];
int pos[M][4],cc[N],ans[M<<2];
struct seg{int l,r,id;}s[M<<2]; int scnt;
bool operator<(seg a,seg b){return a.r<b.r;}
int opp[N],n,m,tag[N],tot,poi;
int build(int l,int r)
{
	int x=++tot; t[x].id=++poi; ++poi;
	if(l==r)	return x;
	ls(x)=build(l,mid); rs(x)=build(mid+1,r);
	addedge(t[x].id,t[ls(x)].id);
	addedge(t[x].id,t[rs(x)].id);
	return x;
}
int insert(int y,int l,int r,int d,int id)
{
	int x=++tot; t[x]=t[y]; t[x].id=++poi; ++poi;
	if(l==r)	return addedge(t[x].id,id),x;
	if(d<=mid)	ls(x)=insert(ls(y),l,mid,d,id);
	else	rs(x)=insert(rs(y),mid+1,r,d,id);
	addedge(t[x].id,t[ls(x)].id);
	addedge(t[x].id,t[rs(x)].id);
	return x;
}
void modify(int x,int l,int r,int LL,int RR,int id)
{
	if(!x)	return;
	if(LL<=l&&RR>=r)	return addedge(id,t[x].id);
	if(LL<=mid)	modify(ls(x),l,mid,LL,RR,id);
	if(RR>mid)	modify(rs(x),mid+1,r,LL,RR,id);
}
bool check()
{
	for(int i=2;i<=poi;i++)
		if(!dfn[i])	tarjan(i);
	for(int i=2;i<=poi;i+=2)	if(col[i]==col[i^1])	return false;
	for(int i=2;i<=poi;i+=2)	opp[col[i]]=col[i^1],opp[col[i^1]]=col[i];
	for(int i=1;i<=c;i++)	if(!tag[i])	tag[i]=1,tag[opp[i]]=-1;
	return true;
}
int main()
{
	int n=read(); poi=(n<<1)+1;
	for(int i=1;i<=(n<<2);i++){int c=read(); pos[c][cc[c]++]=i;}
	for(int i=1;i<=n;i++)
	{
		s[++scnt]=(seg){pos[i][0],pos[i][1],i<<1};
		s[++scnt]=(seg){pos[i][2],pos[i][3],i<<1};
		s[++scnt]=(seg){pos[i][0],pos[i][2],i<<1|1};
		s[++scnt]=(seg){pos[i][1],pos[i][3],i<<1|1};
	}
	sort(s+1,s+scnt+1);
	rt[0]=build(1,n<<2); 
	for(int i=1;i<=scnt;i++)
	{
		modify(rt[i-1],1,n<<2,s[i].l,s[i].r,s[i].id);
		rt[i]=insert(rt[i-1],1,n<<2,s[i].l,s[i].id^1);
	}
	if(!check())	printf("No\n");
	else
	{
		printf("Yes\n");
		for(int i=1;i<=n;i++)
			if(tag[col[i<<1]]==1)	ans[pos[i][1]]=ans[pos[i][3]]=1;
			else	ans[pos[i][2]]=ans[pos[i][3]]=1;
		for(int i=1;i<=(n<<2);i++)	printf("%d",ans[i]);
	}
	return 0;
}
