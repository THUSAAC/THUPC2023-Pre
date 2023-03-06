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
int a[444444], pa,s[2];
int b[444444],pb;
int c[444444],pc;
int main()
{
	auto *t=(new char);
    srand((unsigned long long)t);
    int n=50000;
    printf("%d\n",n);
    for(int i=1;i<=n;++i){
        for(int j=0;j<=1;++j){
            a[++pa]=i;
			b[++pb]=j;
			b[++pb]=j;
        }
    }
    std::random_shuffle(a+1,a+2*n+1);
	std::random_shuffle(b+1,b+4*n+1);
	for(int i=1;i<=4*n;++i){
		c[++pc]=a[++s[b[i]]];
	}
    for(int i=1;i<=4*n;++i){
        printf("%d%c",c[i]," \n"[i==4*n]);
    }
	delete t;
    return 0;
}