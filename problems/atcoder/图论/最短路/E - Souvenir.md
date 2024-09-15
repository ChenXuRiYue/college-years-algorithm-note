https://atcoder.jp/contests/abc286/tasks/abc286_e

题意：

给出节点之间的相连情况：

要求：

任意两个城市之间的最短路，求出多种最短路中经历节点权重和的最大值。

##### solve

这里要求多源最短路，使用dijkstra算法来实现。

同时在更新最短路的过程中，维护最短路上节点权和的最小方案。



集中的困惑点是：

###### *problem_first*

**是否可以在记录最短路的过程中记录下这个当前方案的权重和？**

该问题和能否记录路径等效。从最小的状态开始。当d\[i][j]变化,维护w\[i][j]和p\[i][j]

最初状态下，是可以溯源的。

- ==**关于求最短路路径结构**==

	当任意一个状态下。某个状态发生改变。那么依然可以溯源。

	于是最短路计算完成之后。

- ==**关于求最短路的节点权重之和。**==

1. 是否所有同级别的最短路都会枚举到？

   转换问题—什么样的结构会被淘汰？什么样的结构有机会在更新中出现？

   关注最小的子问题：在计算k规模时候。k-1规模中的各个问题的劣解都已经被淘汰了。

   对于最短路结构。只有更优或者相等有机会将它淘汰。不存在更优，所以只有可能由同级别的进行淘汰。

   所以最优级别的结构都已经被枚举到了。

   同级别的不一定。

3. 如果1成立那么是否可以记录下最短路结构的节点之和？

  关于2与上述路径结构相似的证明角度。

##### ==生长思考==

- 动态规划；指导设计子问题，状态转移的方式就是关注模型，关注解空间。理解转移同样是关注最小状态，以及最小状态之后的递推.一般状态下的递归。

##### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int  oo = 1000 + 10;

const int N = 1E6 + 10;
int v[N];
int g[400][400];
ll ans[400][400];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
	}
	for (int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		for (int j = 0 ; j < n; j++)
		{
			if (s[j] == 'Y') {
				g[i][j + 1] = 1;
				ans[i][j + 1] = v[i] + v[j + 1];
			}
			else if (i == j + 1) {
				g[i][j + 1] = 0;
				ans[i][j + 1] = v[i] ;
			}
			else {g[i][j + 1] = oo;}
		}
	}

	for (int i = 1; i <= n; i++)
		ans[i][i] = v[i] ;

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				if (g[i][j] > g[i][k] + g[k][j])
				{
					g[i][j] = g[i][k] + g[k][j];
					ans[i][j] = ans[i][k] + ans[k][j] - v[k];
				}
				if (g[i][j] == g[i][k] + g[k][j])
				{
					ans[i][j] = max(ans[i][j], ans[i][k] + ans[k][j] - v[k]);
				}
			}

	int q;
	cin >> q;
	int t = 0;
	while (q--)
	{
		int l , r;
		cin >> l >> r;
		//cout << g[l][r] << '\n';
		if (g[l][r] == oo)
		{
			cout << "Impossible\n";
		}
		else
		{
			cout << g[l][r] << ' ' << ans[l][r] << '\n';
		}
	}
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

