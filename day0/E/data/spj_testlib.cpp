#include<bits/stdc++.h>
#include"testlib_for_tuoj.h"
using namespace std;

const int _ = 3e5 + 3; int cnt[_]; queue < int > hand_queue; multiset < int > hand; vector < int > stk; bool vis[_];
void push(int x , int peo){
	if(vis[x]){
		if(peo) hand.insert(x); else hand_queue.push(x);
		int t; do{t = stk.back(); stk.pop_back(); vis[t] = 0; if(peo) hand.insert(t); else hand_queue.push(t);}while(t != x);
	}else{vis[x] = 1; stk.push_back(x);}
}

int main(int argc, char** argv){
	registerTestlibCmd(argc, argv);
	int N = inf.readInt(1 , 3e5 , "N"); for(int i = 1 ; i <= N ; ++i) vis[i] = cnt[i] = 0;
	for(int i = 1 ; i <= N ; ++i){int t = inf.readInt(1 , N); hand_queue.push(t); ensuref(++cnt[t] <= 2 , "input error");}
	for(int i = 1 ; i <= N ; ++i) for(int j = cnt[i] ; j < 2 ; ++j) hand.insert(i);
	int ansv = ans.readInt() , outv = ouf.readInt(); if(outv != ansv) quitf(_wa , "Wrong Step.");
	for(int i = 1 ; i <= outv ; ++i){
		int t = ouf.readInt(1 , N , "card");
		ensuref(hand.find(t) != hand.end() , "card does not exist");
		push(t , 1); push(hand_queue.front() , 0); hand_queue.pop(); hand.erase(hand.find(t));
		ensuref(hand.size() , "You lose");
		if(hand_queue.empty()) ensuref(i == outv , "Game ends but you are still moving");
	}
	if(ansv != -1) ensuref(hand_queue.empty() ,  "Game continues but you do not move");
	quitf(_ok , "Correct.");
	return 0;
}
