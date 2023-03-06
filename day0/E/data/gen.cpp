#include<bits/stdc++.h>
using namespace std;

const int _ = 3e5 + 7; mt19937 rnd(12348792); int file_id = 1;

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

void gen3(int size){
	// n/2 pairs
	if(size & 1) --size;
	static int cnt = 0; vector < int > pot , num;
	int step = rnd() % 2 ? rnd() % (int)(sqrt(5 * size)) : 0;
	for(int i = 1 ; i <= size ; ++i) num.push_back(i);
	shuffle(num.begin() , num.end() , rnd); num.resize(size / 2);
	switch((cnt++) % 4){
	case 0:
		for(auto t : num){pot.push_back(t);pot.push_back(t);}
		shuffle(pot.begin() , pot.end() , rnd); break;
	case 1:
		shuffle(num.begin() , num.end() , rnd); for(auto t : num) pot.push_back(t);
		shuffle(num.begin() , num.end() , rnd); for(auto t : num) pot.push_back(t);
		break;
	case 2: for(auto t : num){pot.push_back(t);pot.push_back(t);} break;
	case 3:
		for(auto t : num) pot.push_back(t);
		reverse(num.begin() , num.end()); for(auto t : num) pot.push_back(t);
	}
	for(int i = 0 ; i < step ; ++i){int x = rnd() % pot.size() , y = rnd() % pot.size(); swap(pot[x] , pot[y]);}
	output(pot);
}

void gen45(int size){
	// at least 1 pair
	if(rnd() % 2) return gen3(size);
	static int cnt = 0; vector < int > pot , num;
	int step = rnd() % 2 ? rnd() % (int)(sqrt(5 * size)) : 0 , pos;
	for(int i = 1 ; i <= size ; ++i) num.push_back(i);
	shuffle(num.begin() , num.end() , rnd);
	
	switch((cnt++) % 4){
	case 0:
		for(auto t : num){pot.push_back(t); pot.push_back(t);}
		while(1){
			shuffle(pot.begin() , pot.end() , rnd);
			static bool vis[_]; memset(vis , 0 , sizeof(bool) * (size + 1)); int cnt = 0;
			for(int i = 0 ; i < size ; ++i){cnt += !vis[pot[i]]; vis[pot[i]] = 1;}
			if(cnt != size) break;
		}
		pot.resize(size); break;
	case 1:
		for(int i = 1 ; i < size - 1 ; ++i) pot.push_back(num[i]);
		pos = rnd() % (pot.size() + 1);
		pot.insert(pot.begin() + pos , num[0]); pot.insert(pot.begin() + pos , num[0]);
		break;
	case 2:
		for(int i = 0 ; pot.size() < size ; ++i)
			if(size - pot.size() > 2){pot.push_back(num[i]); pot.push_back(num[i]);}
			else{int pos = rnd() % (pot.size() + 1); pot.insert(pot.begin() + pos , num[i]);}
		break;
	case 3:
		for(int i = 1 ; i < size - 1 ; ++i) pot.push_back(num[i]);
		pos = rnd() % (pot.size() + 1);
		pot.insert(pot.begin() + pos , num[0]); pot.insert(pot.end() , num[0]);
	}
	for(int i = 0 ; i < step ; ++i){int x = rnd() % pot.size() , y = rnd() % pot.size(); swap(pot[x] , pot[y]);}
	output(pot);
}

void gen67(int size){
	// no pair
	vector < int > pot; for(int i = 1 ; i <= size ; ++i) pot.push_back(i);
	if(file_id % 2) shuffle(pot.begin() , pot.end() , rnd);
	else for(int i = rnd() % (int)(sqrt(5 * size)) ; i ; --i){int x = rnd() % pot.size() , y = rnd() % pot.size(); swap(pot[x] , pot[y]);}
	output(pot);
}

void gen_rand(int size){
	vector < int > pot; for(int i = 1 ; i <= size ; ++i){pot.push_back(i); pot.push_back(i);}
	shuffle(pot.begin() , pot.end() , rnd); pot.resize(size);
	output(pot);
}

int gen(int L , int R){return rnd() % (R - L + 1) + L;}

int main(){
	for(int i = 1 ; i <= 8 ; ++i) gen45(gen(2e5 , 3e5));
	gen_rand(1); gen_rand(2); gen_rand(4); gen_rand(gen(5,15)); gen_rand(gen(100, 250)); gen_rand(gen(2e5 , 3e5)); gen_rand(gen(1e3 , 2e4)); gen_rand(gen(2e4 , 5e4));
	gen67(gen(2e5 , 3e5)); gen67(gen(2e5 , 3e5)); gen67(gen(1e3 , 2e3)); 
	return 0;
}
