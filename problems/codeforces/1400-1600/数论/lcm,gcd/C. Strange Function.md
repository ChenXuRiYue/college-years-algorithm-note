https://codeforces.com/contest/1542/problem/C



第一个问题。怎么研究$f_i$的性质？

$f(x)=i$，那么$f(x)\%LCM(1...i-1)==0$。

怎么在连续的数域中求出$f(x)$为i的总贡献呢。

首先关注第一个集合 $n/LCM(1....i-1)$

然后关注第二个集合$n/LCM(1....i)$

整体减去局部得到这部分的贡献

综上$\sum_{i=1}^{lcm(1..i)<=n}(i+1)\times(n/lcm(1..i)-n/lcm(1...i+1))  $



#### 生长思考：

- 从一个数的因数，来寻求关于整除运算的结论。
- 自然数集合上的优美的枚举。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;
const ll  mod = 1E9 + 7;

ll gcd(ll x , ll y)
{
	return x == 0 ? y : gcd(y % x, x);
}

ll lcm(ll x, ll y)
{
	return x * y / gcd(x, y);
}
void work(int testNo)
{
	ll n;
	cin >> n;
	ll ans = 0;
	for (ll i = 1 , x1 = 1 , x2 = 1; x2 <= n; i++)
	{
		x2 = lcm(x2, i + 1);
		x1 = lcm(x1, i);
		ans = (ans + (n / x1 - n / x2 ) * (i + 1)) % mod;
	}
	cout << ans << '\n';
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

