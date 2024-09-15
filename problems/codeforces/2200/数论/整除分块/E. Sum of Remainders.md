

# E. Sum of Remainders

[Problem - E - Codeforces](https://codeforces.com/contest/616/problem/E)

### 题目描述

计算以下式子的和：$n \bmod 1 + n \bmod 2 + n \bmod 3 + \dots + n \bmod m$。由于结果可能很大，你需要输出其对 $10^9+7$ 取模的结果。

#### 输入输出格式

**输入格式：**

一行两个整数 $n,m(1 \leq n,m \leq 10^{13})$。

**输出格式：**

输出整数 $s$，表示结果对 $10^9+7$ 取模的结果。

## solve

首先从整体考虑，统计这些贡献。并且关注一些根号复杂度的角度。

**对mod运算进行一个转换 ，更加方便更加宏观的统计答案。**
$$
a\%b = a -\left \lfloor \frac{a}{b} \right \rfloor *b
$$
整体上考虑：
$$
\sum _{i = 1}^{m} a -\left \lfloor \frac{a}{i} \right \rfloor *i\\
n\times m - \sum_{i =1}^{m}\left \lfloor \frac{a}{i} \right \rfloor *i
$$
关注每一个整除分块的贡献。然后通过$O(1)$算出每一块的贡献。最终的复杂度为$\sqrt m$。

**考虑一个整除分块具体的贡献：**

1. 将$\left \lfloor \frac{a}{i} \right \rfloor$ 提出一整个加法分式后，于是转变成等差数列求和问题。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define int ll

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;;
const ll INF = 1E18 + 7;
const int N = 1E6 + 10;
const int mod = (int)1E9 + 7;
void add(ll& a , ll b) {
    a += b;
    a %= mod;
    if (a < 0) a += mod;
}

ll qpow(ll x , ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) res = res * x %  mod;
        x = x * x % mod;
        n /= 2;
    }
    return res;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n , m;
    cin >> n >> m;
    ll ans = (n % mod) * (m % mod) % mod;

    ll inv2 = qpow(2 , mod - 2);
    // ll inv2 = 2;
    for (ll l = 1, r; l <= min(n , m); l = r + 1) {
        r = min( n / (n / l) , m);
        //基于当前定位的快操作。
        // cerr << l << " " << r << "\n";
        add(ans , -((((r + l)  % mod) * ((r - l + 1) % mod) % mod * inv2) % mod * (n / l)) % mod);
    }
    (ans += mod) %= mod;
    cout << ans << "\n";
}
```





