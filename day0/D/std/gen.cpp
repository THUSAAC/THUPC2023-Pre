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
	//freopen(c,"r",stdin);
	//sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,f[200010];
inline li rdqz(int fg = 0){
	if(fg == 0) return rd() % 100000 - rd() % 100000;
	if(fg == 1) return rd() % 10000 - rd() % 10000;
	return rd() % 1000000 - rd() % 1000000;
}
int main(){
	srand(time(0));rd();
	file("apple");
	n = m = 50000;
	int i,j,op,u,v,w,x;
	print(n);pc(' ');print(m);pc('\n');
	for(i = 1;i <= n;++i) print(rdqz()),pc(' ');pc('\n');
	for(i = 2;i <= n;++i){
		if(i < n / 3) f[i] = i - 1;
		else if(i == n / 3) f[i] = 1;
		else if(i <= n / 2) f[i] = i - 1;
		else if(i <= 2 * n / 3) f[i] = n / 2;
		else f[i] = rd() % (i - 1) + 1;
		print(i);pc(' ');print(f[i]);pc('\n');
	}
	int lst1 = n,lst2 = n;
	for(i = 1;i <= m;++i){
		op = rd() % 4 + 1;
		//while(op == 1) op = rd() % 4 + 1;
		if(op == 1){
			if(rd() & 1) u = lst1;
			else u = rd() % (n - 1) + 2;
			v = f[u];
			lst1 = x = ++n;f[u] = x;f[x] = v;
			print(op);pc(' ');print(u);pc(' ');print(v);pc(' ');print(rdqz());pc('\n');
		}
		else if(op == 2){
			if(rd() & 1) u = lst2;
			else u = rd() % n + 1;
			lst2 = x = ++n;f[x] = u;
			print(op);pc(' ');print(u);pc(' ');print(rdqz());pc('\n');
		}
		else{
			print(op);pc(' ');print(rd() % n + 1);pc(' ');print(rd() % n + 1);pc(' ');
			print(rdqz(op - 2));pc('\n');
		}
	}
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}


