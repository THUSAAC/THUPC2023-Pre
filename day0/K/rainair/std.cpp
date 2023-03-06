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

const int MAXN = 1e5 + 5;
std::set<int> S;
std::vector<int> vec[MAXN];

std::mt19937 g(time(0));
int main(){
	int n;scanf("%d",&n);
	FOR(i,1,n){
		int x;scanf("%d",&x);
		S.insert(i);
		vec[x].pb(i);
	}
	LL ans = 0;
	FOR(i,1,MAXN-1){
		if(S.empty()) break;
		ans += 1ll*S.size()*(*S.rbegin());
		for(auto x:vec[i]) S.erase(S.find(x));
	}
	printf("%lld\n",ans);
	return 0;
}
