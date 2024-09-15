# F. Unique Occurrences

[Problem - F - Codeforces](https://codeforces.com/contest/1681/problem/F)
给你一棵树，由 $n$ 个顶点组成。每条边上都写有一个整数值。
设 $f(v, u)$是顶点 $v$和顶点 $u$之间的简单路径边权中，只出现一次出现的值的个数。
计算所有顶点$v$和$u$对上的$f(v, u)$之和，使得$1 \le v \lt u \le n$.

$\large 1. SOLVE$ 

这种贡献问题，和一些求期望问题的角度相似，并非考虑一个结构整体的贡献情况： 比方说，并不是先枚举出一条具体的路径，然后详细探究路径上每一条边的贡献情况。而是从一条边开始看，在多少条路径中其单独存在：

考虑树形dp：将一条边分成上下两块：
1. 这两块一直延展，同时需要满足节点到该边，没有相同权值的边：
2. 根节点特殊处理：

**状态定义：**

$f_{i}$ 表示从i能够到达的点数： （要求不经过与i父亲相同的边：根特殊处理）

**状态转移方程：**

1. 枚举一个边时，寻找当前边上一个父亲同边权对应的u。 这里通过stk实现：

   $ans <- f_{u} * f_{v}$

2. 如果没有上述类型的父亲节点，就看根节点： 维护一个$root_i$ 对根节点特殊处理：

   对根结点记录的信息：$root_{i}$ 假定根节点与父亲连接了一条权值为i的边。根节点向下延展可以到达的点个数。

$\large 2.CODE$

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;;
const ll INF = 1E18 + 7;
const int N = 5E5 + 10;

vector<pair<int , int>> g[N];

/*
f[i] , 不经过u到父亲的边 ， 可以到达的点的总数：
计算方法：
维护几个关键信息：
1. 整一个子树的带大小：
2. 上一个相遇的同颜色的边的点； （这个可以通过栈维护信息：）

2. 统计答案的方法：
1. 同理，枚举到一个边的时候，直接做即可》

细节 ： 注意1节点（根是特殊的，其一定在栈中：）
*/
// 对0的处理
// 点到达子树中 ， 只经过与父亲相同的点颜色一次的点数： 对根使用root特判：
int root[N] , f[N] , sz[N];
// 记录各种颜色的栈： 方便找到上一个同色边。
stack<int> stk[N];

void dfs(int u , int fa , int PreCol) {
    sz[u] = 1;
    stk[PreCol].push(u);
    for (auto [v , w] : g[u]) {
        if (v == fa) continue;
        dfs(v , u , w);
        sz[u] += sz[v];
    }
    stk[PreCol].pop();
    f[u] += sz[u];
    if (stk[PreCol].empty()) {
        root[PreCol] -= sz[u];
    } else {
        f[stk[PreCol].top()] -= sz[u];
    }
}

ll ans;

void dfs1(int u , int fa , int PreCol) {
    if (stk[PreCol].empty()) {
        ans += 1LL * f[u] * root[PreCol];
        // cout << ans << "\n";
    } else {
        int v = stk[PreCol].top();
        ans += 1LL * f[u] * f[v];
        // cout << ans << "\n";
    }
    stk[PreCol].push(u);
    for (auto [v , w] : g[u]) {
        if (v == fa)  continue;
        dfs1(v , u , w);
    }
    stk[PreCol].pop();
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u , v , w;
        cin >> u >> v >> w;
        g[u].push_back({v , w});
        g[v].push_back({u , w});
    }
    dfs(1 , 0 , 0);
    for (int i = 1; i <= n; i++) {
        root[i] += sz[1];
        // cout << root[i] << "\n";
    }
    // for (int i = 1; i <= n; i++) {
    //     // cout << f[i]  << " \n"[i == n];
    //     cout << root[i] << " \n"[i == n];
    // }
    // for (int i = 1; i <= n; i++) {
    //     cout << f[i]  << " \n"[i == n];
    //     // cout << root[i] << " \n"[i == n];
    // }
    root[0] = 0;
    dfs1(1 , 0 , 0);
    cout << ans << "\n";
}
```

