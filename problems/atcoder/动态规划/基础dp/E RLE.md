**E.RLE**

[Editorial - Monoxer Programming Contest 2022（AtCoder Beginner Contest 249）](https://atcoder.jp/contests/abc249/editorial/3883)

#### solve

**状态定义**：
定义状态$f_{i , j}$表示S串长度为i ， T串长度为j方案个数。
**状态转移**
由小更新大的贡献转移角度：

1. $dp_{i , j}$枚举k。然后贡献后方。
    **复杂度分析**
    枚举i， j总体的复杂度应该是：$O(N^3)$

**考虑优化**

关注从大到小直接统计转移：

当我们枚举计算某个状态时，发现贡献来源于几种不同二维数组中某一段之和。因此可以使用前缀和优化。具体的实现方案是：分析枚举在后面拼接不同的字母长度。将其对k的影响分类成三种情况,分别为1 10 100 1000 10000 .假设拼接的的长度为1....9。对于j维度关注关注j - 2段的下标。 假设拼接长度为 10 ....99 考虑 j - 3段的前缀。依此类推。
$$
dp_{i , j} += (sum[i - 1][j - 2] - sum[i - 10][j - 2])\times 25;\\
dp_{i,j} += (sum[i - 10][j - 3] - sum[i - 1000][j-3])\times 25\\
推广到第10^k次种长度
dp_{i , j} += (sum[i - 10^k] - sum[i - 10^{k+1}])\times 25
$$


**初始化**

考虑那些全放同一个字母的各种方案作为最小状态：

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3E3 + 10;

ll dp[N][N];
int lg(int x) {
	int res = 1;
	while (x) {
		x /= 10;
		res++;
	}
	return res;//在基础上加1的刚刚好。
}

ll sum[N][N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n , p; cin >> n >> p;
	int pre[6] = {1 , 10 , 100 , 1000 , 10000 , 100000};
	for (int i = 1; i <= n; i++) {
		dp[i][lg(i)] = 26;

	}
	for (int i = 1; i <= n; i++) {
        //小心对无关的状态做贡献。计算错误。还是要详细研究转移过程。
		for (int j = lg(i) + 1; j <= min(n , i * 2); j++) {
			for (int k = 1; k <= 4; k++) {
				dp[i][j] += (((sum[max(0 , i - pre[k - 1])][j - k - 1] - sum[max(0 , i - pre[k])][j - k - 1]) + p) % p) * 25;
				dp[i][j] %= p;

			}
		}
		for (int j = 1; j <= n; j++) {
			sum[i][j] = (sum[i - 1][j] + dp[i][j]) % p;
		}
	}
	ll ans = 0;
	for (int i = 1; i < n; i++) {
		ans = (ans + dp[n][i]) % p;
	}
	cout << ans << '\n';
}
```

