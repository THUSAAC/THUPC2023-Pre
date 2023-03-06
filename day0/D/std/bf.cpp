#include<bits/stdc++.h>
//#pragma gcc optimize(3)
#define gc getchar()
//char buf[100000],*buff = buf + 100000;
//#define gc ((buff == buf + 100000 ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
#define pc putchar
//char bfu[10000000],*bfuu = bfu;
//#define pc(x) (*(bfuu++) = x)
#define li long long
#define uli unsigned li
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define md int mid = l + r >> 1
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
using namespace std;
//const int mo = 998244353;
//const int mo = 1000000007;
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
	sprintf(c,"%s.ans",s);
	freopen(c,"w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,f[400010];
li a[400010];
struct edge{
	int to,nxt;
}e[400010];
int cnt,fir[400010];
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

inline int bf_lca(int u,int v){
	int d1 = 0,d2 = 0,x;
	for(x = u;x;x = f[x]) ++d1;
	for(x = v;x;x = f[x]) ++d2;
	while(d1 > d2) u = f[u],--d1;
	while(d2 > d1) v = f[v],--d2;
	while(u != v) u = f[u],v = f[v];
	return u;
}
inline void bf_xg(int u,int x,int w){
	for(;u != x;u = f[u]) a[u] += w;
}
inline int bf_cx(int u,int x,int w){
	int as = 0;
	for(;u != x;u = f[u]) as += (a[u] >= w);
	return as;
}



inline void build(){
	
}
inline void rebuild(){
	
	build();	
}
inline int lca(int u,int v){
	return bf_lca(u,v); 
}
inline void xg(int u,int x,int w){
	bf_xg(u,x,w);
}
inline void xgnd(int x,int w){
	a[x] += w;
}
inline int cx(int u,int x,int w){
	return bf_cx(u,x,w);
}
inline int cxnd(int x,int w){
	return a[x] >= w;
}
int lstas;
int main(){
	srand(time(0));rd();
	//file("apple");
	int i,j,op,u,v,w,x;
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
			x = ++n;f[u] = x;f[x] = v;a[x] = w;
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
		if(i % 1000 == 0) rebuild();
	}
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}
