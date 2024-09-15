### 树上连通块

[树上连通块 - 题目 - Daimayuan Online Judge](http://oj.daimayuan.top/course/8/problem/274)

#### 题目简介

给定一个点，求出包含该点的连通块的个数，答案对$m(2 <= m <= 10^9)取模$。$1 <=n <= 10^5$

#### solve

1. 先考虑一个最简单的dp问题。只是求一个点。

   1. 定义状态$f_i$表示的是，以i为根的子树中连通块的个数（不包含节点数为0的情况）。

   2. 状态转移方程;
      $$
      f_i = (f_{son_1}+1)\times (f_{son_2}+1)\times....\times(f_{son_i}+1)
      $$

2. 

2. 考虑要求所有点：

   1. 考虑简单的换根dp.，每次换根计算出更新的dp值

      1. 暴力。$O(deg*deg)$  - > $O(n^2)$

      2. 对父亲的dp值直接 除法。（m不一定是质数，无法计算出逆元）

换根dp优化实现方法：
      1. 维护儿子的前缀积，后缀积。局部修改问题。直接考虑前后缀的情况。

下面是一些困惑：

1. 换根dp的顺序是什么？

​		随意找一个点作为根，发现不能处理父亲的情况。作为子树的贡献情况。换根的前提是，待选根的父亲作为子树的方案贡献已经求		出来。	

2. 换根的过程中 ， 节点的dp要出现什么变化？

​		 节点的dp不需要变化。再开一个dp2用来表示，该节点的父亲作为其余节点构成的子树的的父亲时 ， 其子树的连通块种类（不包···		括0的情况）。

​		 关于dp2的转移方程：	
​      1. 对于深度为1的节点，就是兄弟节点的（dp + 1）相乘。为什么要加一（因为可以考虑不选）。
​      2. 对于深度不为1的节点，就是兄弟节点乘上父亲的(dp2  +  1)。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E5 + 10;
int  n , mod;
vector<int> son[N];
ll dp[N] , dp2[N] , ans[N];

void dfs(int u) {
	dp[u] = 1;
	for (auto v : son[u]) {
		dfs(v);
		dp[u] = dp[u] * (dp[v] + 1) % mod;
	}
}

void dfs2(int u) {
	int m = son[u].size(); if (m == 0) return ;
	static ll pre[N] , suf[N];

	pre[0] = 1;
	for (int i = 1; i <= m; i++) {
		int v = son[u][i - 1];
		pre[i] = pre[i - 1] * (dp[v] + 1) % mod;
	}
	suf[m + 1] = 1;
	for (int i = m; i >= 1; i--) {
		int v = son[u][i - 1];
		suf[i] = suf[i + 1] * (dp[v] + 1) % mod;
	}
	for (int i = 0; i < m; i++) {
		int v = son[u][i];
		dp2[v] = pre[i] * suf[i + 2] % mod;
		if (u != 1) dp2[v] = dp2[v] * (dp2[u] + 1)  % mod;
	}
	for (auto v : son[u]) {
		ans[v] = (dp2[v] + 1) * dp[v] % mod;
		dfs2(v);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> mod;
	for (int i = 2; i <= n ; i++) {
		int x; cin >> x;
		son[x].push_back(i);
	}
	dfs(1);
	dfs2(1);
	ans[1] = dp[1];
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << '\n';
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

#### 生长思考

1. 换根dp也有一定的模式：
   1. 比方说，专门开一个dp2表示节点的父亲作为其余节点构成的根时，所定义的指标函数的解。
