#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io
{
	int F()
	{
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G()
	{
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
int R(int l,int r){
    return (rand()%(r-l+1)+l);
}
int no=0;
void add(int n,int k){
	std::string infile = std::to_string(++no)+".in";
    freopen(infile.c_str(),"w",stdout);
	printf("%d %d\n",n,k);
}
int main()
{
    for(int k=2;k<=4;++k){
		for(int n=100000;n>99990;--n){
			add(n,k);
		}
	}
	add(100000,5);
	add(R(50000,100000),1);
	add(1,1);
	int d=R(10000,100000);
	add(d,d);
	for(int i=1;i<=32;++i){
		int n=R(50000,100000);
		int k=R(3,100);
		add(n,k);
	}
	for(int i=1;i<=30;++i){
		int k=R(4000,5000);
		int n=R(15000,40000);
		add(n,k);
	}
	add(100000,10000);
	add(100000,33333);
	add(100000,66666);
	add(100000,99999);
    return 0;
}