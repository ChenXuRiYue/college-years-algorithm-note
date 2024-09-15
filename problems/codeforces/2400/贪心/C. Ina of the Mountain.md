# C. Ina of the Mountain

https://codeforces.com/problemset/problem/1852/C

To prepare her "Takodachi" dumbo octopuses for world domination, Ninomae Ina'nis, a.k.a. Ina of the Mountain, orders Hoshimachi Suisei to throw boulders at them. Ina asks you, Kiryu Coco, to help choose where the boulders are thrown.

There are $n$ octopuses on a single-file trail on Ina's mountain, numbered $1, 2, \ldots, n$. The $i$\-th octopus has a certain initial health value $a_i$, where $1 \leq a_i \leq k$.

Each boulder crushes consecutive octopuses with indexes $l, l+1, \ldots, r$, where $1 \leq l \leq r \leq n$. You can choose the numbers $l$ and $r$ arbitrarily for each boulder.

For each boulder, the health value of each octopus the boulder crushes is reduced by $1$. However, as octopuses are immortal, once they reach a health value of $0$, they will immediately regenerate to a health value of $k$.

Given the octopuses' initial health values, find the **minimum** number of boulders that need to be thrown to make the health of all octopuses equal to $k$.

为了让她的 "Takodachi "大章鱼做好称霸世界的准备，Ninomae Ina'nis（又名 "山之伊娜"）命令 Hoshimachi Suisei 向它们投掷巨石。伊娜让你--桐生可可--帮忙选择投掷巨石的位置。
伊娜山上的一条单行小路上有$n$只章鱼，编号为$1, 2, \ldots, n$。第$i$只章鱼有一定的初始健康值$a_i$，其中$1 \leq a_i \leq k$只。
每块巨石都会压碎指数为$l, l+1, \ldots, r$的连续章鱼，其中$1 \leq l \leq r \leq n$。你可以为每块巨石任意选择数字$l$和$r$。
对于每块巨石，被巨石压碎的每只章鱼的健康值都会减少 $1$。不过，由于章鱼是不死之身，一旦它们的健康值达到 $0$，就会立即再生到健康值 $k$。
给定章鱼的初始健康值，求最少需要投掷多少块巨石才能使所有章鱼的健康值等于 $k$。

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^5$). The description of the test cases follows.

The first line of each test case contains two integers $n$ and $k$ ($1 \le n \le 2 \cdot 10^5$, $1 \le k \le 10^9$) – the number of octopuses, and the upper bound of a octopus's health value.

The second line contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le k$) – the initial health values of the octopuses.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

### solve

首先对问题做一些简单的迁移：

1. 将问题转变成花费代价，使得每一个矩形的升降。 为了使得思维背景更加朴素：因此将思维背景转变为如下：

   将所有矩形降到0的代价：

   1. 如果$a_i = k$ 则重定义对应矩形高度为0.

**问题1 ： 当所有矩形的高度确定时 ， 最优秀操作次数怎么计算？**

1. 到下个矩形的每一次上升的统计就是最优答案。

**问题2 ： 什么样的升降策略确定答案？**

考虑贪心，处理每一次的上升的代价：

1. 追求1 ... i的最优解：

   考察第i个时， 当前可以进行的选择是：

   1. 不做上升。将当前上升作为贡献。
   2. 上升一个k：

考虑第二种操作的变化。我们可以通过一些手段来调整这个代价： 选择之前的下降最高。找到这一段之后，在这段区间都上升一个k。发现一些现象：
1. 总操作数，变化是d + k。
2. 其它的下降本质上是不变的。
考虑到前方最优的选择总是要被使用，因此能用就用。
因此整体上，比较两种操作之后，选择的更优方案，与前方的最优方案拼接构成了当前规模下的最小贡献。

![草稿 (1)](%E8%8D%89%E7%A8%BF%20(1).png)

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 1E6 + 10;

int a[N];

void work(int testNo)
{
	int n , k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (a[i] == k) a[i] = 0;
	}
	priority_queue<int , vector<int> , greater<int>> que;
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		int d = a[i] - a[i - 1];
		if (d == 0) continue;
		if (d < 0) que.push(d);
		else if (que.size() && k + que.top() < d) {
			ans += k + que.top();
			que.pop();
			que.push(d - k);
		} else {
			ans += d;
		}
	}
	cout << ans << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```
