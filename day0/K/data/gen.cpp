#include<bits/stdc++.h>
using namespace std;

const int M = 1e5; int file_id = 1; mt19937 rnd(time(0));
void random_resize(vector < int > &V , int len){shuffle(V.begin() , V.end() , rnd); V.resize(len); sort(V.begin() , V.end());}

void gen(int len , int valType , int seqType){
	if(len >= 1000) len -= rnd() % 10;
	vector < int > valpot , seq;
	
	switch(valType){
	case 1: //All
		for(int i = 1 ; i <= M ; ++i) if(rnd() % 5) valpot.push_back(i);
		break;
	case 2: //Large value
		for(int i = M / 10 * 9 ; i <= M ; ++i) if(rnd() % 3 == 0) valpot.push_back(i);
		break;
	case 3: //Small value
		for(int i = 1 ; i <= max(50 , min((int)(len / 15) , 1000)) ; ++i) if(rnd() % 2) valpot.push_back(i);
		break;
	case 4: //Rand, Small number
		for(int i = 1 ; i <= M ; ++i) valpot.push_back(i);
		random_resize(valpot , 20);
		break;
	}
	if(len < valpot.size()) random_resize(valpot , len);
	
	vector < int > divpot; for(int i = 1 ; i < len ; ++i) divpot.push_back(i);
	random_resize(divpot , valpot.size() - 1); seq.resize(len);
	switch(seqType){
	case 1: // Totally Random
		for(auto &t : seq) t = valpot[rnd() % valpot.size()];
		break;
	case 2: // Increasing
		for(auto t : divpot) ++seq[t];
		for(int i = 1 ; i < len ; ++i) seq[i] += seq[i - 1];
		for(int i = 0 ; i < len ; ++i) seq[i] = valpot[seq[i]];
		break;
	case 3: // Decreasing
		for(auto t : divpot) ++seq[t];
		for(int i = 1 ; i < len ; ++i) seq[i] += seq[i - 1];
		for(int i = 0 ; i < len ; ++i) seq[i] = valpot[valpot.size() - 1 - seq[i]];
		break;
	case 4: //Dominant
		for(int i = 0 ; i < len ; ++i)
			if(rnd() % 15) seq[i] = valpot.back();
			else seq[i] = valpot[rnd() % valpot.size()];
	}
	
	// random pertubation
	for(int i = 1 ; i <= 2 * len ; ++i){
		int &t = seq[rnd() % len];
		if(t == M || (t != 1 && rnd() % 2)) --t; else ++t;
	}

	//output
	ofstream out(to_string(file_id) + ".in");
	out << len << '\n';
	for(int i = 0 ; i < len ; ++i){
		if(i) out << ' ';
		out << seq[i];
	}
	out.close();
	system(("std.exe < " + to_string(file_id) + ".in > " + to_string(file_id) + ".ans").c_str());
	++file_id;
}

int main(){
	gen(1e5 , 3 , 2);
	gen(7e4 , 2 , 2);
	gen(8e4 , 3 , 3);
	gen(8e4 , 2 , 3);
	gen(2 , 2 , 1);
	gen(100 , 2 , 2);
	gen(100 , 1 , 3);
	gen(1000 , 3 , 1);
	gen(6e4 , 1 , 3);
	gen(8e4 , 1 , 1);
	gen(1e5 , 1 , 4);
	gen(5e4 , 4 , 1);
	gen(1e5 , 4 , 3);
	return 0;
}
