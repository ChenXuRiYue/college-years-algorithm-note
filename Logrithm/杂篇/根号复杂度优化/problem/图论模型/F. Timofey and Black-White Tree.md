https://codeforces.com/contest/1790/problem/F

题意：

给定一颗有根树。

c0节点初始节点黑色：其余n-1个节点白色。

接下来进行n-1次染色。

每一次染色后，查询当前任意两个黑色节点距离的最小值。

$solve\quad one$

参考：

https://zhuanlan.zhihu.com/p/601326343

每一次染色。

然后向其它节点。更新它们离黑色节点的最小值。

如果本身就是黑色节点。那么dis[now]=0;

$dis[i]:当前节点离原有黑色节点的最小值；$

如果发现新增加的黑色节点对其它的节点的最短距离不再产生影响，于是就停止bfs。

##### 复杂度分析

复杂度取决于，最后更新的几个点之间与染色点之间的路径长度。

1. 如果一条线上已经有$\sqrt(n)$个节点。那么该线上的所有的节点的和其它染色节点的最小距离必然小于$\sqrt n$

于是这部分染色节点的贡献为$\sqrt n$

2. 如果少于$\sqrt n$的节点。那么每一个节点的贡献上界是$\sqrt n$
3. 处理每一个染色节点的贡献都是$\sqrt n*n$



#### $solve \quad two$

每一次染色，我们更新该点的祖宗。（子孙的白点，等到染色的时候更新。黑点的影响已经处理于当前的d[now]）

祖宗上的节点必然是是连接其它子树之间的纽带。当新增黑点出发遍历所有的祖宗节点时候。那么与任何黑色节点的联系。可以

在祖宗节点中挖掘。$dis[i]$了该便遍历点与其子树的节点的最小距离。

以后大抵上是看不懂的。模拟一下就可以理解了。



#### 生长思考

1. 打开思路的另外一种方式：想出一个看上去复杂度大的想法。然后分析这个模型，某一步的的最坏情况。发现事实上可以达到$n*\sqrt n或者 n 或者n*logn$
2. 更有趣的编写技巧：
   1. lambda表达式子的递归写法。对于接受函数值的变量的定义。
   2. 处理行末空格，统一输出的写法；"it ' s a strings"[id];

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;

void work(int testNo)
{
	int n;
	cin >> n;
	vector<int> c(n);
	for (int i = 0; i < n; i++)
	{
		cin >> c[i];
		c[i] --;
	}

	vector<vector<int>>g(n);
	for (int i = 1; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		x--; y--;
		g[x].push_back(y);
		g[y].push_back(x);
	}

	vector<int> pv(n, 0);
	function<void(int)> dfs = [&](int v)
	{

		for (auto i : g[v]) {
			if (i != pv[v]) {
				pv[i] = v;
				dfs(i);
			}
		}
	};
	dfs(0);

	int ans = n + 1;
	vector<int> d(n, n + 1);

	pv[0] = -1;
	for (int i = 0; i < n; i++)
	{
		int v = c[i];
		int val = 0;
		while (v >= 0 && val < ans)
		{
			ans = min(ans, val + d[v]);
			d[v] = min(d[v], val);
			v = pv[v];
			val++;
		}

		if (i > 0)cout << ans << " \n"[i == n - 1];
	}
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



