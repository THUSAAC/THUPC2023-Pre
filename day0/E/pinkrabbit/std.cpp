#include <iostream>
#include <vector>

int main() {
   int n;
   std::cin >> n;
   if (n == 1) {
      std::cout << "-1\n";
      return 0;
   }
   std::vector<int> a(n), t(n, 0), b(n + 1, -1);
   int k = 0;
   for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
      if (b[a[i]] == -1)
         b[a[i]] = i;
      else
         t[b[a[i]]] = 1,
         ++k,
         b[a[i]] = n;
   }
   if (!k) {
      std::cout << n + 2 << '\n' << a[1] << ' ' << a[0] << ' ' << a[0];
      for (int i = 2; i < n; ++i)
         std::cout << ' ' << a[i];
      std::cout << ' ' << a[0] << '\n';
   } else {
      std::vector<int> c;
      for (int i = 1; i <= n; ++i)
         if (b[i] == -1)
            c.push_back(i);
      std::cout << n << '\n' << c[0];
      for (int i = 0; i < n; ++i) {
         int j = i;
         while (t[j] == 1)
            ++j;
         if (j > i) {
            for (int w = 1; w < j - i; ++w)
               std::cout << ' ' << c[w];
            std::cout << ' ' << c[0];
         }
         if (j + 1 < n) {
            if (i == j)
               std::cout << ' ' << a[i];
            else
               std::cout << ' ' << c[0];
         }
         i = j;
      }
      std::cout << '\n';
   }
   return 0;
}
