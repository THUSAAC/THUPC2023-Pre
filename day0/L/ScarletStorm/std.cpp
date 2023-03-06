#include <cstdio>
#include <cstring>
using namespace std;
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
long double f[100008];
int s[9][2], u[9][4], v[9][4], n, c, current_score;
int id[9][135], presum[261], failsum[261], sum[261], tot;
inline long double get_prob(int score){
	return score < 0 ? 0 : f[score];
}
long double calc(int d, int s){
	int nowid = id[d][s];
	long double res = (d > 1 ? get_prob(current_score - presum[nowid]) : 0), fail, normal, high, tmp;
	if (d == n) {
		fail = (d > 1 ? get_prob(current_score - failsum[nowid]) : 0);
		normal = get_prob(current_score - sum[s << 1]);
		high = get_prob(current_score - sum[s << 1 | 1]);
	}
	else {
		fail = (d > 1 ? get_prob(current_score - failsum[nowid]) : 0);
		normal = calc(d + 1, s << 1);
		high = calc(d + 1, s << 1 | 1);
	}
	// cmax(res, fail);
	tmp = (u[d][0] * fail + u[d][1] * normal + u[d][2] * high) / u[d][3];
	cmax(res, tmp);
	tmp = (v[d][0] * fail + v[d][1] * normal + v[d][2] * high) / v[d][3];
	cmax(res, tmp);
	return res;
}
void init(int d, int state, int score){
	if (d > n) {
		sum[state] = score;
		return ;
	}
	id[d][state] = tot++;
	presum[id[d][state]] = score;
	failsum[id[d][state]] = c * score / 100;
	init(d + 1, state << 1, score + s[d][0]);
	init(d + 1, state << 1 | 1, score + s[d][1]);
	return ;
}
int main(){
	int m, i;
	long double lbd, rbd, mid, res;
	scanf("%d %d %d", &n, &m, &c);
	for (i = 1; i <= n; ++i) {
		scanf("%d %d %d %d %d %d %d %d", &s[i][0], &s[i][1], &u[i][0], &u[i][1], &u[i][2], &v[i][0], &v[i][1], &v[i][2]);
		u[i][3] = u[i][0] + u[i][1] + u[i][2];
		v[i][3] = v[i][0] + v[i][1] + v[i][2];
	}
	u[1][0] = v[1][0] = 0;
	u[1][3] = u[1][1] + u[1][2];
	v[1][3] = v[1][1] + v[1][2];
	init(1, 0, 0);
	f[0] = 1;
	for (current_score = 1; current_score <= m; ++current_score) {
		lbd = 0.0;
		rbd = 1.0;
		while (rbd - lbd > 1e-18) {
			mid = (lbd + rbd) / 2;
			f[current_score] = mid;
			res = calc(1, 0);
			if (mid < res) lbd = mid;
			else rbd = mid;
		}
		f[current_score] = (lbd + rbd) / 2;
	}
	for (i = 1; i <= m; ++i) printf("%.18Lf%c", f[i], " \n"[i == m]);
	return 0;
}
