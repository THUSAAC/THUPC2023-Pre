// 02:07 ~ 02:57

#include <iostream>
#include <vector>

using LL = long long;
const int Mod = 998244353;
const int Inv2 = (Mod + 1) / 2;

void exgcd(int a, int b, int &x, int &y) {
   if (!b) x = 1, y = 0;
   else exgcd(b, a % b, y, x), y -= a / b * x;
}
int gInv(int b) {
   int x, y;
   exgcd(Mod, b, x, y);
   return (y + Mod) % Mod;
}

int main() {
   int n;
   std::cin >> n;
   std::vector<int> inv(n + 1), a(n + 1), b(n + 1);
   inv[1] = 1;
   for (int i = 2; i <= n; ++i)
      inv[i] = (int)((LL)(Mod - Mod / i) * inv[Mod % i] % Mod);
   {
      a[0] = 1;
      int s = 0;
      for (int i = 1; i <= n; ++i) {
         a[i] = (int)(((LL)s * inv[i] + a[i - 1] + Mod) % Mod * Inv2 % Mod);
         s = (s + a[i - 1]) % Mod;
      }
      s = (s + a[n]) % Mod;
      int is = gInv(s);
      for (int i = 0; i <= n; ++i)
         a[i] = (int)((LL)a[i] * is % Mod);
   }
   {
      b[0] = 1;
      int s = 0;
      for (int i = 1; i <= n; ++i) {
         b[i] = (int)(((LL)s * inv[i] + b[i - 1] + Mod) * 2 % Mod);
         s = (s + b[i - 1]) % Mod;
      }
      s = (s + b[n]) % Mod;
      int is = gInv(s);
      for (int i = 0; i <= n; ++i)
         b[i] = (int)((LL)b[i] * is % Mod);
   }
   for (int i = 0; i <= n; ++i)
      std::cout << a[i] << " \n"[i == n];
   for (int i = 0; i <= n; ++i)
      std::cout << b[i] << " \n"[i == n];
   return 0;
}