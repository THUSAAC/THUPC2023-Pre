//Love and Freedom.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<stack>
#include<cassert>
#define ll long long
#define inf 20021225
#define N 50010
using namespace std;
int read()
{
    int s=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')    f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9')    s=s*10+ch-'0',ch=getchar();
    return s*f;
}
int c[N];
int main()
{
	int n=read();
	for(int i=1;i<=(n<<2);i++)
	{
		int x=read();
		assert(x>=1 && x<=n);
		c[x]++; 
	}
	for(int i=1;i<=n;i++)	assert(c[i]==4);
	return 0;
}
