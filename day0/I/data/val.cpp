#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
#define li long long
using namespace std;
inline li read(li l = 0,li r = 1e9){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9'){
		assert(y != '-' && (c == ' ' || c == '\n' || c == '\r' || c == '-'));
		y = c;c = gc;
	} 
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	assert(c == -1 || c == ' ' || c == '\n' || c == '\r');
	if(y == '-') x *= -1;
	assert(x >= l && x <= r);
	return x;
}
inline double read_double(double l = 0,double r = 1e9,int len = 6){
	double x = 0;
	char c[50];
	scanf("%s",c);
	int fg = 0,wz = 0;
	for(int i = strlen(c) - 1;i >= 0;--i){
		if(c[i] == '.') ++fg,wz = i;
		if(c[i] != '.' && (c[i] < '0' || c[i] > '9')) assert(0);
	}
	if(fg > 1 || (fg == 1 && wz < strlen(c) - len - 1)) assert(0);
	sscanf(c,"%lf",&x);
	//cerr<<l<<" "<<x<<" "<<r<<endl; 
	assert(l <= x && x <= r);
	return x; 
}
void end_chk(){
	char c;
	do{
		c = gc;
		assert(c == -1 || c == ' ' || c == '\n' || c == '\r');			
	}while(c != -1);
}
int n,m;
set<pair<int,pair<int,int>>> a,b;
#define mp make_pair
int main(){
	int tot = 32;
	for(int tsd = 1;tsd <= tot;++tsd){
		cerr<<tsd<<":"<<endl;
		//goto qwq;
		char ch[50];
		sprintf(ch,"%d.in",tsd);
		freopen(ch,"r",stdin);
		a.clear();b.clear();
		b.insert(mp(1,mp(0,0)));
		b.insert(mp(-1,mp(0,0)));
		b.insert(mp(0,mp(1,0)));
		b.insert(mp(0,mp(-1,0)));
		b.insert(mp(0,mp(0,1)));
		b.insert(mp(0,mp(0,-1)));
		n = read(1,100);
		m = read(1,100);
		long double pi = acosl(-1);
		int tmp = 0;
		double p;
		for(int i = 1;i <= n + n;++i){
			int x,y,z;
			x = read(-100,100);y = read(-100,100);z = read(-100,100);
			assert(a.find(mp(x,mp(y,z))) == a.end());
			a.insert(mp(x,mp(y,z)));
			x = read(-1,1);y = read(-1,1);z = read(-1,1);
			assert(b.find(mp(x,mp(y,z))) != a.end());
			x = read(-1,1);y = read(-1,1);z = read(-1,1);
			assert(b.find(mp(x,mp(y,z))) != a.end());
			
			read_double(pi / 4,pi / 2);
			read_double(pi / 4,pi / 2);
			read_double(pi / 4,pi / 2);
			p = read_double(3,20);
			if(p > 10) ++tmp;
			read_double(1,100);
			read_double(1,100);
			
			read_double(pi / 4,pi / 2);
			p = read_double(3,20);
			if(p > 10) ++tmp;
			read_double(1,20);
			read_double(1,20);
			read_double(pi / 4,pi / 2);
			read(1,100);
		}
		cerr<<tmp<<endl;
		end_chk();
		fclose(stdin); 
		freopen("con","r",stdin);
		continue;
		qwq:
		sprintf(ch,"std.exe <%d.in >std.out",tsd);
		//sprintf(ch,"i.exe <%d.in >%d.ans",tsd,tsd);
		system(ch);
		continue;
		sprintf(ch,"fc %d.ans std.out",tsd);
		system(ch);
		
	} 
	return 0;
}
