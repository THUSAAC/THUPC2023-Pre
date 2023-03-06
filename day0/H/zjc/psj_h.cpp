#include <bits/stdc++.h>
#define debug(x) cerr << #x << " " << (x) << endl
using namespace std;
typedef long long ll;
const int N = 55, V = 1000005;
const ll inf = (ll)1e18;

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

int n, q, v[N];
ll c[N], f[V];
bool vis[V];
void add(int vol, ll val, int mod, ll v) {
	for (int i = 0; i < mod; i++) vis[i] = false;
	for (int i = 0; i < mod; i++) {
		if (vis[i]) continue;
		ll tmp = -inf;
		for (int j = 0; j <= 1; j++) {
			int k = i;
			do {
				vis[k] = true, f[k] = max(f[k], tmp);
				tmp = f[k] + val, k += vol;
				tmp -= v * (k / mod), k %= mod;
			} while (k != i);
		}
	}
}

int main() {
	read(n), read(q);
	for (int i = 1; i <= n; i++) read(v[i]), read(c[i]);

	int pos = 1;
	for (int i = 2; i <= n; i++) {
		if (1LL * c[i] * v[pos] > 1LL * c[pos] * v[i]) pos = i;
	}
	for (int i = 0; i < v[pos]; i++) f[i] = i ? -inf : 0;
	for (int i = 1; i <= n; i++) add(v[i], c[i], v[pos], c[pos]);
	for (int i = 1; i <= q; i++) {
		ll vol;
		read(vol);
		ll ans = c[pos] * (vol / v[pos]) + f[vol % v[pos]];
		write(ans >= 0 ? ans : -1), putchar('\n');
	}
	return 0;
}