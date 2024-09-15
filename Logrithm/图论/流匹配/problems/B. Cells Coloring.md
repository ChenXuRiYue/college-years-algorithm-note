# B. Cells Coloring

[Problem - B - Codeforces](https://codeforces.com/gym/104077/problem/B)

You are given an $n \times m$ grid. Some of the cells are obstacles, the others are empty. Choose a non-negative integer $k$ and color all empty cells with $k+1$ colors $0, 1, 2, \ldots k$. You can not color two cells in the same row or same column with the same **non-zero** color.

You are given two non-negative integers $c$ and $d$. For a coloring plan, define $z$ as the number of the cells with color $0$. Define the cost of the plan is $ck+dz$.

Find the minimum cost.

**Input**

The first line contains four integers $n$, $m$ ($1\leq n, m\leq 250$), $c$ and $d$ ($0\leq c, d\leq 10 ^ 9$).

The $i$\-th line of the next $n$ lines contains a string of $m$ characters. The $j$\-th character is '\*' if the cell in the $i$\-th row and the $j$\-th column is an obstacle. The $j$\-th character is '.' if the cell in the $i$\-th row and the $j$\-th column is empty.

### solve

1. 考虑枚举k ， 于是问题转变成了对于枚举的k，使得被染色的点数目最大。

2. 考虑具体的k ， 解决染色点数目最大的问题。

**网络流解法：**

1. 对每一行抽象出一个节点。
2. 对每一列抽象出一个节点。
3. 抽象出源点汇点。

s -> 向每一行建立一条容量为k的边。
每一列的点 -> 向t建立一条容量为k的边。
行点向对应行上的点连1的流量。
点向对应列点连1的流量。
发现，网络流中的每一个流动方案，都可以保证解的合法性。并且每一个合法方案都可以表达成网络中的一个具体流动方案。

网络流中的每一个流动方案，都可以保证解的合法性。
证明：
1. 确定了了一个每行每列染色数目合法的最大染色方案之后。
   必然有一种分配方案。

官方答案以及证明：

若我们已经确定了哪些格子不染 $0$，构建一个二分图，若 $(i,j)$ 不染 $0$ 则连边 $(i,j')$。

引理：$k=\max_x deg_x$。其中 $x$ 是任意左部点或右部点。

证明：考虑增量 + 调整。每次插入一条边 $(x,y')$ 并给其染色，由于 $deg_x\leq k$，必然能找到一个颜色 $u$ 使得 $x$ 满足限制。若此时 $y'$ 不满足限制，则问题转化为将原先 $y'$ 相邻的颜色为 $u$ 的边修改为一个 $y'$ 满足限制的颜色 $v$。若此时原先 $y'$ 相邻的颜色为 $v$ 的边的另一端 $z$ 又不满足限制，我们再要求与 $z$ 相邻的颜色为 $v$ 的边的颜色改成 $u$。发现问题的形式和之前等价，递归处理。一旦不存在后继边或得到偶环即找到了方案。由于图是二分图，这样下去不会得到奇环，于是必定能做到。

于是我们可以枚举 $k$，接下来就是删掉最少的边使得 $\max_x deg_x\leq k$。这是一个每个点可以匹配至多 $k$ 个点的二分图最大匹配，直接网络流即可。一个有效的优化是，我们可以以升序枚举 $k$，这样每次可以在 $k-1$ 的残量网络上直接加容量。

（虽然我不懂，但是他是正确的。）

**如果每一次重新调整流量。跑若干次网络流，那么常数将会比较大，会T掉**
利用残量网络进行调整：（一个经典地trick。如果考虑增加的流量，怎么基于之前。）可以中途加，这是没有影响的。因为网络流中最基本的想法是，能选就选。可以将图等效为其它图）相当于加多了一个点，一条边。被加的流量代表的边，优先级非常低。（或者随机性问题，最后才被访问。）

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) (x).begin(),(x).end()
#define int ll

const ll INF = 1LL << 60;

const int V = 1010;
const int E = 101000;
template<typename T>
struct FlowGraph {
	int s, t, vtot;
	int head[V], etot;
	int dis[V], cur[V];

	// 邻接表存储。
	// 这样可以方便建立反边^1。

	struct edge {
		int v, nxt;
		T f;
	} e[E * 2];
	void addedge(int u, int v, T f) {
		e[etot] = {v, head[u], f}; head[u] = etot++;
		e[etot] = {u, head[v], 0}; head[v] = etot++;
	}

	bool bfs() {
		for (int i = 1; i <= vtot; i++) {
			dis[i] = 0;
			cur[i] = head[i];
		}
		queue<int> q;
		q.push(s); dis[s] = 1;

		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = head[u]; ~i; i = e[i].nxt) {
				if (e[i].f && !dis[e[i].v]) {
					int v = e[i].v;
					dis[v] = dis[u] + 1;
					if (v == t) return true;
					q.push(v);
				}
			}
		}
		return false;
	}

	T dfs(int u, T m) {
		if (u == t) return m;
		T flow = 0;
		for (int i = cur[u]; ~i; cur[u] = i = e[i].nxt)
			if (e[i].f && dis[e[i].v] == dis[u] + 1) {
				T f = dfs(e[i].v, min(m, e[i].f));
				e[i].f -= f;
				e[i ^ 1].f += f;
				m -= f;
				flow += f;
				if (!m) break;
			}
		if (!flow) dis[u] = -1;
		return flow;
	}

	T dinic() {
		T flow = 0;
		// 从起点开始bfs，确定分层图。 然后开始增广。
		//
		while (bfs()) flow += dfs(s, numeric_limits<T>::max());
		return flow;
	}

	void init(int s_, int t_, int vtot_) {
		s = s_;
		t = t_;
		vtot = vtot_;
		etot = 0;
		for (int i = 1; i <= vtot; i++) head[i] = -1;
	}
};

FlowGraph<ll> g;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int  n , m , c , d;
	cin >> n >> m >> c >> d;
	int s = n + m + 1 , t = n + m + 2;
	g.init(s , t , t);
	vector<int> a(n + 1) , b(m + 1);

	for (int i = 1; i <= n; i++)
		g.addedge(s , i , 0);
	for (int i = 1; i <= m; i++)
		g.addedge(i + n , t , 0);

	int tot = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char s; cin >> s;
			if (s == '.') {
				tot++;
				a[i]++;
				b[j]++;
				g.addedge(i , n + j , 1);
			}
		}
	int mx = 0;
	int ans = INF;
	mx = max(*max_element(all(a)) , *max_element(all(b)));

	int z = 0;
	for (int k = 0; k <= mx; k++) {
		if (k) {
			for (int i = 0; i < n + m; i++) {
				g.e[i * 2].f++;
			}
		}
		z += g.dinic();
		// cout << k << " " << z << "\n";
		ans = min(ans , c * k + d * (tot - z));
		// cout << ans << "\n";
	}
	cout << ans << "\n";
}
```









