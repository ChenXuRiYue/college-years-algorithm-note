***D. Renting Bikes***
https://codeforces.com/problemset/problem/363/D
#### 题目简介
有n个学生。他们之中有公共的可使用的钱 记为$a$ . 每一个学生有自己的钱。它们去租自行车。但是他们自己的钱买自己的自行车。公共的钱可以任意的分配。问最多可以有多少人拥有自行车。同时使得他们自己付出的钱最少。
#### solve
1. 尝试二分。枚举一个数字x ， check： 购买自行车的数量是否可以达到这个数字。
   1. 最保守的策略是，钱最多的x个人， 一一匹配买最便宜的x辆自行车。如果不够就去补
      1. 如果其它结构可以买到x辆。那么上述的购买策略也一定合理。
      2. 所以上述购买的策略是边界策略。作为check的标准。
2. 花钱最小
   1. 有多少补多少。显然就是$min(sum - a , 0)$.sum指的是所有单车的价格。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;

ll  n , m , a;
ll p[N] , b[N];

bool check(int x) {
	ll sum = 0;
	for (int i = 1; i <= x; i++) {
		sum += max(0LL , b[i] - p[n - x + i]);
	}
	return sum <= a;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> a;
	for (int i = 1; i <= n; i++)cin >> p[i];
	for (int i = 1; i <= m; i++) cin >> b[i];

	int low = 0 , high = min(n , m);
	sort(p + 1 , p + n + 1);
	sort(b + 1, b + m + 1);
	while (low < high) {
		int mid = (low + high + 1) / 2;
		if (check(mid))low = mid;
		else high = mid - 1;
	}
	ll sum = 0;
	for (int i = 1; i <= low ; i++) {
		sum += b[i];
	}
	cout << low << ' ' << max(0LL , sum - a) << '\n';
}
/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

