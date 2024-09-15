# E. Speedrun

[Problem - E - Codeforces](https://codeforces.com/contest/1863/problem/E)

You are playing a video game. The game has $n$ quests that need to be completed. However, the $j$\-th quest can only be completed at the beginning of hour $h_j$ of a game day. The game day is $k$ hours long. The hours of each game day are numbered $0, 1, \ldots, k - 1$. After the first day ends, a new one starts, and so on.

Also, there are dependencies between the quests, that is, for some pairs $(a_i, b_i)$ the $b_i$\-th quest can only be completed after the $a_i$\-th quest. It is guaranteed that there are **no circular dependencies**, as otherwise the game would be unbeatable and nobody would play it.

You are skilled enough to complete any number of quests in a negligible amount of time (i. e. you can complete any number of quests at the beginning of the same hour, even if there are dependencies between them). You want to complete all quests as fast as possible. To do this, you can complete the quests in any valid order. The completion time is equal to the difference between the time of completing the last quest and the time of completing the first quest in this order.

Find the least amount of time you need to complete the game.

您正在玩一款视频游戏。游戏中有$n$个任务需要完成。但是，第$j$个任务只能在游戏日的第$h_j$个小时开始时完成。游戏日为$k$小时。每个游戏日的小时数为$0, 1, \ldots, k - 1$。第一天结束后，新的一天开始，依此类推。

此外，任务之间存在依赖关系，即对于某些任务对$(a_i, b_i)$来说，$b_i$/-个任务只能在$a_i$/-个任务之后完成。保证不存在**循环依赖**，否则游戏将是不可战胜的，也不会有人玩。

您有足够的技能在可以忽略不计的时间内完成任意数量的任务（也就是说，您可以在同一小时开始时完成任意数量的任务，即使它们之间存在依赖关系）。您希望尽快完成所有任务。为此，您可以按照任何有效顺序完成任务。完成时间等于完成最后一个任务的时间与按此顺序完成第一个任务的时间之差。

找出完成游戏所需的最少时间。

###  solve



### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 1E6 + 10;

void work(int testNo)
{
    int n , m , k;
    cin >> n >> m >> k;
    vector<int> h(n);
    for (int  i = 0; i < n; i++)
        cin >> h[i];
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u , v;
        cin >> u >> v;
        u-- , v--;
        g[u].push_back(v);
    }
    /*深度*/
    vector<int> dp(n);
    for (int i = 0; i < n; i++) {
        for (auto j : g[i]) {
            dp[j] = max(dp[j] , dp[i] + (h[j] < h[i]));
        }
    }
    vector<int> order(n);
    iota(all(order) , 0);
    sort(all(order) , [&](int x , int y) {
        return h[x] < h[y];
    });
    ll mx = 0;
    for (int i = 0; i < n; i++) {
        mx = max(mx , 1LL * dp[i] * k + h[i]);
    }
    /*然后进行一些更新：*/
    /*不断的跳跃式的选择一个起点， 并且对所有点进行小规模的更新；*/
    /*order[0]*/
    ll ans = INF;
    for (int i = 0; i < n; i++) {
        ans = min(ans , mx - h[order[i]]);
        vector<int> que;
        /*将x点放在第v天完成*/
        auto update = [&](int x , int v) {
            if (dp[x] < v) {
                dp[x] = v;
                que.push_back(x);
                mx = max(mx , 1LL * dp[x] * k + h[x]);
            }
        };
        /*将其放在第一天完成：*/
        update(order[i] , 1);
        for (int j = 0; j < sz(que); j++) {
            int u = que[j];
            for (auto v : g[u]) {
                update(v , dp[u] + (h[v] < h[u]));
            }
        }
    }
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

