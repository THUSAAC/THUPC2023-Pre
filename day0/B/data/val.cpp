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
void end_chk(){
	char c;
	do{
		c = gc;
		assert(c == -1 || c == ' ' || c == '\n' || c == '\r');			
	}while(c != -1);
}
int n,m;
int main(){
	int tot = 100;
	for(int tsd = 1;tsd <= tot;++tsd){
		cerr<<tsd<<":"<<endl;
		char ch[50];
		sprintf(ch,"%d.in",tsd);
		freopen(ch,"r",stdin);
		n = read(1,100000);
		m = read(1,n);
		end_chk();
		fclose(stdin); 
		freopen("con","r",stdin);
		sprintf(ch,"b2.exe <%d.in >std.out",tsd);
		system(ch);
		sprintf(ch,"fc %d.ans std.out",tsd);
		system(ch);
	} 
	return 0;
}
