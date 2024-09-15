# C. Baby Ehab Partitions Again

https://codeforces.com/problemset/problem/1516/C

宝宝 Ehab 正在玩数组。他有一个长度为 $n$的数组 $a$。如果没有办法将数组分割成 $2$ 个子序列，使得第一个子序列中的元素之和等于第二个子序列中的元素之和，那么他就认为这个数组是好数组。现在他想删除 $a$中的最少元素数，使其成为一个好数组。你能帮助他吗？

如果通过删除一些（可能是零或全部）元素可以从 $a$得到 $b$，那么序列 $b$就是数组 $a$的子序列。数组的分割是一种将数组分成 $2$ 个子序列的方法，每个元素恰好属于一个子序列，因此必须使用所有元素，不能共享任何元素。

### solve

首先就几种特殊的情况展开一些讨论：

1. 如果和为奇数那么已经是优解了：
否则考察不花费的情况下是否可以分成两个序列： 这是一个经典的利用bitset实现的可行性背包问题。

2. 发现至多只需要花费1的消费就可以得到好序列：

可以对这个序列做一个等效处理，就是将每一个元素除于2：

1. 这种方式下，组合的相对关系是不变化的，其好序列的本质属性不变。其每一种划分方式对应原数组中的划分方式，其结果是等效的。
2. 这样不断除于2，必然会出现奇数，于是就递归到了上述1中的讨论。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define return return 0;

const int inf = 1E9 + 7;;
const ll INF = 1E18 + 7;
const int N = 110;
const int M = 100 * 2000 + 1;

int a[N];
bitset<M> f[N];

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	ll sum = 0;

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	if (sum % 2) {
		cout << 0 << "\n";
		return;
	}

	f[0][0] = 1;

	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] | (f[i - 1] << a[i]);
	}

	if (f[n][sum / 2] == 0) {
		cout << 0 << "\n";
		return;
	}

	while (true) {
		for (int i = 1; i <= n; i++) {
			if (a[i] % 2) {
				cout << 1 << "\n";
				cout << i << "\n";
				return;
			}
			a[i] /= 2;
		}
	}

}
```

