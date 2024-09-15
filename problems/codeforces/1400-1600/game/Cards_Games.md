#### cards_game

[cards_game](https://codeforces.com/problemset/problem/1739/C)

- 问题简介

```txt
偶数张卡牌，标记为1.....n;
平均分给两个人。
第一轮，a先打，b接。
如果对手不能接，对手输了。
如果安然度过，就变为对手先打。
每个人，都采取最优策略。
问a赢，b赢，平手的牌组。
```

#### 分析

```
最优策略总是打出最大的牌。
枚举a从第几轮赢。
自己的思路是：
第i轮赢
那么在采取最优的策略之下，前面几轮的牌分配已经确定。
如果第一轮就赢了。那么最大牌必须在手
如果第三轮赢了。  出牌是 n-1 -> n ,, -> n-2,,  (只要保证n-2在手即可。n-3在手或者n-4在手，或者两个都在手都可以在第三轮赢。否则继续向下打牌。第三轮赢不了)
如果第五轮赢   必须在手 n-1,n-2,n-4,n-5 n-6.如果不在手，在前面的过程中就输。

8 7 6 5 4 3 2 1
```

#### code

``` cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;

const ll N = 2020, mod = 998244353;

ll c[N][N]; //相当于数学中的组合公式Cab（数学公式不知如何插入le...）

void init()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            if (!j)
                c[i][j] = 1;
            else
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod; //递推公式
}

void solve()
{
    int n;
    cin >> n;
    if (n == 2)
    {
        cout << 1 << ' ' << 0 << ' ' << 1 << '\n';
        return;
    }
    ll ans = 0;
    ans += c[n - 1][n / 2 - 1];
    for (int i = 3; i <= n / 2; i += 2) //第几轮赢。//只可能在先手轮赢
    {
        ans += c[n - (i - 2) * 2 - 3][n / 2 - i] * 2 + c[n - (i - 2) * 2 - 3][n / 2 - i - 1];
        ans %= mod;
    }
    cout << ans << ' ' << (c[n][n / 2] - ans + mod - 1) % mod << ' ' << 1 << '\n';
}
int main()

{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t;
    cin >> t;
    init();
    while (t--)
        solve();
}
```

#### 生长思考

- 发现问题：漏了，详细到数据检查情况。

