#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

const int NMX = 5e5 , VMX = 1e6; int N , val[NMX + 3] , file_id = 1; mt19937 rnd(11233);
int rndv(){return rnd() % VMX + 1;}

void output(){
	ofstream out(to_string(file_id) + ".in"); shuffle(val + 1 , val + N + 1 , rnd);
	out << N << '\n'; for(int i = 1 ; i <= N ; ++i){out << val[i]; if(i != N) out << ' ';}
	out.close();
	system(("std.exe < " + to_string(file_id) + ".in > " + to_string(file_id) + ".ans").c_str());
	++file_id;
}

void dominate(int size){
	N = 5e5; vector < int > V; for(int i = 0 ; i < size; ++i) V.push_back(rndv());
	for(int i = 1 ; i <= N ; ++i) if(rnd() % 100) val[i] = V[rnd() % size]; else val[i] = rndv();
	output();
}

void random(int LMX){
	N = LMX - rnd() % (LMX / 10); for(int i = 1 ; i <= N ; ++i) val[i] = rndv();
	output();
}

const int _ = 1e6 + 7;
int lst[_] , prm[_] , mx[_] , type[_] , cnt[_] , cprm; bool nprm[_] , vis[_];
void sieve(){
	for(int i = 2 ; i <= VMX ; ++i){
		if(!nprm[i]){prm[++cprm] = i; lst[i] = i;}
		for(int j = 1 ; prm[j] * i <= VMX ; ++j){
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

long long poww(long long a , int b){long long tms = 1; for(int i = 1 ; i <= b ; ++i) tms *= a; return tms;}
void strong1(int LMX , int valLim = VMX){
	/*
	  Main idea:
	  Limit the maximum power of some small primes
	  Limit the number of maximum power of many primes to be 1
	  Need to ensure that
	  1. deleting many numbers would decrease LCM
	  2. adding many numbers would increase LCM
	  3. deleting two maximum power would result in larger power
	 */
	/*
	  Type
	  0: arbitrary
	  1: exactly 1 max
	  2: exactly 2 max
	 */
	memset(vis , 0 , sizeof(vis)); N = 0;
	for(int i = 1 ; i <= cprm ; ++i){
		int mxpw = 1 , cur = prm[i]; while(1ll * cur * prm[i] <= VMX){++mxpw; cur *= prm[i];}
		if(prm[i] <= valLim){type[prm[i]] = rnd() % 3; mx[prm[i]] = type[prm[i]] == 0 ? rnd() % (mxpw + 1) : rnd() % mxpw + 1;}
		else{type[prm[i]] = 0; mx[prm[i]] = mxpw;}
		//cerr << prm[i] << ' ' << type[prm[i]] << ' ' << mx[prm[i]] << endl;
	}
	auto dectype = [&](int x){if(!--type[x]) --mx[x];};
	for(int i = cprm ; i ; --i)
		while(type[prm[i]]){
			int pw = poww(prm[i] , mx[prm[i]]) , T = (rnd() % (VMX / pw) + 1) * pw;
			vector < pii > tmp = fact(T); bool flg = 1; for(auto t : tmp) flg &= mx[t.first] >= t.second;
			int cnt = 0; if(flg){val[++N] = T; for(auto t : tmp) if(type[t.first] && mx[t.first] == t.second){dectype(t.first); ++cnt;}}
			if(cnt >= 2) cerr << "Wow!" << ' ' << file_id << endl;
		}
	int totN = max(N , (int)(LMX - rnd() % (LMX / 10)));
	for(int i = 1 ; i <= cprm ; ++i){long long t = poww(prm[i] , mx[prm[i]] + 1); for(long long j = t ; j <= VMX ; j += t) vis[j] = 1;}
	vector < int > pot; for(int i = 1 ; i <= VMX ; ++i) if(!vis[i]) pot.push_back(i);
	while(N < totN) val[++N] = pot[rnd() % pot.size()];
	output();
}

int main(){
	sieve();
	strong1(100000);
	dominate(8);
	random(5000);
	random(30000);
	random(200000);
	random(500000);
	strong1(200000);
	strong1(300000);
	strong1(400000);
	strong1(500000);
	return 0;
}
