#include<bits/stdc++.h>
using namespace std;

const int P = 998244353 , _ = 2e6 + 7; int prm[_] , lst[_] , cprm; bool nprm[_];
int poww(long long a , int b){int tms = 1; while(b){if(b & 1) tms = tms * a % P; a = a * a % P; b >>= 1;} return tms;}
int mx[_][2] , iv[_] , tms = 1 , ans , T , N;

#define pii pair < int , int >
#define fi first
#define se second
vector < pii > getprm(int val){
	vector < pii > pot;
	while(val != 1){int t = lst[val]; val /= t; if(pot.empty() || pot.back().fi != t) pot.push_back(pii(t , t)); else pot.back().se *= t;}
	return pot;
}

void sieve(){
	for(int i = 2 ; i <= 2e6 ; ++i){
		if(!nprm[i]){prm[++cprm] = i; lst[i] = i;}
		for(int j = 1 ; prm[j] * i <= 2e6 ; ++j){nprm[prm[j] * i] = 1; lst[prm[j] * i] = prm[j]; if(i % prm[j] == 0) break;}
	}
}

int calc(int x , int y){
	static bool flg[_] , vis[_]; static int pmx[_]; static vector < int > pot;
	vector < pii > p1 = getprm(x) , p2 = getprm(y) , p3 = getprm(x + y);
	for(auto t : p1){vis[t.fi] = 1; pot.push_back(t.fi); if(mx[t.fi][0] == t.se) flg[t.fi] = 1;}
	for(auto t : p2){vis[t.fi] = 1; pot.push_back(t.fi); if(mx[t.fi][0] == t.se) flg[t.fi] = 1;}
	for(auto t : p3){vis[t.fi] = 1; pot.push_back(t.fi); pmx[t.fi] = t.se;}
	int fin = tms; for(auto t : pot) if(vis[t]){int val = max(mx[t][flg[t]] , pmx[t]); fin = 1ll * fin * iv[t] % P * val % P; pmx[t] = vis[t] = flg[t] = 0;}
	pot.clear(); return fin;
}

int main(){
	ios::sync_with_stdio(0); sieve();
	cin >> N; map < int , int > cnt; for(int i = 1 ; i <= cprm ; ++i) mx[prm[i]][0] = mx[prm[i]][1] = 1;
	for(int i = 1 ; i <= N ; ++i){
		int x; cin >> x; ++cnt[x]; vector < pii > tmp = getprm(x);
		for(auto t : tmp) if(mx[t.fi][0] < t.se){mx[t.fi][1] = mx[t.fi][0]; mx[t.fi][0] = t.se;} else mx[t.fi][1] = max(mx[t.fi][1], t.se);
	}
	tms = 1; for(int i = 1 ; i <= cprm ; ++i){tms = 1ll * tms * mx[prm[i]][0] % P; iv[prm[i]] = poww(mx[prm[i]][0] , P - 2);}
	for(auto p = cnt.begin() ; p != cnt.end() ; ++p){
		if(p->se >= 2) ans = (ans + 1ll * p->se * (p->se - 1) / 2 % P * calc(p->fi , p->fi)) % P;
		for(auto q = p ; ++q != cnt.end() ; ) ans = (ans + 1ll * p->se * q->se % P * calc(p->fi , q->fi)) % P;
	}
	cout << ans << endl;
	return 0;
}
