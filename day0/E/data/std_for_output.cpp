#include<bits/stdc++.h>
using namespace std;

const int _ = 3e5 + 7; int T , N , seq[_] , cnt[_]; multiset < int > hand;
bool vis[_]; vector < int > step , stk;
void push(int x , bool peo){
	if(peo){hand.erase(hand.find(x)); step.push_back(x);}
	if(vis[x]){int t; do{t = stk.back(); vis[t] = 0; stk.pop_back(); if(peo) hand.insert(t);}while(t != x); if(peo) hand.insert(x);}
	else{stk.push_back(x); vis[x] = 1;}
}

int main(){
	cin >> N; for(int i = 1 ; i <= N ; ++i){cin >> seq[i]; ++cnt[seq[i]];}
	if(N == 1){cout << -1; return 0;}
	for(int i = 1 ; i <= N ; ++i) for(int j = cnt[i] ; j < 2 ; ++j) hand.insert(i);
	int pos = 1 , pre; while(cnt[pos]) ++pos;
	if(pos == N + 1){push(seq[N] , 1); pre = seq[1];} else push(pre = pos , 1);
	for(int i = 1 ; i < N ; ++i){
		push(seq[i] , 0);
		if(vis[seq[i + 1]] || hand.count(seq[i + 1])){push(pre , 1); pre = seq[i + 1];}
		else{auto t = hand.begin(); push((*t == pre ? *(++t) : *t) , 1);}
	}
	if(pos == N + 1){step.push_back(1 + (seq[N] == 1)); step.push_back(1 + (seq[N] == 1));}
	cout << step.size() << '\n';
	//for(int i = 0 ; i < step.size() ; ++i) cout << step[i] << " \n"[i + 1 == step.size()];
	return 0;
}
