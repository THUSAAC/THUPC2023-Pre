#include<bits/stdc++.h>
using namespace std;

long long mx[100003] , v[53] , c[53] , V; int N , q , pos = 1;

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N >> q; for(int i = 1 ; i <= N ; ++i){cin >> v[i] >> c[i]; if(v[i] * c[pos] < v[pos] * c[i]) pos = i;}
	memset(mx , -0x3f , sizeof(mx)); mx[0] = 0;
	int num = 0;
	for(int i = 1 ; i <= N ; ++i)
		for(int j = 0 ; j < __gcd(v[pos] , v[i]) ; ++j)
			for(int k = j , nxt , cnt = 0 ; cnt != 2 ; cnt += (k = nxt) == j){
				nxt = (k + v[i]) % v[pos];
				mx[nxt] = max(mx[nxt] , mx[k] + c[i] - (k + v[i]) / v[pos] * c[pos]);
				++num;
			}
	while(q--){cin >> V; long long val = mx[V % v[pos]] + V / v[pos] * c[pos]; cout << max(val , -1ll) << '\n';}
	return 0;
}
