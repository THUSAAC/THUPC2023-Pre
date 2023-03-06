#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define ull unsigned lint
#define db double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
inline int getn(int a,int b) { return (rand()*32768+rand())%(b-a+1)+a; }
inline db getr() { return (rand()*32768.0+rand())/(INT_MAX/2.0); }
inline db getr(db n) { return getr()*n; }
inline db getr(db a,db b) { return getr()*(b-a)+a; }
int Sv[6][3]={
	{1,0,0},
	{-1,0,0},
	{0,1,0},
	{0,-1,0},
	{0,0,1},
	{0,0,-1}
};
set<pair<pii,int> > s;
int main()
{
	FILE *fsd=fopen("seed.txt","r");unsigned int sd,ccc;fscanf(fsd,"%u%u",&sd,&ccc);
	FILE *gsd=fopen("seed.txt","w");sd+=12321,ccc+=1;fprintf(gsd,"%u\n%u\n",sd,ccc);
	freopen("data.in","w",stdout),srand((unsigned int)time(0)+sd);
	int n=100,T=100,Tz=T,x=100;printf("%d %d\n",n,T);
	double theta=acos(-1.0)/2,Lx=100,Hy=Lx,ds=2,Vm_pl=5,Vm_ms=10,dp=10;
	
	rep(i,1,2*n)
	{
		int a=getn(-x,x),b=getn(-x,x),c=getn(-x,x);
		while(s.count(mp(mp(a,b),c)))
			a=getn(-x,x),b=getn(-x,x),c=getn(-x,x);
		s.insert(mp(mp(a,b),c));
		printf("%d %d %d\n",a,b,c);
		int d=getn(0,5),u=getn(0,5);
		while(u==d||(u^d)==1) u=getn(0,5);
		#define get_t getr(theta/2,theta)
		printf("%d %d %d %d %d %d\n",Sv[d][0],Sv[d][1],Sv[d][2],Sv[u][0],Sv[u][1],Sv[u][2]);
		printf("%.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n",get_t,get_t,get_t,getr(3,Vm_pl),getr(1,Lx),getr(1,Hy));
		printf("%.6lf %.6lf %.6lf %.6lf %.6lf %d\n",get_t,getr(3,Vm_ms),getr(1,ds),getr(1,dp),get_t,getn(1,Tz));
		printf("\n");
	}
	return 0;
}
