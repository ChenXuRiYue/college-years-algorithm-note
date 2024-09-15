# D. Array Differentiation
https://codeforces.com/problemset/problem/1552/D
给你一个由 $n$个整数组成的序列 $a_1, \, a_2, \, \dots, \, a_n$。
是否存在一个 $n$整数序列 $b_1, \, b_2, \, \dots, \, b_n$，使得下面的性质成立？

- 对于每个$1 \le i \le n$，存在两个（不一定不同）指数$j$和$k$（$1 \le j, \, k \le n$），使得$a_i = b_j - b_k$成立。

### solve

[题解 CF1552D 【Array Differentiation】 - SSerxhs 的博客 - 洛谷博客 (luogu.com.cn)](https://www.luogu.com.cn/blog/SSerxhs/solution-cf1552d)

参考博客：
1. 第一点，$b_i - b_j = a , b_j -b_i = -a$ : 原数组中元素的正负对解没有影响，为了方便处理统一变成正数：

2. 建模：抽象出b之间的关系。如果两个元素之间产生一个a那么就连一条边。

3. 对上述的图进行分析：

   1. n条边n个点， 如果构造出一个合法的图就必须有环。
   2. 由于边代表了$b_i - b_j = x$ 这样对每一个边代表的方程相加：则最终为$\sum x = 0$

4. 在一个环中，当确定一个节点时，只关注一个元素对其它元素进行展开：
   $$
   b_1 = b_1\\
   b_2 = f_1(b_1)\\
   b_3 = f_2(b_2)= f_2(f_1(b_1))\\
   $$

5. 最终都可以用$b_1$进行表示 ： 综上有环则必有解：其余连通图，显然容易构造：
   

**实现方式：**
  问题已经转变成了是否可以判断有若干个$a_i$ 随意分配正负（重定向）使得最终和为0：

使用进制模型，压位枚举： 下面是三进制地使用技巧：给一个数字地分配方式有：

1. 为0      对应0
2. 为a      对应1
3. 为-a     对应2

### code

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 1E6 + 10;

void work(int testNo)
{
	int n;
	cin >> n;
	vector<int> a(n);
	int c = 1; // 枚举子集。
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		c *= 3;
	}
	// 至少从一开始：
	for (int i = 1; i < c; i++) {
		int t = i;
		ll sum = 0;
		for (int j = 0; j < n; j++) {
			int x = t % 3;
			t /= 3;
			if (x == 2) x = -1;
			sum += x * a[j];
		}
		if (sum == 0) {
			cout << "YES\n";
			return;
		}
	}
	cout << "NO\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```



