#include<bits/stdc++.h>
using namespace std;

set < int > val; vector < int > pot[100003]; int N , X; long long ans;

int main(){
	cin >> N; for(int i = 1 ; i <= N ; ++i){cin >> X; pot[X].push_back(i); val.insert(i);}
	for(int i = 1 ; val.size() ; ++i){ans += 1ll * *val.rbegin() * val.size(); for(auto t : pot[i]) val.erase(t);}
	cout << ans; return 0;
}
