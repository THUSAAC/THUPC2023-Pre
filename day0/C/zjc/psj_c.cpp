#include <bits/stdc++.h>
using namespace std;

const int N = 500005, M = 1000005, LOG = 22, R = 3, mod = 998244353;

template <class T>
void read(T &x) {
	int sgn = 1;
	char ch;
	x = 0;
	for (ch = getchar(); (ch < '0' || ch > '9') && ch != '-'; ch = getchar()) ;
	if (ch == '-') ch = getchar(), sgn = -1;
	for (; '0' <= ch && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	x *= sgn;
}
template <class T>
void write(T x) {
	if (x < 0) putchar('-'), write(-x);
	else if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}

int n, m = 0, r[N];
int min_pr[M << 1], pri[M << 1], mx[M << 1], se[M << 1], inv[M << 2], w[LOG][M << 2], len = 1, cnt = 0;
bool is_pri[M << 1];

int qpow(int a, int b) {
	int res = 1;
	for (; b; a = 1LL * a * a % mod, b >>= 1) {
		if (b & 1) res = 1LL * res * a % mod;
	}
	return res;
}
void init() {
	for (int i = 1; i <= (m << 1); i++) is_pri[i] = (i != 1), min_pr[i] = i;
	for (int i = 2; i <= (m << 1); i++) {
		if (is_pri[i]) pri[cnt++] = i, min_pr[i] = i;
		for (int j = 0; j < cnt && i * pri[j] <= (m << 1); j++) {
			min_pr[i * pri[j]] = pri[j];
			is_pri[i * pri[j]] = false;
			if (i % pri[j] == 0) break;
		}
	}
	for (len = 1; len <= (m << 1); len <<= 1) ;
	for (int i = 2, j = 1; i <= len; i <<= 1, j++) {
		w[j][0] = 1, w[j][1] = qpow(R, mod - 1 >> j);
		for (int k = 2; k <= i; k++) w[j][k] = 1LL * w[j][k - 1] * w[j][1] % mod;
	}
	inv[1] = 1;
	for (int i = 2; i <= len; i++) inv[i] = 1LL * (mod / i) * (mod - inv[mod % i]) % mod;
}

int bitrev[M << 1];
void dft(int *a, int len, int ty) {
	bitrev[0] = 0;
	for (int i = 1; i < len; i++) {
		bitrev[i] = bitrev[i >> 1] >> 1;
		if (i & 1) bitrev[i] |= (len >> 1);
	}
	for (int i = 0; i < len; i++) {
		if (bitrev[i] < i) swap(a[i], a[bitrev[i]]);
	}
	for (int i = 1, j = 1; i < len; i <<= 1, j++) {
		for (int k = 0; k < len; k += (i << 1)) {
			for (int l = 0; l < i; l++) {
				int u = a[k + l], v = a[k + l + i], c = w[j][ty > 0 ? l : (i << 1) - l];
				a[k + l] = (u + 1LL * v * c) % mod;
				a[k + l + i] = (u + 1LL * v * (mod - c)) % mod;
			}
		}
	}
	if (ty < 0) {
		for (int i = 0; i < len; i++) a[i] = 1LL * a[i] * inv[len] % mod;
	}
}

int num[M << 1];
int calc1(int x) {
	int res = 1;
	while (x > 1) {
		int p = min_pr[x], t = 0;
		for (; x % p == 0; x /= p) t++;
		if (t == mx[p]) res = 1LL * res * num[p] % mod;
	}
	return res;
}
int calc2(int x) {
	int res = 1;
	while (x > 1) {
		int p = min_pr[x], t = 0;
		for (; x % p == 0; x /= p) t++;
		if (t > mx[p]) {
			for (int i = 0; i < t - mx[p]; i++) res *= p;
		}
	}
	return res;
}

int coef[N], seq1[M << 2], seq2[M << 2], seq3[M << 2];
int main() {
	read(n);
	for (int i = 1; i <= n; i++) read(r[i]), m = max(m, r[i]);
	init();
	for (int i = 1; i <= (m << 1); i++) mx[i] = se[i] = 0;
	for (int i = 1; i <= n; i++) {
		int x = r[i];
		while (x > 1) {
			int p = min_pr[x], t = 0;
			for (; x % p == 0; x /= p) t++;
			if (t > mx[p]) se[p] = mx[p], mx[p] = t;
			else if (t > se[p]) se[p] = t;
		}
	}

	int base = 1, ans = 0;
	for (int i = 1; i <= (m << 1); i++) {
		if (is_pri[i]) {
			num[i] = qpow(inv[i], mx[i] - se[i]);
			base = 1LL * base * qpow(i, mx[i]) % mod;
		}
	}

	for (int i = 0; i < len; i++) seq1[i] = 0;
	for (int i = 1; i <= n; i++) coef[i] = calc1(r[i]), seq1[r[i]] = (seq1[r[i]] + coef[i]) % mod;
	for (int i = 0; i < len; i++) seq2[i] = seq1[i];
	dft(seq2, len, 1);
	for (int i = 0; i < len; i++) seq3[i] = 1LL * seq2[i] * seq2[i] % mod;
	dft(seq3, len, -1);
	for (int i = 1; i <= n; i++) seq3[r[i] << 1] = (seq3[r[i] << 1] + mod - 1LL * coef[i] * coef[i] % mod) % mod;
	for (int i = 0; i < len; i++) seq3[i] = 1LL * seq3[i] * inv[2] % mod;
	for (int i = 0; i <= (m << 1); i++) ans = (ans + 1LL * base * seq3[i] % mod * calc2(i)) % mod;
	write(ans), putchar('\n');
	return 0;
}