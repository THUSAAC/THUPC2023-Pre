#include<bits/stdc++.h>
using namespace std;

#define ld long double
#define eps 1e-9
const int _ = 1e4 + 7 , LIMN = 6 , TOTAL = 1 << LIMN | 1; ld dp[_] , val[TOTAL] , prob[LIMN][2][3];
int Log2[TOTAL << 1] , trans[TOTAL][2] , N , M , C , sum[TOTAL << 1] , S[LIMN][2];

ld qval(int i , int j , int pos){
	if(pos == 0){int dlt = sum[j] * C / 100; return i >= dlt ? dp[i - dlt] : 0;}
	int nj = trans[j][pos - 1] , dlt = sum[nj];
	if(Log2[nj] == N) return i >= dlt ? dp[i - dlt] : 0;
	return max(val[nj] , i >= dlt ? dp[i - dlt] : 0);
}

int main(){
	cin >> N >> M >> C;
	for(int i = 0 ; i < N ; ++i){
		cin >> S[i][0] >> S[i][1];
		for(int j = 0 ; j < 2 ; ++j){
			int sum = 0; for(int k = 0 ; k < 3 ; ++k){cin >> prob[i][j][k]; sum += prob[i][j][k];}
			for(int k = 0 ; k < 3 ; ++k) prob[i][j][k] /= sum;
		}
	}
	for(int i = 2 ; i < 1 << (N + 1) ; ++i){Log2[i] = Log2[i >> 1] + 1; for(int j = 0 ; j < Log2[i] ; ++j) sum[i] += S[j][i >> j & 1];}
	for(int i = 1 ; i < 1 << N ; ++i) for(int j = 0 ; j < 2 ; ++j) trans[i][j] = (i | (2 << Log2[i])) & ~(!j << Log2[i]);
	dp[0] = 1;
	for(int i = 1 ; i <= M ; ++i){
		ld L = 0 , R = 1;
		while(R - L > eps){
			ld mid = (L + R) / 2; dp[i] = mid;
			for(int k = (1 << N) - 1 ; k ; --k){
				val[k] = 0;
				for(int p = 0 ; p < 2 ; ++p){
					ld sum = 0; for(int q = 0 ; q < 3 ; ++q) sum += prob[Log2[k]][p][q] * qval(i , k , q);
					val[k] = max(val[k] , sum);
				}
			}
			val[1] > mid ? L = mid : R = mid;
		}
		cout << fixed << setprecision(12) << (dp[i] = L) << ' ';
	}
	return 0;
}