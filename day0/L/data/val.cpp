#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int TOTAL = 47;

int main(){
	for(int i = 1 ; i <= TOTAL ; ++i){
		cout << "validating test case " << i << endl;
		freopen((to_string(i) + ".in").c_str() , "r" , stdin);
		registerValidation();
		int N = inf.readInt(1 , 6 , "N"); inf.readSpace();
		int M = inf.readInt(1 , 10000 , "M"); inf.readSpace();
		int C = inf.readInt(0 , 100 , "C"); inf.readEoln();
		for(int i = 1 ; i <= N ; ++i){
			int S1 = inf.readInt(1 , 1e4 , "S1"); inf.readSpace();
			int S2 = inf.readInt(S1 , 1e4 , "S2"); inf.readSpace();
			for(int P = 0 ; P < 2 ; ++P){
				static int V[3];
				for(int Q = 0 ; Q < 3 ; ++Q){
					V[Q] = inf.readInt(0 , 1e4);
					if(P == 1 && Q == 2) inf.readEoln();
					else inf.readSpace();
				}
				ensuref(V[1] + V[2] >= 1 , "u_1+u_2 / v_1+v_2 = 0");
			}
		}
		inf.readEof();
		fclose(stdin);
	}
	return 0;
}
