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
int R(int l,int r){
	return rand()%(r-l+1)+l;
}
int main(int argc, char **argv)
{
	auto *t=(new char);
    srand((unsigned long long)t);
	int n=(argc==1)?50000:atoi(argv[1]);
    printf("%d\n",n);
    for(int i=1;i<=n;++i){
        for(int j=0;j<=1;++j){
            a[++pa]=i;
        }
    }
    std::random_shuffle(a+1,a+2*n+1);
	int cnt[2]={};
	while(1){
		int x,y;
		do{
			x=R(0,1);
			y=R(0,13);
			y=R(1,1<<y);
		}
		while(cnt[x]==2*n);
		cmin(y,2*n-cnt[x]);
		for(int i=1;i<=y;++i){
			b[++pb]=x;
		}
		cnt[x]+=y;
		if(cnt[0]==2*n&&cnt[1]==2*n)break;
	}
	for(int i=1;i<=4*n;++i){
		c[++pc]=a[++s[b[i]]];
	}
    for(int i=1;i<=4*n;++i){
        printf("%d%c",c[i]," \n"[i==4*n]);
    }
	delete t;
    return 0;
}
