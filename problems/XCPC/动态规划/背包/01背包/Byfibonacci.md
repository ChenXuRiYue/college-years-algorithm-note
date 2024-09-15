**Byfibonacci**

https://ac.nowcoder.com/acm/contest/54944/B

2021广东省省赛：

#### solve

考虑一些问题：
1. 对于一个数怎么分解为若干个斐波那契数的组合。
   每一个数字只能使用一次，于是问题转变成了，若干个斐波那契数相加为规定容量的问题。这样就可以求出01背包的方案。

2. 回到题意本身的贡献：计算

   子问题的方案贡献的和乘上选择的斐波那契数，就是该问题的答案。所以01背包即可。

**状态转移方程：**
$$
f_{i , j} = f_{i - 1, j - a_i}*a_i + f_{i - 1 , j}
$$

#### 生长思考：

**卡常：**

1. 减少mod运算。mod运算相当的大。
2. 滚动数组优化：
3. cin改成scanf ， printf

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E7;
const int mod = 998244353;
int f[100] , dp[N + 1];
int main()
{
	f[1] = f[2] = 1;
	for (int  i = 3; i <= 40; ++i) {
		f[i] = f[i - 1] + f[i - 2];
	}
	dp[0] = 1;
	for (int i = 1; i <= 36; ++i) {
		for (int j = N; j >= f[i]; --j) {
			dp[j] = (dp[j] +  1LL * f[i] * dp[j - f[i]]) % mod;
		}
	}
	int q;
	scanf("%d" , &q);
	while (q --) {
		int t;
		scanf("%d" , &t);
		printf("%d\n" , dp[t]);
	}
}
```

