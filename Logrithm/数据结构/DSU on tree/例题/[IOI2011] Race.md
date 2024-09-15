# [IOI2011] Race

[P4149 [IOI2011\] Race - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P4149)

给一棵树，每条边有权。求一条简单路径，权值和等于 $k$，且边的数量最小。

### solve

启发式合并的解法：

1. 树上枚举路径的一种顺序可以为：

   1. 枚举一个节点： 然后通过两个子树情况的组合来枚举路径。

2. 维护信息内容：

   1. 维护当前维护的树的某权值下的最大深度。

   2. 每次在合并子树前，枚举当前是否有可行解：
      $$
      d2 = k  +  2 * dep2[u] - dep2[w];
      $$
      d2 就是在当前数据集维护的一大块子树中，查找一些权值的最小路径。

### code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;

int n, k;
vector<pair<int, int>> e[N];
int l[N], r[N], id[N], sz[N], hs[N], tot, c[N];
int dep1[N];
ll dep2[N];
int ans;
map<ll, int> val;

void dfs_init(int u, int f) {
	l[u] = ++tot;
	id[tot] = u;
	sz[u] = 1;
	hs[u] = -1;
	for (auto [v, w] : e[u]) {
		if (v == f) continue;
		dep1[v] = dep1[u] + 1;
		dep2[v] = dep2[u] + w;
		dfs_init(v, u);
		sz[u] += sz[v];
		if (hs[u] == -1 || sz[v] > sz[hs[u]])
			hs[u] = v;
	}
	r[u] = tot;
}

void dfs_solve(int u, int f, bool keep) {
	for (auto [v, w] : e[u]) {
		if (v != f && v != hs[u]) {
			dfs_solve(v, u, false);
		}
	}
	if (hs[u] != -1) {
		dfs_solve(hs[u], u, true);
	}
	auto query = [&](int w) {
		ll d2 = k  +  2 * dep2[u] - dep2[w];
		if (val.count(d2)) {
			ans = min(ans, val[d2] + dep1[w] - 2 * dep1[u]);
		}
	};
	auto add = [&](int w) {
		if (val.count(dep2[w]))
			val[dep2[w]] = min(val[dep2[w]], dep1[w]);
		else
			val[dep2[w]] = dep1[w];
	};

	for (auto [v, w] : e[u]) {
		if (v != f && v != hs[u]) {
			for (int x = l[v]; x <= r[v]; x++)
				query(id[x]);
			for (int x = l[v]; x <= r[v]; x++)
				add(id[x]);
		}
	}
	query(u); add(u);
	if (!keep) {
		val.clear();
	}
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		++u; ++v;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	ans = n + 1;
	dfs_init(1, 0);
	dfs_solve(1, 0, false);
	if (ans >= n + 1) ans = -1;
	printf("%d\n", ans);
}
```

