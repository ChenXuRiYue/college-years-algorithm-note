https://ac.nowcoder.com/acm/contest/46810/K

给定一个图。

每次查询给定若干个节点。

每次查询中，从这些节点组成的子图中选取一条边。问最多可以选出多少条不同的边？

#### 20mins

$one$

每一次查询，子图做一个搜索。检查边的对经历的边增加一。

在最后做一次遍历，选出有多少种边。

$problems$

边数可能非常多。map，set都将会难以承受。事实上，只需要出现q次边就行。

1. 总数但与q次。那么就可以正常退出。



最终用了一个暴力的方法计算。但是超时了，最终的复杂度是O(q*E)

如果是完全图。复杂度将非常的大。



#### solve

根号分治：根号分治：将子问题划分成多个子问题。但是这个问题的规模是$\sqrt n$

根号分治的想法：

通过问题转换，将在无向图上的问题转换成一个有向图上的问题。

具体的建图方法是，度大的节点指向小的节点.

可以发现，每一个节点的出度都会小于$m*\sqrt m$

##### 生长思考

1. 为什么tle？算法复杂度没有正确估计。明确时间浪费的地方，（在这里一个节点的边的遍历重复，且累赘非常多。）

2. 虽然复杂度非常像根号分治。但是感觉上应该有一定的差别。应该是一个追求根号复杂度的优化的角度。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2E5 + 10;

bool in[N], passed[N];
int de[N];
vector<pair<int , int>> edge;
vector<vector<int>>g;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n , m , q;
    cin >> n >> m >> q;
    edge.resize(m);
    for (auto &i : edge)
    {
        cin >> i.first >> i.second;
        de[i.first]++;
        de[i.second]++;
    }
    g.resize(n + 1);
    for (auto i : edge)
    {
        if (de[i.first] > de[i.second])swap(i.first, i.second);
        g[i.first].push_back(i.second);
    }

    while (q --)
    {
        int k;
        cin >> k;
        vector<int>ku;
        for (int i = 1; i <= k; i++)
        {
            int x;
            cin >> x;
            in[x] = true;
            ku.push_back(x);
        }
        int ans = 0;
        for (int i : ku)
        {
            for (auto j : g[i])
            {
                if (in[j])ans ++;
            }
        }
        for ( auto i : ku)
            in[i] = false;
        cout << ans << '\n';
    }


}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWn;
* DON'T GET STUCK ON ONE APPROACH
*/
```

