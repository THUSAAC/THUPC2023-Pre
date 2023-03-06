#include<bits/stdc++.h>
using namespace std;

const int _ = 1 << 21 | 1 , P = 998244353 , G = 3;
int upd(int x){return x + (x >> 31 & P);}
int add(int x , int y){return upd(x + y - P);}
int sub(int x , int y){return upd(x - y);}
int poww(long long a , int b){int tms = 1; while(b){if(b & 1) tms = tms * a % P; a = a * a % P; b >>= 1;} return tms;}

#define vi vector < int >
int dir[_] , w[_] , need , invnd;
void init(int len){
	need = 1; while(need < len) need <<= 1;
	for(int i = 1 ; i < need ; ++i) dir[i] = (dir[i >> 1] >> 1) | (i & 1 ? need >> 1 : 0);
	static int L = 1; invnd = poww(need , P - 2);
	for(int &i = L ; i < need ; i <<= 1){
		w[i] = 1; int wn = poww(G , P / 2 / i);
		for(int j = 1 ; j < i ; ++j) w[i + j] = 1ll * w[i + j - 1] * wn % P;
	}
}

void dft(int *a , int t){
	for(int i = 1 ; i < need ; ++i) if(i < dir[i]) swap(a[i] , a[dir[i]]);
	for(int i = 1 ; i < need ; i <<= 1)
		for(int j = 0 ; j < need ; j += i << 1)
			for(int k = 0 ; k < i ; ++k){
				int x = a[j + k] , y = 1ll * a[i + j + k] * w[i + k] % P;
				a[j + k] = add(x , y); a[i + j + k] = sub(x , y);
			}
	if(t == -1){reverse(a + 1 , a + need); for(int i = 0 ; i < need ; ++i) a[i] = 1ll * a[i] * invnd % P;}
}

int lst[_] , prm[_] , mx[_] , cmx[_] , mxc[_] , cprm; bool nprm[_];
void sieve(){
	for(int i = 2 ; i < _ ; ++i){
		if(!nprm[i]){prm[++cprm] = i; lst[i] = i;}
		for(int j = 1 ; prm[j] * i < _ ; ++j){
			nprm[prm[j] * i] = 1; lst[prm[j] * i] = prm[j];
			if(i % prm[j] == 0) break;
		}
	}
}
#define pii pair < int , int >
vector<pii> fact(int t){
	if(t == 1) return {};
	int cur = lst[t] , cnt = 0; vector<pii> ans;
	while(t != 1){if(cur == lst[t]) ++cnt; else{ans.push_back(pii(cur,cnt)); cnt = 1; cur = lst[t];} t /= lst[t];}
	ans.push_back(pii(cur,cnt)); return ans;
}

int N , cnt[_] , val[_] , ans;

int main(){
	ios::sync_with_stdio(0); sieve();
	cin >> N; for(int i = 1 ; i <= N ; ++i){int A; cin >> A; ++cnt[A];}
	for(int i = 1 ; i < _ ; ++i)
		if(cnt[i]){
			vector<pii> fct = fact(i);
			for(auto t : fct){
				if(t.second > mx[t.first]){cmx[t.first] = mx[t.first]; mx[t.first] = t.second; mxc[t.first] = 0;}
				if(t.second == mx[t.first]) mxc[t.first] += cnt[i]; else cmx[t.first] = max(cmx[t.first] , t.second);
			}
		}
	for(int i = 1 ; i < _ ; ++i)
		if(cnt[i]){
			vector<pii> fct = fact(i); int val = 1;
			for(auto t: fct) if(t.second == mx[t.first] && mxc[t.first] == 1) val *= poww(t.first , mx[t.first] - cmx[t.first]);
			::val[i] = 1ll * cnt[i] * poww(val , P - 2) % P;
		}
	init(1 << 21); dft(val , 1); for(int i = 0 ; i < need ; ++i) val[i] = 1ll * val[i] * val[i] % P;
	dft(val , -1);
	for(int i = 1 ; i < _ ; ++i)
		if(cnt[i]){
			vector<pii> fct = fact(i); int val = 1;
			for(auto t: fct) if(t.second == mx[t.first] && mxc[t.first] == 1) val *= poww(t.first , mx[t.first] - cmx[t.first]);
			::val[2 * i] = (::val[2 * i] - 1ll * cnt[i] * poww(val , 2 * (P - 2)) % P + P) % P;
		}
	for(int i = 1 ; i < _ ; ++i)
		if(val[i]){
			vector<pii> fct = fact(i); int val = 1; for(auto t: fct) if(t.second > mx[t.first]) val *= poww(t.first , t.second - mx[t.first]);
			ans = (ans + 1ll * val * ::val[i]) % P;
		}
	for(int i = 1 ; i < _ ; ++i) if(mx[i]) ans = 1ll * ans * poww(i , mx[i]) % P;
	cout << ans * (P + 1ll) / 2 % P; return 0;
}
