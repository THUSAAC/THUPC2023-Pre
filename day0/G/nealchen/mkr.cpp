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
int main(int argc, char **argv)
{
	int n=(argc==1)?50000:atoi(argv[1]);
    srand(time(0));
    for(int i=1;i<=n;++i)p[i]=i;
    std::random_shuffle(p+1,p+n+1);
    printf("%d\n",n);
    for(int z=1;z<=4;++z){
        for(int i=1;i<=n;++i){
            printf("%d%c",p[i]," \n"[z==4&&i==n]);
        }
    }
    return 0;
}
