# **dfs序**

**概念：**

1. 对树节点打一个序标记： 其中该序和dfs的顺序有关。遇到就打一个未分配标记：
2. 使用L ， R数组 记录其子节点访问节点的序范围。

在上述记录结构下，就可以实现一些灵活自由的操作。

## 例题：

### DFS序练习1

给一棵n个点的树，每个点有点权$w_i$，1号点为根。给q个操作：

1. `1 x y`，将x点的点权改成y。
2. `2 x`，询问x点子树的点权和，到根的路径的点权和（都包含x这个点）。

#### solve

1. 关键想法， 使用dfs序，将子树上的维护问题转换成，数组的段信息的维护问题。
2. 整出dfs序数组后。使用两个树状数组维护以下信息。
   1. $d_1:$ 朴素用法维护权的前缀和。然后可以轻松解决第一个问题。x点子树的点权和就是到L[x] , R[x]的段和。
   2. $d_2: $ 维护差分数组 ， 前缀和就是x节点到根节点的路径和。那么当修改一个点权时，只有其子树内的点受到影响。于是对这一段做区间L[x] , R[x]加减即可。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define fsio ios::sync_with_stdio(false);cin.tie(0);
#define int ll

const int N = (int)1E6 + 10;
const int inf = (int)1E9 + 10;
const ll INF = (long long)1E18 + 10;
int n , q;
class BIT {
public:
	ll c[(int)1E6 + 10];
	ll query(int x) {
		ll res = 0;
		for (; x ; x -= x & (-x))
			res += c[x];
		return res;
	}
	void modify(int x, ll d) {
		assert(x != 0);
		for (; x <= n; x += x & (-x)) {
			c[x] += d;
		}
	}
	int bineray_serach(ll x) {
		int pos = 0;
		ll  t = 0;
		//18对应5e5
		//19对应1e6
		for (int i = 18; i >= 0; i--) {
			//t的水平一直是小于等于x的关系。
			if (pos + (1 << i) <= n && t + c[pos + (1 << i)] <= x) {
				pos += (1 << i);
				t += c[pos];
			}
		}
		//dbg(pos)
		return pos;
	}
} d1 , d2;

vector<int> e[N];
ll l[N] , r[N] , tot;
ll w[N];
void dfs(int u , int fa) {
	l[u] = ++tot;
	for (auto v : e[u])
		if (v != fa) {
			dfs(v , u);
		}
	r[u] = tot;
}
signed main() {
	fsio;
	cin >> n >> q;
	for (int i = 1; i < n; i++) {
		int u , v; cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1 , 0);
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
		d1.modify(l[i] , w[i]);
		d2.modify(l[i] , w[i]);
		d2.modify(r[i] + 1 , -w[i]);
	}
	// d0维护第一个问题。
	// d1 , d2 维护第二个问题；
	while (q--) {
		int ty; cin >> ty;
		if (ty == 1) {
			ll x , y; cin >> x >> y;
			ll d = y - w[x];
			w[x] = y;
			d1.modify(l[x] , d);
			d2.modify(l[x] , d);
			d2.modify(r[x] + 1 , -d);
		} else {
			int x; cin >> x;
			cout << d1.query(r[x]) - d1.query(l[x] - 1) << " " << d2.query(l[x]) << '\n';
		}
	}
}
```
-----------
### DFS序练习2

给一棵n个点的树，每个点有点权$w_i$，1号点为根。给q个操作：

1. `1 x y`，将x点的点权改成y。
2. `2 x`，询问x点子树的点权和。
3. `3 x`，将根换到x位置。

#### solve

每一次操作中，如果朴素的处理dfs序操作，那么dfs序将会变化非常大。想法是，维护之前的dsf序来完成这些操作。

当查询一个节点时： 有3种i情况： （不对dfs序做出改动，且依然用BIT维护当前序列权前缀情况下：）

1. 当前查询的节点就是根
   当前整棵树的点权和就是子树的点权和。

   

2. 根在x的子树外（这里的前提是：1作为根节点时。）

   x的子树没有发生变化：依然可以用之前的方法直接求出。


3. 根在x的子树内：（前提也是，1作为根节点。）

   找出分支直接做容斥即可。总权重减去根所在子树的权重和即可。



**所以集中的精力解决的几个问题：**

1. 判断根节点的位置。比较$L[root] ， L[x] , R[x]$即可。
2. 如果根在x的子树里头， 找出其子树和。
   1. 倍增
   2. 对dfs序二分。 
      1. 实现方式是对sons的子树范围处理。详细看代码即可。

```cpp

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2E5 + 10;

int n , q ,  w[N];
vector<int> e[N];
vector<pair<int, int>> son[N];

int l[N] , r[N] , tot;
ll c[N];
void modify(int x , ll d) {
	for (; x <= n; x += x & -x) {
		c[x] += d;
	}
}
ll query(int x) {
	ll res = 0;
	for (; x; x -= x & -x) {
		res += c[x];
	}
	return res;
}
void dfs(int u , int fa) {
	l[u] = ++tot;
	for (auto v : e[u]) {
		if (v != fa) {
			dfs(v , u);
			son[u].emplace_back(l[v] , r[v]);
		}
	}
	r[u] = tot;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i < n; i++) {
		int u , v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1 , 0);
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
		modify(l[i] , w[i]);
	}

	int root = 1;
	while (q--) {
		int ch , x;
		cin >> ch >> x;
		if (ch == 1) {
			int y;
			cin >> y;
			modify(l[x] , y - w[x]);
			w[x] = y;
		} else if (ch == 2) {
			// 根节点的位置信息
			if (x == root) {
				cout << query(n) << "\n";
			}
			// 在里面
			else if (l[root] >= l[x] && r[root] <= r[x]) {
				auto seg = *(--upper_bound(son[x].begin() , son[x].end() , make_pair(l[root] , r[root])));
				cout << query(n) - (query(seg.second) - query(seg.first - 1)) << "\n";
			}
			// 在外面：
			else {
				cout << query(r[x]) - query(l[x] - 1) << "\n";
			}
		} else {
			root = x;
		}
	}
}
```









