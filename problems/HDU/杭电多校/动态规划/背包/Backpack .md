# Backpack
 [Backpack - HDU 7140 - Virtual Judge (vjudge.net)](https://vjudge.net/problem/HDU-7140)

给定一个规定容量的背包， 选取一些物品，要求这些物品的体积和刚好等于背包的容量。求出可行方案下，选择物品之间异或和的最大值。

其中数据范围大概都是1000：

### solve

**第一个角度：**
做一个普通的背包：$f_{i ,j }$ 表示选择了前i位 ， j空间。但是发现这转移不了。因此再开一个维度去记录前面方案的异或和。首先这空间上是不允许的，其次，每次考察新的物品，其转移是异或和的转移。是无性质的。每一个之前的异或和可能都要更新转移。是行不通的。

**第二个角度**

将其转换成一个可行性问题：追求一个移位性的转移。然后可以使用bitset优化暴力复杂度的dp。

**状态定义**

bitset<m + 1> $f_{i ,j}$ 表示考虑前i个物品， 当前的异或和为j , 背包体积为0....m的可行性。

**状态转移方程：**
考虑当前物品选或者不选两种策略：
$f_{i , j , x} = max(f_{i - 1 , j , x} , f _{i -1 , j \oplus v , x - w})$

发现对于该元素的转移，实际上对组进行一个偏移后复制。（并且由于是可行性问题，只要求0与1两种信息。）因此可以使用bitset , 优化。

**总复杂度：**

$O(\frac {nm}{w})$

#### 生长思考：
一个方案可以有多种属性： 这些属性之间相互独立。比如上述问题中方案中的以下几个关键属性：

1. 价值的异或和。
2. 重量

其中两个量的值域都是有限的。可以直接开一个数组记录。转换角度 ： 对一个给定重量的选择情况下，可行方案中异或和的存在情况，逆向思维转换成：给定异或和某个值，可行方案中所有物品总质量大小存在情况。 然后就神奇的完成转移了。可见有时候，虽然是研究同一个空间，正向与逆向的考虑可能是有所不同的。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;;
const ll INF = 1E18 + 7;
const int N = (1 << 10) + 10;
const int M = 1 << 10;
void solve() {
	int n, m; cin >> n >> m;
	array <bitset<M>, M > f;
	// 表示重量为0 ， 异或和为0true：
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		int v, w; cin >> w >> v;
		auto g = f;
		for (int j = 0; j < M; j++) {
			f[j] |= g[j ^ v] << w;
		}
	}
	for (int i = M - 1; i >= 0; i--) {
		if (f[i][m]) {
			cout << i << "\n";
			return;
		}
	}
	cout << -1 << "\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}
```

