#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN=100200;
const int MAXA=100000;

int n;
int a[MAXN];
priority_queue<pair<int,int> ,vector<pair<int,int> >, greater<pair<int,int> > >hp;
int sum[MAXN];
long long suma[MAXN];
bool is_del[MAXN];

signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
		hp.push(make_pair(a[i],i));
		sum[a[i]]++;
		suma[a[i]]+=a[i];
	}
	for(int i=1;i<=MAXA;i++)sum[i]+=sum[i-1];
	for(int i=1;i<=MAXA;i++)suma[i]+=suma[i-1];
	
	long long lst=0;
	long long ans=0;
	long long lsta=-1;
	for(int i=n;i>=1;i--){
		if(is_del[i])continue;
		long long nw=(n-sum[a[i]])*a[i]+suma[a[i]];
		assert(a[i]>lsta);lsta=a[i];
		ans+=1ll*i*(nw-lst);
		assert(nw>lst);lst=nw;
		while(!hp.empty()&&hp.top().first<=a[i])is_del[hp.top().second]=true,hp.pop();
	}
	printf("%lld\n",ans);
	return 0;
}
