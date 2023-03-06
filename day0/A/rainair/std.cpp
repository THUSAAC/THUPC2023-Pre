#include <bits/stdc++.h>

#define fi first
#define se second
#define DB double
#define U unsigned
#define P std::pair
#define LL long long
#define LD long double
#define pb emplace_back
#define pf emplace_front
#define MP std::make_pair
#define SZ(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;
int n,a[MAXN],sz[MAXN],dep[MAXN];
std::vector<int> G[MAXN],vec;

void dfs(int v,int fa=0){
	dep[v] = dep[fa] + 1;
	sz[v] = 1;
	for(auto x:G[v]){
		if(x == fa) continue;
		dfs(x,v);
		sz[v] += sz[x];
	}
}

int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",a+i);
	FOR(i,2,n){
		int f;scanf("%d",&f);
		G[f].pb(i);G[i].pb(f);
	}
	dfs(1);
	FOR(i,1,n) vec.pb((sz[i]-1)-(dep[i]-1)-a[i]);
	std::sort(all(vec));std::reverse(all(vec));
	LL ans = 0;
	FOR(i,0,SZ(vec)-1){
		if(!(i&1)) ans += vec[i];
	}
	printf("%lld\n",ans);
	return 0;
}
