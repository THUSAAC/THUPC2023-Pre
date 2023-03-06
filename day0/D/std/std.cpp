#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
#define li long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pli pair<li,int>
using namespace std;
inline li read(){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9') y = c,c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
inline void file(char *s){
	char c[50];
	sprintf(c,"%s.in",s);
	freopen(c,"r",stdin);
	sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
const int N = 400010,M = 1000;
int n,m,f[N];
li a[N];
struct edge{
	int to,nxt;
}e[N];
int cnt,fir[N];
inline void ins(int u,int v){
	e[++cnt].to = v;e[cnt].nxt = fir[u];fir[u] = cnt;
	e[++cnt].to = u;e[cnt].nxt = fir[v];fir[v] = cnt;
}
void dfs(int x){
	for(int i = fir[x];i;i = e[i].nxt) if(e[i].to != f[x]){
		f[e[i].to] = x;
		dfs(e[i].to);
	}
}

int bel[N],vis[N],col,ff[N],dy[N],tot,ft1,ft2,dpt[N],sl[N],nd[N];
pli s[M << 1][10010],tp1[N],tp2[N];
li bj[N];
int st[N],ft;
inline void addnd(int x){
	if(bel[x]) return;
	bel[x] = x;nd[++tot] = x;dy[x] = tot;s[tot][sl[x] = 1] = mp(a[x],x);
}
inline void getdpt(int x){
	ft = 0;
	while(x && !dpt[x]) st[++ft] = x,x = ff[x];
	int y = dpt[x];
	while(ft) dpt[st[ft--]] = ++y;
}
inline void build(){
	memset(bel,0,sizeof(bel));memset(ff,0,sizeof(ff));memset(dy,0,sizeof(dy));
	memset(dpt,0,sizeof(dpt));memset(sl,0,sizeof(sl));memset(bj,0,sizeof(bj));
	tot = 0;
	int i,j,k,l,x,y;
	addnd(1);for(i = 1;i <= M && i <= n;++i) addnd(rd() % n + 1);
	++col;
	for(i = 1;i <= tot;++i){
		x = nd[i];
		for(y = x;y && vis[y] != col;y = f[y]) vis[y] = col;
		if(y) addnd(y);
	}
	for(i = 2;i <= tot;++i){
		x = nd[i];
		for(y = f[x];!bel[y];y = f[y]){
			bel[y] = x;
			s[i][++sl[x]] = mp(a[y],y);
		}
		ff[x] = y;	
		sort(s[i] + 1,s[i] + sl[x] + 1,[=](pli x,pli y){return x > y;});
	} 
	for(i = 1;i <= tot;++i) if(!dpt[nd[i]]) getdpt(nd[i]);
}
inline void rebuild(){
	for(int i = 1;i <= n;++i) a[i] += bj[bel[i]];
	build();	
}
inline bool chkfa(int u,int v){
	int x = bel[u],y = bel[v];
	if(dpt[x] < dpt[y]){
		for(v = ff[y];dpt[x] < dpt[v];v = ff[v]);
	}
	y = bel[v];
	if(x != y) return 0;
	while(u != v && bel[v] == y) v = f[v];
	return u == v;
}
inline int lca(int u,int v){
	++col;for(;!bel[u];u = f[u]) vis[u] = col;
	for(;!bel[v] && vis[v] != col;v = f[v]);
	if(vis[v] == col) return v;
	if(dpt[bel[u]] <= dpt[bel[v]] && chkfa(u,v)) return u;
	if(dpt[bel[v]] <= dpt[bel[u]] && chkfa(v,u)) return v;
	u = ff[bel[u]];v = ff[bel[v]];
	if(dpt[u] < dpt[v]) swap(u,v); 
	while(dpt[u] > dpt[v]) u = ff[u];
	while(u != v) u = ff[u],v = ff[v];
	return u;
}

inline void xgls(int u,int x,int w){
	if(u == x) return;
	++col;
	int i,j,k,v,y = bel[u],z = dy[y];
	for(v = u;v != x;v = f[v]) a[v] += w,vis[v] = col;
	ft1 = ft2 = 0;
	for(i = 1;i <= sl[y];++i){
		if(vis[s[z][i].se] == col) tp1[++ft1] = s[z][i];
		else tp2[++ft2] = s[z][i];
	}
	for(i = 1;i <= ft1;++i) tp1[i].fi += w;
	i = j = k = 1;
	while(i <= ft1 && j <= ft2){
		if(tp1[i] > tp2[j]) s[z][k++] = tp1[i++];
		else s[z][k++] = tp2[j++];
	}
	while(i <= ft1) s[z][k++] = tp1[i++];
	while(j <= ft2) s[z][k++] = tp2[j++];
}
inline void xgnd(int x,int w){
	a[x] += w;
	int y = bel[x],z = dy[y],i;
	if(!y) return;
	for(i = 1;i <= sl[y] && s[z][i].se != x;++i);
	assert(i <= sl[y]);
	s[z][i].fi += w;
	while(i > 1 && s[z][i] > s[z][i - 1]) swap(s[z][i],s[z][i - 1]),--i;
	while(i < sl[y] && s[z][i] < s[z][i + 1]) swap(s[z][i],s[z][i + 1]),++i;
}

inline void xg(int u,int x,int w){
	if(u == x) return;
	for(;u != x && !bel[u];u = f[u]) xgnd(u,w);
	if(u == x) return;
	if(bel[u] == bel[x]){
		xgls(u,x,w);return;
	}
	int v = u;
	for(;u != x && u != bel[u];u = f[u]);
	xgls(v,u,w);
	for(;bel[u] != bel[x];u = ff[u]) bj[u] += w;
	xgls(u,x,w);
}
inline int cxnd(int x,int w){
	return a[x] + bj[bel[x]] >= w;
}
inline int cxzk(int u,int w){
	int y = dy[u],l = 1,r = sl[u],as = 0,mid;
	while(l <= r){
		mid = l + r >> 1;
		if(s[y][mid].fi >= w - bj[u]) as = mid,l = mid + 1;
		else r = mid - 1;
	}
	return as;
}
inline int cx(int u,int x,int w){
	if(u == x) return 0;
	int as = 0;
	for(;u != x && !bel[u];u = f[u]) as += cxnd(u,w);
	if(u == x) return as;
	for(;u != x && u != bel[u];u = f[u]) as += cxnd(u,w);
	if(u == x) return as;
	for(;bel[u] != bel[x];u = ff[u]) as += cxzk(u,w);
	for(;u != x;u = f[u]) as += cxnd(u,w);
	return as;
}
int lstas;
int main(){
	srand(time(0));rd();
	//file("apple");
	int i,j,op,u,v,w,x,y,z;
	n = read();m = read();
	for(i = 1;i <= n;++i) a[i] = read();
	for(i = 1;i < n;++i) ins(read(),read());
	dfs(1);
	build();
	for(i = 1;i <= m;++i){
		op = read();u = read() ^ lstas;
		if(op != 2) v = read() ^ lstas;
		w = read() ^ lstas;
		if(op == 1){
			if(f[v] == u) swap(u,v);
			assert(f[u] == v);
			x = ++n;f[u] = x;f[x] = v;
			bel[x] = bel[u];a[x] = w - bj[bel[u]];
			if(bel[x]){
				y = bel[x];z = dy[y];s[z][++sl[y]] = mp(a[x],x);
				for(j = sl[y];j > 1 && s[z][j] > s[z][j - 1];--j) swap(s[z][j],s[z][j - 1]);
			}
		}
		else if(op == 2){
			x = ++n;f[x] = u;a[x] = w;
		}
		else if(op == 3){
			x = lca(u,v);
			xg(u,x,w);xg(v,x,w);xgnd(x,w);
		}
		else{
			x = lca(u,v);
			print(lstas = cx(u,x,w) + cx(v,x,w) + cxnd(x,w));pc('\n');
		}
		if(i % M == 0) rebuild();
	}
	//cerr<<clock()<<endl;
	return 0;
}
