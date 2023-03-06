#include<bits/stdc++.h>
using namespace std;

int n;
int a;

int main(){
	for(int T=1;T<=13;T++){
		string infile = std::to_string(T)+".in";
	    freopen(infile.c_str(),"r",stdin);
		scanf("%d",&n);
		assert(n>=1&&n<=100000);
		while(n--){
			scanf("%d",&a);
			assert(a>=1&&a<=100000);
		}
		char c;assert(scanf("%c",&c)==EOF);
		cout<<T<<" OK\n";
	}
}
