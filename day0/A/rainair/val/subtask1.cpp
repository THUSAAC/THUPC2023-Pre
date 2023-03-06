#include "testlib.h"
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
int f[MAXN],cnt;

int find(int x){
	return x == f[x] ? x : f[x] = find(f[x]);
}

void merge(int x,int y){
	x = find(x);y = find(y);
	if(x == y) return;
	cnt--;
	f[x] = y;
}

int main(int argc,char *argv[]){
	registerValidation(argc,argv);

	int n = inf.readInt(1,200000,"n out of bound");
	inf.readEoln();
	FOR(i,1,n) f[i] = i;cnt = n;
	FOR(i,1,n){
		inf.readInt(0,200000,"w out of bound");
		if(i < n) inf.readSpace();
	}
	inf.readEoln();
	FOR(i,2,n){
		int fa = inf.readInt(1,n,"father out of bound");
		merge(i,fa);
		if(i < n) inf.readSpace();
	}
	ensuref(cnt==1,"Given is not a tree");
	inf.readEof();
	return 0;
}
