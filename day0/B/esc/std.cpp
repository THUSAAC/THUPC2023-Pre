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
template <const unsigned base>
struct bigint{
    int len;
    unsigned a[2000];
    bigint(){
        len=1;
        memset(a,0,sizeof(a));
        a[1]=0;
    }
    bigint(unsigned x){
        if(x==0){
            bigint();
            return;
        }
        memset(a,0,sizeof(a));
        len=0;
        while(x){
            a[++len]=x%base;
            x/=base;
        }
    }
    void operator *=(unsigned y) {
        unsigned car=0;
        for(int i=1;i<=len;++i){
            a[i]=a[i]*y+car;
            if(a[i]>=base){
                car=a[i]/base;
                a[i]-=car*base;
            }
            else{
                car=0;
            }
        }
        if(car){
            a[++len]=car;
        }
    }
    void divmod(unsigned d,unsigned& r) {
        r=0;
        for(int i=len;i;--i){
            r=r*base+a[i];
            a[i]=r/d;
            r-=a[i]*d;
        }
        if(!a[len]&&len>1)--len;
    }
    void operator +=(int y) {
        for(int i=1;i<=len;++i){
            a[i]+=y;
            if(a[i]>=base){
                y=1;
                a[i]-=base;
            }
            else break;
        }
        if(a[len+1])++len;
    }
    void print(){
        int b=0,tmp=base;
        while(tmp>1){
            ++b;
            tmp/=10;
        }
        char fmt[10];
        sprintf(fmt,"%%0%du",b);
        printf("%u",a[len]);
        for(int i=len-1;i>=1;--i){
            printf(fmt,a[i]);
        }
        puts("");
    }
};
template <const unsigned base>
void solve(int n,int k){
    int now=k;
    int X=1;
    int y=0;
    while(X+y<=k){
        int q=k/(X+y+1);
        int r=k%(X+y+1);
        if(r<=X){
            now+=q;
            X=X+1-r;
            y+=r;
        }
        else{
            now+=q+1;
            int tmp=r-X;
            X+=X+y+1-r;
            y=tmp;
        }
        if(now>=n){
            printf("%d\n",X+y);
            return;
        }
    }
    bigint<base> x(X);
    while(now<n){
        unsigned r=0;
        x.divmod(k-1,r);
        ++now;
        x*=k;
        if(r==0){
            x+=y;
            y=0;
        }
        else{
            x+=y+r+1;
            y=k-r-1;
        }
    }
    x+=y;
    x.print();
}
int main()
{
    int n=io::F(),k=io::F();
    if(n==k){
        puts("1");
        return 0;
    }
    if(k==1){
        puts("Poor E.S.!");
        return 0;
    }
    if(k==2){
        return 0;
    }
    if(k<=4){
        solve<1000000000>(n,k);
    }
    else if(k<=40){
        solve<100000000>(n,k);
    }
    else{
        solve<10000>(n,k);
    }
    return 0;
}