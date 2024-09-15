**F. XOR Counting**
https://codeforces.com/contest/1816/problem/F

![image-20230414215429101](image-20230414215429101.png)

#### solve

不妨先解决一个问题：

1. 设置m个数相加。一共有多少种方案？
   1. 可以设置状态暴力枚举。复杂度为$O(n)$如果n来到了1E9直接爆炸。
   2. 可能有一些数学规律。

**题解：**

1. 分类特殊情况
   1. m = 1 : 特殊解；就是等于1.
   2. m = 2 ？？。
   3. m >= 3

**m = 1**

直接算即可。

**m >= 3**
$$
(x , \frac {n-x}{2} , \frac {n -x}{2} , ....)
$$
对于m >= 3是否任意x（1  <= x <= n）都可以实现？显然不行：‘

1. 如果n是奇数。最终分出的多个数的第一位中 ，其最终的异或和必然是奇数。
2. 如果n是偶数。最终多个数的异或和必然是偶数 ， 综上。

综上如果n是奇数。范围内的所有奇数都可以达到。如果是偶数。范围内的所有偶数都可以达到。

**m = 2**

![image-20230414233823114](image-20230414233823114.png)

对两个资源空间进行映射。同时发现他们的独立的解一一对应是等效的。

#### 生长思考：

1. 怎么理解这个映射？
   1. 将值映射到小空间的一些值中。然后整体上考虑得到两个解空间的关系。（角度）
      1. 具体方法。
         1. 迁移：找到映射方程 - 》 二进制模型除2.（没什么好说的 ，体会几周。）
2. 非常精彩的等效性思维。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;
const ll mod = 998244353;
unordered_map<ll , ll> f, g;


void dfs(ll n) {
	if (g[n] != 0) return;
	if (n % 2) {
		dfs((n - 1) / 2);
		g[n] = g[(n - 1) / 2];
		f[n] = (2 * f[(n - 1) / 2] + g[(n - 1) / 2]) % mod;
	} else {
		dfs(n / 2);
		dfs(n / 2 - 1);
		g[n] = (g[n / 2] + g[n / 2 - 1]) % mod;
		f[n] = 2 * (f[n / 2] + f[n / 2 - 1]) % mod;
	}
}

void work(int testNo)
{
	ll n , m;
	cin >> n >> m;
	if (m == 1) {
		cout << n % mod << "\n";
		return;
	} else if (m >= 3) {
		if (n % 2) {
			cout << (((n / 2 + 1) % mod ) * ((n / 2 + 1) % mod)) % mod << "\n";
		} else {
			cout << (((n / 2 + 1) % mod) * ((n / 2) % mod)) % mod << "\n";
		}
	} else {
		dfs(n);
		cout << f[n] << "\n";
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	g[0] = 1;
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

