# D. Survey in Class

[Problem - D - Codeforces](https://codeforces.com/contest/1834/problem/D)

Zinaida Viktorovna has $n$ students in her history class. The homework for today included $m$ topics, but the students had little time to prepare, so $i$\-th student learned only topics from $l_i$ to $r_i$ inclusive.

At the beginning of the lesson, each student holds their hand at $0$. The teacher wants to ask some topics. It goes like this:

-   The teacher asks the topic $k$.
-   If the student has learned topic $k$, then he raises his hand by $1$, otherwise he lower it by $1$.

Each topic Zinaida Viktorovna can ask **no more than one time**.

Find the maximum difference of the heights of the highest and the lowest hand that can be in class after the survey.

Note that the student's hand **can go below $0$**.

Zinaida Viktorovna 的历史课上有$n$名学生。今天的作业包括$m$个题目，但学生们没有多少时间准备，所以$i$个学生只学了$l_i$到$r_i$（含】）的题目。

上课伊始，每个学生都把手放在$0$处。老师想问一些问题。是这样的

- 老师提出题目$k$。
- 如果学生已学过题目$k$，则举手$1$，否则举手$1$。

每个话题季娜达-维克托罗夫娜可以提问**次，但不得超过一次**。

找出调查后全班最高和最低的手的高度之差的最大值。

注意，学生的手**可以低于$0$**。

## solve

**基本的观察：**

枚举某个学生得分为最大： 则对于该类解的最优策略必定是，将该学生会的所有题目问一遍。



## code

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define fi first
#define se second

const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 1E6 + 10;

/*
1
4 8
2 6
4 8
2 7
1 5

1
3 3
1 3
2 3
2 2
*/
void work(int testNo)
{
    int n , m;
    cin >> n >> m;
    vector<pair<int , int>> inter(n);
    int mx_l = 0 , mi_r = m + 1 , mi_len = m + 1;
    for (int i = 0; i < n; i++) {
        cin >> inter[i].fi >> inter[i].se;
        mx_l = max(mx_l , inter[i].fi);
        mi_r = min(mi_r , inter[i].se);
        mi_len = min(mi_len , inter[i].se - inter[i].fi + 1);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int l = inter[i].fi , r = inter[i].se;
        int len = r - l + 1;
        ans = max(ans , len - max(0 , mi_r - l + 1));
        ans = max(ans , len - max(0 , r - mx_l + 1));
        ans = max(ans , len - mi_len);
    }
    cout << ans * 2 << "\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++)work(i);
}
```

