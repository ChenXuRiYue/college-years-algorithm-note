#include<iostream>

using namespace std;

const int N = 2020;
int mod=998244353;

int c[N][N];//相当于数学中的组合公式Cab（数学公式不知如何插入le...）

void init(){
  for(int i = 0; i < N; i++)
      for(int j = 0; j <= i; j++)
      if(!j)c[i][j] = 1;
      else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1])  % mod;//递推公式

}
/*
int main(){
  init();
  int n; cin >> n;
  while(n --){
      int a, b;
      cin >> a >> b;
      cout << c[a][b] << endl;
  }
  return 0;
}*/
#include<iostream>
using namespace std;
#define int long long
const int N = 1e6 + 7, mod = 1e9 + 7;
int n, m, k, t; 
int inv[N];
int fact[N], infact[N];

void init (int n)
{
    fact[0] = infact[0] = inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; ++ i) 
        inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 1; i <= n; ++ i) {
        fact[i] = 1ll * fact[i - 1] * i % mod;
        infact[i] = 1ll * infact[i - 1] * inv[i] % mod;
    }
}

int c(int n, int m)
{
    if(n < m) return 0;
    if(m == 0 || n == m) return 1;
    return 1ll * fact[n] * infact[m] % mod * infact[n - m] % mod;
}


