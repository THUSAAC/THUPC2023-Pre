#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, a[2007];
long double f[2007], g[2007], tmp[4005];
void mod(long double *p){
	for (int i = 1; i <= n; ++i) *(p - a[i]) += *p / n;
	return ;
}
void fastmod(int t, int k) {
	int cnt = 0, rev = 0, i, j;
	while (t > k) {
		rev = (rev << 1) | (t & 1);
		t >>= 1;
		++cnt;
	}
	g[t] = 1;
	while (cnt--) {
		memset(tmp, 0, sizeof(long double) * (k << 1 | 1));
		for (i = 0; i <= k; ++i) for (j = 0; j <= k; ++j) tmp[i + j] += g[i] * g[j];
		for (j = k << 1; j > k; --j) mod(tmp + j);
		if (rev & 1) {
			g[0] = 0;
			memcpy(g + 1, tmp, sizeof(long double) * k);
			for (i = 1; i <= n; ++i) g[k + 1 - a[i]] += tmp[k] / n;
		}
		else memcpy(g, tmp, sizeof(long double) * (k + 1));
		rev >>= 1;
	}
	return ;
}
int main(){
	int l, i, j, a0 = 0;
	long double ans, fx;
	scanf("%d %d", &n, &l);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if (a0 < a[i]) a0 = a[i];
	}
	sort(a + 1, a + n + 1);
	if (l < a0) {
		fx = 0;
		g[0] = 1;
		for (j = 0; j <= l; ++j) {
			for (i = 1; i <= n; ++i) {
				if (j + a[i] <= l) g[j + a[i]] += g[j] / n;
				else fx += g[j] / n;
			}
			f[j] = fx;
		}
		
		for (j = l; j >= 0; --j) {
			fx = 0;
			for (i = 1; i <= n; ++i) {
				if (j + a[i] <= l) fx += f[j + a[i]] / n;
			}
			if (fx > f[j]) f[j] = fx;
		}
		printf("%.18Lf\n", f[0]);
	}
	else {
		fastmod(l, a0 - 1);
		memcpy(tmp, g, sizeof(long double) * a0);
		
		fx = 0;
		for (j = a0 - 1; j >= 0; --j) {
			for (i = 1; i <= n; ++i) {
				if (a[i] <= j) g[j - a[i]] += g[j] / n;
				else fx += g[j] / n;
			}
			f[j] = fx;
		}
		
		ans = 0;
		for (j = 0; j < a0; ++j) {
			fx = 0;
			for (i = 1; i <= n; ++i) {
				if (a[i] <= j) fx += f[j - a[i]] / n;
			}
			if (fx > f[j]) f[j] = fx;
			ans += f[j] * tmp[j];
		}
		printf("%.18Lf\n", ans);
	}
	
	return 0;
}
