**C. Line Empire**

[Problem - 1659C - Codeforces](https://codeforces.com/problemset/problem/1659/C)

#### 简介：

从0点开始，要把所有的点都消灭掉：有如下几种方案：
1. 消灭：

   要求起点和消灭的城市之间没有存在，不被攻占的城市：

   $a*|x_{now} - x_{to}|$

2. 移动：

   $b*_{x_{now} - x_{to}}$

对于终点不做要求：问最小花费是多少？

[Line Empire - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/CF1659C)

#### solve

考虑所有的过程，就是不断地迁都，占领地过程。
如果要迁都，假设最终首都落到了$x_{i}$
那么来到$x_i$之前，考虑一种贪心的策略：

1. 由于攻占城市和距离差有关：
   1. 逐渐的迁移攻占；

枚举终点后，采取上述策略：转移上的花费不会受到影响：并且前面段的攻占难度最小：
于是枚举这种情况，贪心就前缀和优化，就可以求出最优的方案解。

#### code

```cpp
ll sum[N] , x[N];
void work(int testNo)
{
	int n , a , b; cin >> n >>  a >> b;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
		sum[i] = sum[i - 1] + x[i];
	}
	ll ans = 1E18;
	for (int i = 0; i <= n; i++) {
		ans = min(ans , x[i] * a + x[i] * b + (sum[n] - sum[i] - (n - i) * x[i]) * b);
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
```



