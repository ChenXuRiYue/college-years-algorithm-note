#### 概念简介

借鉴：

[2-SAT - OI Wiki (oi-wiki.org)](https://oi-wiki.org/graph/2-sat/)

#### 背景
SAT是适用性的简称。一般形式为k-SAT.但是当k>2时。建模较麻烦，且复杂度比较高。
#### 简述
给定N个布尔变量。若干个或表达式约束。
给每一表达式中的一对变量分配真假。求符合约束的一组解。

2-SAT，简单的说就是给出 n 个集合，每个集合有两个元素，已知若干个 <a,b>，表示 a 与 b 矛盾（其中 a 与 b 属于不同的集合）。然后从每个集合选择一个元素，判断能否一共选 n 个两两不矛盾的元素。显然可能有多种选择方案，一般题中只需要求出一种即可。

问题背景往往是n个集合中，每个集合选一个。当然可以选两个。但是如果选两个必然存在每个集合选一个的一种方案。（贪心）

#### 建模方法

1. 二元布尔表达式都可以转换成或表达式（离散数学中的内容。）

2. 建图：

   1. 枚举假设，变量的情况。比方说$x_1=1，x_2 = 0$至少一个成立

   2. 关注两种确定的组合：
      $$
      x_1 = 0 => x_2 = 1\\
      $$

      $$
      x_2=1=>x_1 = 1\\
      $$

      1. 为什么要关注这两种假设？两个都成立的假设不考虑？
      2. 因为我们使得变量为真，有数量上的限制。我们追求用尽量少变量为真的数量，得到一组解。

    3. 根据上述描述建立边。。对每一个变量拆成两个点。

3. 图上性质。

   1. 选择了一个点作为方案结构。不能再选择与之矛盾的解。
   2. 选择了一个点作为方案结构。其可达的点都要选择。


#### 求解方法

1. 判断是否有解。

   根据规则：只要对每一个变量分配了真假。并且不出现矛盾。那么就是有解。可知当且仅当，不存在相矛盾的两个点（$x和！x$）在同一个连通分量中。

2. 具体构造出一组解。

   1. 先缩点。然后判断是否可以构造出一组解。
   2. 在缩完点的dag上，任选一个拓扑序。从拓扑序靠后的开始选择。
   3. 关于1，2的证明。
      1. 首先关注，几种出现矛盾的可能情况。选择了$x_i,x_i=>....=>!x_i$同时选了两个。但是我们优先选择拓扑序小的。就不会先选到$x_i$
      2. 从拓扑序小的开始选择。每一条边都有一个反边。也就是具有了一种对称性。缩点都有其对称的内容。就是缩点内部涉及了相同类型的变量。所以考察一个缩点。
         1. 如果对称的缩点已经选择了。那么这个缩点就不必再选了。
         2. 如果对称的缩点还没有选择。可以保证子孙都已经被选择，没有空隙。观察图的结构。可以发现它是具有点的关于边的对称性的。如果$fa$子孙中同时出现了出现了$x_i,!x$。那么也必然出现了$!fa$。矛盾。


#### 例题1 满汉全席

[P4171 [JSOI2010\] 满汉全席 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P4171)

##### solve

问题就是给定若干对。求一个解，使得其中的元素至少存在一个。典型的2—SAT问题。
1. 约束定义
    对于每一个变量有状态就是为h和为m。类比true   和   false.  定义  m为 0 状态。 h为1状态。

2. 建模

  选择一个取反操作。然后指向另一个即可。

3. 缩点

  tarjan。一步到位。因为不用求一个具体的结构。所以不需要记录拓扑序。（或者在tarjan过程中直接求解。）

4. 利用bel数组判断有无解即可。

##### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;

void work(int testNo)
{
	int n , m;
	cin >> n >> m;

	vector<vector<int>> e(2 * n);

	for (int i = 0; i < m; i ++) {
		char a , b;
		int u , v;
		cin >> a; cin >> u; cin >> b; cin >> v;
		u--; v--;

		u = u * 2 + (a == 'h');
		v = v * 2 + (b == 'h');
		e[u ^ 1].push_back(v);
		e[v ^ 1].push_back(u);
	}

	vector<int> dfn(2 * n) , low(2 * n) , bel(2 * n) , ins(2 * n);
	int id = 0;
	stack<int> stk;
	int cnt = 0;

	function<void(int)> dfs = [&](int u) {
		dfn[u] = low[u] = ++id;
		ins[u] = true;
		stk.push(u);

		for (auto v : e[u]) {
			if (!dfn[v]) dfs(v);
			if (ins[v]) low[u] = min(low[v] , low[u]);
		}

		if (low[u] == dfn[u]) {
			++cnt;
			while (true) {
				int v = stk.top();
				stk.pop();
				ins[v] = false;
				bel[v] = cnt;
				if (v == u) break;
			}
		}
	};

	for (int i = 0; i < 2 * n; i++) {
		if (dfn[i] == 0) dfs(i);
	}

	for (int i = 0; i < 2 * n; i++) {
		if (bel[i ^ 1] == bel[i]) {
			cout << "BAD\n";
			return;
		}
	}

	cout << "GOOD\n";
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/

```

##### 生长思考。

1. 拆点技巧。乘2。利用数字的第一位信息区分。
2. 用lambda表达式，使码风更简洁，清晰。
   1. 可能传引用调用，局部调用速度更快。
   2. 更利于封装。模板优化。

#### 例题二 奶牛议会。

每个奶牛给出两个方案的决定。要求两个变量至少一个成立才为可行解。

##### 问法变化：

1. 考察所有可行解。研究，一个议案的情况：所有可行方案都通过 。所有方案不通过。部分方案通过，部分方案不通过。三种情况。

##### solve

1. 是否存在解的问题，求强连通分量即可。
2. 基于某一个提案，分析所有方案结构
   1. 假设只能为真，看是否有解。 即给定一条!x->x
   2. 假设只能为假，是否有解。 同一引入 x->!x
3. 分析出结论，如果x可达!x，那么不存在x的方案。所以此时为‘N’反之如果$!x$可达x. ， 那么不存在！x的提案，

##### 关于实现

1. 对于第3点。求出每一个点的可达情况。不可以使用树形dp。因为状态与状态间会互相影响。最多通过bitset来做一个常数优化。类似的问题：[清楚姐姐学排序.md](清楚姐姐学排序.md) 



##### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;


void tarjan()
{
	int n , m;
	cin >> n >> m;

	//建图
	//情景不同数组可能开更大。注意
	vector<vector<int>> e(n * 2);

	for (int i = 0; i < m; i ++) {
		/*处理边输入*/
		int a[2];
		char s[2];
		cin >> a[0] >> s[0] >> a[1] >> s[1];
		a[0] --;
		a[1] --;
		a[0] = a[0] * 2 + (s[0] == 'N');
		a[1] = a[1] * 2 + (s[1] == 'N');
		e[a[0] ^ 1].push_back(a[1]);
		e[a[1] ^ 1].push_back(a[0]);
	}

	vector<int> dfn(n * 2) , low(n * 2) , bel(n * 2) , ins(n * 2);
	int id = 0;
	stack<int> stk;
	int cnt = 0;

	vector<vector<int>> ssc(n * 2);

	function<void(int)> dfs = [&](int u) {
		dfn[u] = low[u] = ++id;
		ins[u] = true;
		stk.push(u);

		for (auto v : e[u]) {
			if (!dfn[v]) dfs(v);
			if (ins[v]) low[u] = min(low[v] , low[u]);
		}

		if (low[u] == dfn[u]) {
			++cnt;
			vector<int> c;
			while (true) {
				int v = stk.top();
				stk.pop();
				ins[v] = false;
				bel[v] = cnt;
				if (v == u) break;
			}
			ssc.push_back(c);
		}
	};

	for (int i = 0; i < 2 * n; i++) {
		if (dfn[i] == 0) dfs(i);
	}

	for (int i = 0; i < n; i++) {
		if (bel[i * 2 + 1] != bel[i * 2]) {
			cout << "IMPOSSIBLE\n";
			return ;
		}
	}
	vector<int> vis(n * 2);
	function<void (int)> dfs2 = [&](int u) {
		vis[u] = true;
		for (auto v : e[u]) {
			if (!vis[v])dfs(v);
		}
	};
	string ans;
	ans.resize(n + 1);
	for (int i = 0; i < n; i++) {
		fill(vis.begin() , vis.end(), 0);
		dfs2(i * 2);
		ans[i] = '?';
		if (vis[i * 2 + 1]) {
			ans[i] = 'N';
		}
		fill(vis.begin(), vis.end() , 0);
		dfs2(i * 2 + 1);
		if (vis[i * 2]) {
			ans[i] = 'Y';
		}
	}
	cout << ans << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	tarjan();
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```



