#### $first$

- [The Tower of Babylon](https://vjudge.net/problem/UVA-437#author=0)

- 简介

  ```txt
  有n块砖头，关注长宽高属性。
  打算将它们叠成一个塔，限制如下。
  上面的石头对应的向下的面，宽和长，必须严格小于下面的石头的宽和长。
  问最多能叠多高？
  ```

- $solve$

  ```txt
  最暴力： 暴搜索，2^n 
  
  dag上的dp
  
  关于节点：
  对于一种砖头，抽象出三种状态，对于一种状态的选择意味着，哪一个面作为接触面以及它对高的贡献情况。
  这样我们定义了节点：
  点的属性有三种：   mi mx h. 
  关于边的建立：  mi_a>mi_b&&mx_a>mx_b。 那么a，就可以放在b的下面。此时a->b。
  
  建立图复杂度  n^2
  计算问题：    每一个点遍历一次：大概是n级别。
  ```

- [x] $code$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = -1;
struct node
{
    int mi, mx, h;
};
const int maxn = 40;

bool passed[maxn * 3]; //表示该点是否已经被探究过。
int k, n;
int a[maxn][3], f[maxn * 3];
node v[maxn * 3];
vector<vector<int>> g;

int dag_dp(int now)
{
    if (f[now])
        return f[now];
    for (auto to : g[now])
        f[now] = max(dag_dp(to), f[now]);
    return f[now] += v[now].h;
}

void solve()
{
    g.resize(3 * n + 3);
    for (int i = 1; i <= n; i++)
    {
        int temp = (i - 1) * 3;
        cin >> a[i][0] >> a[i][1] >> a[i][2];

        v[temp + 1].h = a[i][0];
        v[temp + 1].mi = min(a[i][1], a[i][2]);
        v[temp + 1].mx = max(a[i][1], a[i][2]);

        v[temp + 2].h = a[i][1];
        v[temp + 2].mi = min(a[i][2], a[i][0]);
        v[temp + 2].mx = max(a[i][2], a[i][0]);

        v[temp + 3].h = a[i][2];
        v[temp + 3].mi = min(a[i][1], a[i][0]);
        v[temp + 3].mx = max(a[i][1], a[i][0]);
    }
    //三个面分别标记，
    //三个相对应的一个标记为(i-1)*3

    for (int i = 1; i <= 3 * n; i++)
    {
        f[i] = 0;
        passed[i] = false;
        for (int j = 1; j <= 3 * n; j++)
        {
            if (v[j].mi < v[i].mi && v[j].mx < v[i].mx)
                g[i].push_back(j);
        }
    }

    int ans = -1;
    for (int i = 1; i <= 3 * n; i++)
        ans = max(ans, dag_dp(i));
    cout << "Case " << k << ": maximum height = " << ans << '\n';
    g.clear();
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t;
    while (cin >> n)
    {
        if (n)
            ++k, solve();
        else
            break;
    }
}
```

----

