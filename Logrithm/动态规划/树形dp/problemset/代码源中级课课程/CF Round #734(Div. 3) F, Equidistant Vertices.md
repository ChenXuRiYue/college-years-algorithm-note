[Problem - F - Codeforces](https://codeforces.com/contest/1551/problem/F)

#### 简介

考察节点数量大小为k ， 并且节点之间距离相等的若干子集。计算出方案的总个数。

#### solve

考察方案。发现所有的合法方案。其实就是每一个节点到一个中心点的距离相等。

1. 考虑枚举这一个中心点。重新构造一棵树。

每一个方案中 ， 每一颗子树 只能选取一个点。并且深度相同。

2. 枚举选取点的深度。



==状态设计==

$dp_{i , j}$ 表示从前i个子树中，选取j个节点的方案个数。

==状态转移方程==
$$
dp_{i， j} = dp_{i - 1,j} + dp_{i - 1 , j}*sum[v]
$$
其中$sum[v]$表示 v 为根的子树中深度为枚举深度的节点数量。

==时间复杂度分析==

枚举根节点的花费： $N$

求出各个子树某深度的节点个数; $N*N$

枚举深度 $N$

每一次枚举儿子： $N$

每一次更新dp数组：$K$

综上，看上去，总的复杂度是$O(N^3k)$

但是事实上，儿子的深度的值域和儿子的个数有关。如果子树的某深度下的节点树为0.不需要更新。

每一次枚举儿子，合并更新的次数，应该是。每个子树中，每个深度处理一次。

所以总的次数是$N$次

所以总的复杂度为$O(N^2k)$

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E2 + 10;
const ll mod = 1E9 + 7;

ll sum[N][N];
int dep[N];
vector<int> g[N];
int n , k , w;
ll dp[N];

void dfs(int u , int  par ) {
    for (int i = 0; i <= n; i++)sum[u][i] = 0;
    sum[u][dep[u]] ++ ;
    for (auto v : g[u])if (v != par) {
            dep[v] = dep[u] + 1;
            dfs(v , u);
            for (int i = 1; i <= n; i++) {
                sum[u][i] += sum[v][i];
            }
        }
}

ll rundp(int u) {
    for (int i = 0; i <= k; i++) dp[i] = 0;
    dp[0] = 1;
    for (auto v : g[u]) {
        if (sum[v][w] == 0)continue;
        for (int i = k; i >= 1; i--) {
            dp[i] = (dp[i] + dp[i - 1] * sum[v][w]) % mod;
        }
    }
    return dp[k];
}


void work(int testNo)
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int x , y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    ll ans = 0;
    if (k == 2) {
        cout << 1LL * n*(n - 1) / 2 << '\n';
        return ;
    }
    for (int i = 1; i <= n; i++) {
        dep[i] = 0;
        dfs(i , 0);
        // cout << "test: " << i << '\n';
        // for (int j = 1; j <= n; j ++)
        //     cout << sum[i][j] << " \n"[j == n];

        for (int j = 1; j <= n; j ++) {
            w = j;
            ans = (ans + rundp(i)) % mod;
        }
    }
    cout << ans << '\n';
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++)work(i);
}
```

