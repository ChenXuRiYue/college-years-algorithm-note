https://codeforces.com/contest/1671/problem/D

outputstandard输出
给你一个n个整数的序列a1 a2…an。你也有x个整数1 2…x。

您需要将每个额外的整数插入到序列a中。每个整数可以插入到序列的开头，序列的末尾，或序列的任何元素之间。

结果序列a '的分数是其中相邻元素的绝对差值之和$\sum_{i=1}^{n+x-1}|a '_ i - a '_{i+1}|)$。

结果序列a '可能的最小分数是多少?



#### 25mins:

啥也想不出来

#### solve

富有启发性的一道构造题。

首先我们思考一种优秀的构造方式。我们每放进一个，类比零点定理，发现一低一高被夹住时，在原有的基础上，贡献为0.

（注意特殊判断放在数组两边的情况。）

发现一个段之内，如果出现了一个小于当前的元素，一个大于当前的元素。则必定存在两个元素把它们给夹住。使得它们的贡献为0；

综上意味着，我们只需要放好1,x.其它元素的贡献都将会是0.

所以我们直接枚举这一些位置即可。

普通的元素放置，其贡献为$2*|a[i]-aim|$



还有一个疑惑点就是，1的位置摆放，是否会影响到x的贡献？

如果1放在了两边，那么x不可能放在同侧，另一端的结果会更优。

如果1放在中间，那么放在1后面是选择的下限（当所有元素都为1的时候才做的选择。）因此只需要考虑部分即可。

#### code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;

int a[maxn];

void solve()
{
    int n, x;
    cin >> n >> x;
    int mx = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    ll ans = 0;
    for (int i = 1; i < n; i++)
        ans += abs(a[i] - a[i - 1]);
    // 首先把1放好。
    int mi = 1e9 + 10;
    mi = min(mi, a[0] - 1);
    mi = min(mi, a[n - 1] - 1);
    for (int i = 1; i < n - 1; i++)
        mi = min(mi, (a[i] - 1) << 1);
    ans += mi;
    if (mx < x)
    {
        mi = abs(a[0] - x);
        mi = min(mi, x - a[n - 1]);
        for (int i = 0; i < n - 1; i++)
            mi = min(mi, (x - a[i]) << 1);
        ans += mi;
    }
    cout << ans << '\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        solve();
}
```

#### 生长思考

- 最终要的是发现上面的2个规律
  - （高低之间必然丝滑，从而砍掉非常大一部分的解空间。）
  - 关于1，x的位置
  - 插入一个元素的影响是什么。我们关注量，做进一步计算上的优化。