# D. The way home

[Problem - 1801D - Codeforces](https://codeforces.com/problemset/problem/1801/D)
The famous magician Borya Budini traveled through the country $X$, which consists of $n$ cities. However, an accident happened, and he was robbed in the city number $1$. Now Budini will have a hard way home to the city number $n$.
He's going to get there by plane. In total, there are $m$ flights in the country, $i$\-th flies from city $a_i$ to city $b_i$ and costs $s_i$ coins. Note that the $i$\-th flight is one-way, so it can't be used to get from city $b_i$ to city $a_i$. To use it, Borya must be in the city $a_i$ and have at least $s_i$ coins (which he will spend on the flight).
After the robbery, he has only $p$ coins left, but he does not despair! Being in the city $i$, he can organize performances every day, each performance will bring him $w_i$ coins.
Help the magician find out if he will be able to get home, and what is the minimum number of performances he will have to organize.

著名魔术师博里亚-布迪尼游历了由$n$个城市组成的$X$个国家。然而，意外发生了，他在$1$号城市被抢劫了。现在，布迪尼将艰难地回到$n$号城市。
他将乘坐飞机到达那里。全国总共有$m$个航班，$i$个从$a_i$号城市飞往$b_i$号城市，需要花费$s_i$个硬币。请注意，$i$次飞行是单程的，因此不能用来从城市$b_i$前往城市$a_i$。要使用它，Borya 必须在城市 $a_i$，并且至少有 $s_i$个硬币（他将把这些硬币花在航班上）。

抢劫之后，他只剩下 $p$个硬币，但他并没有绝望！在城市里 $i$，他可以每天组织演出，每场演出都会给他带来 $w_i$个硬币。

帮助魔术师找出他是否能够回家，以及他最少需要组织多少场演出。

### solve

**状态定义：**
$f_{i ,j}$: 每一个状态用一个{sum , remain} 表示 表示当前在i节点中，途中经过的权值最大点为j节点问题下，的最优可行状态：最优性的定::

1. 由于演出可等效延后执行： 同时最终的解要求的是最小状态。因此记录对于所有可行，记录其最小步数即可。
2. 显然步数相同的情况下记录的是remain的最大值：

**状态转移方程：**
类似于dijkstra的思想，不断盖棺定论（即某个状态不可能被更新时，就取出去更新其它状态。逐步求出所有的状态；）
**初始化：**
1. $f_{1 ,1} = <0 , p>$
2. 其它的初始化定义为：<inf , inf> 表示还没有记录方案；
#### 实现关键：
**使用优先队列：**

1. 定义优先级的问题：
----
**把握更新顺序： **

强调将记录的状态其实是路径：：不断取出一些最优路径来更新。
1. 保证sum越小越优。
2. sum相同情况下， remain越大越优。

求解状态：
$f_{n , x}$ 枚举x不断统计：

### code

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define int ll

const ll inf = 1E18 + 7;
const int N = 1010;

struct path {
	int sum;
	ll remain;
};
struct state {
	int u;
	int best;
	path x;
};

bool operator==(const path &a , const path &b) {
	/*tie语法应用：*/
	return tie(a.sum , a.remain) == tie(b.sum , b.remain);
}

bool operator<(const path &a , const path &b) {
	// 小优先
	if (a.sum != b.sum) return a.sum < b.sum;
	// 大优先：
	return a.remain > b.remain;
}
bool operator>(const path &a , const path &b) {
	return not(a < b);
}
bool operator<(const state&a  , const state&b) {
	return tie(a.x , a.best , a.u) < tie(b.x , b.best , b.u);
	// return a.x < b.x;
}
bool operator>(const state&a , const state&b) {
	return not(a < b);
}

vector<pair<int, int>> g[N];
path f[N][N];
int w[N];
/*
1
4 1 2
1 1 1 1
1 3 2

1
4 4 2
7 4 3 1
1 2 21
3 2 6
1 3 8
2 4 11
*/
void work(int testNo)
{
	int n , m , p;
	cin >> n >> m >> p;
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
		g[i].clear();
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			f[i][j] = {inf , 0};

	for (int i = 0; i < m; i++) {
		int u , v , cost;
		cin >> u >> v >> cost;
		g[u].push_back({v , cost});
	}
	priority_queue<state , vector<state> , greater<state>> que;
	que.push({1 , 1 , {0 , p}});

	f[1][1] = {0 , p};
	while (que.size()) {
		// cout << ++cunt << "\n";
		auto cur = que.top(); que.pop();
		auto X = cur.x;
		int u = cur.u , best = cur.best;
		if (not (f[u][best] == X)) continue;
		/*转移：*/
		// cout << X.sum << " " << X.remain << "\n";
		for (auto [v , cost] : g[u]) {
			// 计算到达当前状态使用的代价：
			auto nxt = cur;
			auto& Y = nxt.x;
			if (Y.remain < cost) {
				int d = (cost - Y.remain + w[best] -  1) / w[best];
				Y.sum += d;
				Y.remain += d * w[best];
			}
			Y.remain -= cost;

			if (w[best] < w[v]) nxt.best = v;
			nxt.u = v;

			if (Y < f[v][nxt.best]) {
				f[v][nxt.best] = Y;
				que.push(nxt);
			}
		}
	}
	int ans = inf;
	for (int i = 1; i <= n; i++) {
		ans = min(ans , f[n][i].sum);
	}
	if (ans == inf) ans = -1;
	cout << ans << "\n";
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```