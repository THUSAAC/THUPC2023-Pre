#include<bits/stdc++.h>
using namespace std;

const int _ = 3e5 + 7; mt19937 rnd(time(0)); int file_id = 20;

void output(vector < int > pot){
	ofstream out(to_string(file_id) + ".in");
	out << pot.size() << '\n';
	for(int i = 0 ; i < pot.size() ; ++i){
		if(i) out << ' ';
		out << pot[i];
	}
	out.close();
	system(("std.exe < " + to_string(file_id) + ".in > " + to_string(file_id) + ".ans").c_str());
	++file_id;
}

void gen(int N , int K){
	vector < int > pot; for(int i = 1 ; i <= N ; ++i) pot.push_back(i);
	shuffle(pot.begin() , pot.end() , rnd); vector < int > seq;
	while(seq.size() != N)
		if(rnd() % 20){
			int L = rnd() % min(K + 1 , (int)(N - seq.size()) / 2 + 1); vector < int > P(pot.end() - L , pot.end()); pot.erase(pot.end() - L , pot.end());
			seq.insert(seq.end() , P.begin() , P.end());
			if(rnd() % 2) reverse(P.begin() , P.end());
			seq.insert(seq.end() , P.begin() , P.end());
		}else{seq.insert(seq.begin() + rnd() % (seq.size() + 1) , pot.back()); pot.pop_back();}
	output(seq);
}

int main(){
	gen(3e5 , 1);
	gen(3e5 , 2);
	gen(3e5 , 3);
	gen(3e5 , 5);
	gen(3e5 , 10);
	gen(3e5 , 25);
	gen(3e5 , 50);
	gen(3e5 , 200);
	gen(3e5 , 1000);
	gen(3e5 , 5000);
	gen(3e5 , 1e4);
	gen(3e5 , 3e4);
	gen(3e5 , 1e5);
	gen(3e5 , 1e5);
	gen(3e5 , 3e5);
	gen(3e5 , 3e5);

	return 0;
}
