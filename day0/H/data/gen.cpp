#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

mt19937_64 rnd(time(0) ^ getpid());
long long gen(long long L , long long R){return rnd() % (R - L + 1) + L;}
int file_id = 1;
const long long VL = 1e11 , VR = 1e12 , VMX = 1e5 , CMX = 1e6 , NMX = 50 , QMX = 1e5;
long long N = NMX , Q = QMX , v[53] , c[53] , q[100003];

void output(){
	ofstream out(to_string(file_id) + ".in");
	out << N << ' ' << Q << '\n';
	for(int i = 1 ; i <= N ; ++i) out << v[i] << ' ' << c[i] << '\n';
	for(int i = 1 ; i <= Q ; ++i) out << gen(VL , VR) << '\n';
	out.close();
	system(("std.exe < " + to_string(file_id) + ".in > " + to_string(file_id) + ".ans").c_str());
	++file_id;
}

void max_answer(){
	for(int i = 1 ; i <= N ; ++i){v[i] = rnd() % VMX + 1; c[i] = rnd() % CMX + 1;}
	int t = rnd() % N + 1; v[t] = 1; c[t] = CMX;
	output();
}

void random(){
	for(int i = 1 ; i <= N ; ++i){v[i] = rnd() % VMX + 1; c[i] = rnd() % CMX + 1;}
	output();
}

void check_gcd(){
	int K = rnd() % 30 + 2; for(int i = 1 ; i <= N ; ++i){v[i] = rnd() % (VMX / K) * K + K; c[i] = v[i] / K * 10 - 3;}
	output();
}

int genv(){
	int flag = rnd() % 3;
	switch(flag){
	case 0: return gen(20 , 1000);
	case 1: return gen(2e4 , 1e5);
	case 2: return gen(20 , 1e5);
	}
	assert(0); return 0;
}

void strong(vector < int > ratio){
	int vbase = genv() , cbase = rnd() % CMX + 1;
	while(cbase * 1000 < vbase){vbase = genv() , cbase = rnd() % CMX + 1;}
	for(int i = 1 ; i <= N ; ++i){
		v[i] = genv(); c[i] = v[i] * cbase / vbase;
		int t = rnd() % ratio[3];
		if(t < ratio[0])//similar ratio
			c[i] -= rnd() % 2;
		else if(t < ratio[1])//a bit smaller ratio
			c[i] -= rnd() % 20;
		else if(t < ratio[2]) //medium ratio
			c[i] -= rnd() % 300;
		else //large ratio
			c[i] -= rnd() % 5000;
		if(c[i] <= 0 || c[i] > CMX) --i;
	}
	int t = rnd() % N + 1; v[t] = vbase; c[t] = cbase;
	output();
}

int main(){
	max_answer(); random(); random(); random(); random(); check_gcd(); check_gcd();
	strong({0,0,0,1}); strong({0,0,1,1}); strong({0,1,1,1}); strong({1,1,1,1}); strong({1,2,3,4});
	for(int i = 1 ; i <= 8 ; ++i){
		vector < int > p; for(int j = 1 ; j <= 4 ; ++j) p.push_back(rnd() % 100 + 1);
		for(int i = 1 ; i < 4 ; ++i) p[i] += p[i - 1];
		strong(p);
	}
	return 0;
}
