# E. Lomsat gelral

https://codeforces.com/problemset/problem/600/E

- 有一棵  $n$ 个结点的以  $1$ 号结点为根的**有根树**。
- 每个结点都有一个颜色，颜色是以编号表示的， $i$ 号结点的颜色编号为  $c_i$。
- 如果一种颜色在以  $x$ 为根的子树内出现次数最多，称其在以  $x$ 为根的子树中占**主导地位**。显然，同一子树中可能有多种颜色占主导地位。
- 你的任务是对于每一个  $i\in[1,n]$，求出以  $i$ 为根的子树中，占主导地位的颜色的编号和。
-  $n\le 10^5,c_i\le n$

### solve

运用书上启发式合并的思想
1. 对小子树求解后进行合并求更大子树的解：

**集中精力解决的问题：**

1. 维护内容设计：
   1. 面向某个节点时，每个颜色出现的次数。
   2. 众数出现的次数。
   3. 总颜色编号的和，以及答案。

2. add函数的设计。
   1. add， 首先调用与重儿子相关的函数。
   
   2. 某个阶段下， 只需要关注
   
3. del函数的设计。
   1. del函数设计是因为，一整块存储结构要只被重儿子使用。如果当前探索的节点并非是其父亲的重度儿子。那么就应该把它及时清空。
   1. 由贡献源到记录的清空，而不是全局的清空。

**复杂度分析：**

1. 单看一个点被朴素的add的访问次数。
2. 作为一个轻儿子，和启发式合并一样，最多被成为logn个轻儿子的节点。
3. 因此总的复杂度是log n次。

### 生长思考：

1. 和树形dp的对比：
   1. 和树形dp相比 ，这并非是策略的最优性问题，而是对这颗子树的结构的探究，对某些属性以及关注函数的计算。
   2. 这里的合并是朴素的，因为子树的结构上的属性信息更大的树的内容之一。关于
2. 如何启发自己？
   1. 方向就是关注问题中的内容：问题中的内容：是否是子树的一些结构信息，以及子树信息是否可以合并成为更大子树。


### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1E5 + 10;
int c[N];
int l[N] , r[N] , id[N] , sz[N] , hs[N] , tot;
int cnt[N]; //每个颜色出现的次数。
int mxcnt; // 众数出现的次数。
ll sumcnt , ans[N];;// 总数颜色编号的和。
vector<int> e[N];
void dfs_init(int u , int fa) {
	l[u] = ++ tot;
	id[tot] = u;
	sz[u] = 1;
	hs[u] = -1;
	for (auto v : e[u]) {
		if (v == fa) continue;
		dfs_init(v , u);
		sz[u] += sz[v];
		if (hs[u] == -1 || sz[v] > sz[hs[u]])
			hs[u] = v;
	}
	r[u] = tot;
}
void dfs_solve(int u , int fa , bool keep) {
	for (auto v : e[u]) {
		if (v != fa && v != hs[u]) {
			dfs_solve(v , u , false);
		}
	}
	if (hs[u] != - 1) {
		dfs_solve(hs[u] , u , true);
		// 重儿子集合
	}
	auto add = [&](int x) {
		x = c[x];
		cnt[x]++;
		if (cnt[x] > mxcnt) mxcnt = cnt[x] , sumcnt = 0;
		if (cnt[x] == mxcnt) sumcnt += x;

	};
	auto del = [&](int x) {
		x = c[x];
		cnt[x] --;
	};
	for (auto v : e[u]) {
		if (v != fa && v != hs[u]) {
			for (int x = l[v]; x <= r[v]; x++)
				add(id[x]);
		}
	}
	// u本身加入。
	add(u);
	ans[u] = sumcnt;
	if (!keep) {
		mxcnt = 0;
		sumcnt = 0;
		for (int x = l[u]; x <= r[u]; x++) {
			del(id[x]);
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
	}
	for (int i = 1; i < n; i++) {
		int u , v; cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs_init(1 , 0);
	dfs_solve(1 , 0 , false);
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " \n"[i == n];
	}
}
```









