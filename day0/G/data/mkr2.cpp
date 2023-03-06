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
int p[55555];
int main()
{
    int no=io::F();
    int n=50000;
    std::string infile = std::to_string(no)+".in";
    freopen(infile.c_str(),"w",stdout);
    srand(time(0));
    for(int i=1;i<=n;++i)p[i]=i;
    std::random_shuffle(p+1,p+n+1);
    printf("%d\n",n);
    for(int i=1;i<=n;++i){
		printf("%d %d ",p[i],p[i]);
	}
	for(int i=n;i>=1;--i){
		printf("%d %d%c",p[i],p[i]," \n"[i==1]);
	}
    return 0;
}