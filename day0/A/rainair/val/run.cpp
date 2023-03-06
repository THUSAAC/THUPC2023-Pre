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

const int id[10][2] = {
	{0,0},
	{1,21}
};

const int n = 1;

int main(){
	FOR(i,1,n){
		printf("Testing Subtask %d:\n",i);
		system(("g++-11 subtask" + std::to_string(i) + ".cpp -o val").c_str());
		FOR(j,id[i][0],id[i][1]){
			bool t = system(("./val < ../../data/" + std::to_string(j) + ".in").c_str());
			if(t){
				printf("Fail: Subtask %d, Test Case #%d\n",i,j);
				system("rm -rf val");
				exit(1);
			}
			else{
				printf("Test Case #%d OK\n",j);
			}
		}
		printf("Subtask %d: OK\n",i);
	}
	system("rm -rf val");
	return 0;
}
