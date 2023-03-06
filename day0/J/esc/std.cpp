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
const int M=998244353,H=M+1>>1;
int p[444444];
int q[444444];
int ex(int b,int e=M-2){
	int ret=1;
	for(;e;e>>=1,b=1ll*b*b%M){
		if(e&1)ret=1ll*ret*b%M;
	}
	return ret;
}
int main()
{
    int n=io::F();
	/*long double out=0.5;
	long double in=0;
	p[0]=1;
	for(int i=1;i<=n;++i){
		p[i]=(out-in)/(i+out-in);
		in=out*(1-p[i]);
		out=(i+1.0L)/2;
	}
	q[0]=1;
	out=1;
	in=0;
	for(int i=1;i<=n;++i){
		q[i]=(out-in)/(i/2.0L+out-in);
		in=out*(1-q[i]);
		out=i+1;
	}
	long double px=1,qx=1;
	for(int i=n;i>=0;--i){
		long double tmp=p[i]*px;
		px*=(1-p[i]);
		p[i]=tmp;
		tmp=q[i]*qx;
		qx*=(1-q[i]);
		q[i]=tmp;
	}*/
	int out=H;
	int in=0;
	p[0]=1;
	for(int i=1;i<=n;++i){
		p[i]=1ll*(out+M-in)*ex(1ll*i+out+M-in)%M;
		in=1ll*out*(1+M-p[i])%M;
		out=1ll*(i+1)*H%M;
	}
	q[0]=1;
	out=1;
	in=0;
	for(int i=1;i<=n;++i){
		q[i]=1ll*(out+M-in)*ex((1ll*i*H+out+M-in)%M)%M;
		in=1ll*out*(1+M-q[i])%M;
		out=i+1;
	}
	int px=1,qx=1;
	for(int i=n;i>=0;--i){
		int tmp=1ll*p[i]*px%M;
		px=1ll*px*(1+M-p[i])%M;
		p[i]=tmp;
		tmp=1ll*q[i]*qx%M;
		qx=1ll*qx*(1+M-q[i])%M;
		q[i]=tmp;
	}
	for(int i=0;i<=n;++i){
		printf("%d%c",p[i]," \n"[i==n]);
	}
	for(int i=0;i<=n;++i){
		printf("%d%c",q[i]," \n"[i==n]);
	}
    return 0;
}