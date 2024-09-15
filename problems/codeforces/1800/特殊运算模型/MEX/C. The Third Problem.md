https://codeforces.com/contest/1699/problem/C

给定一个0.....n-1的排列。

定义一种运算 MEX( l , r )。为\[L,R]之内（0....n）最小的缺省值.

寻找和题目给定排列任意子区间下 MEX{l,r}相等的排列总数。

#### solve:

一步一步迁移计算等效数组。定义pos(i)为数字i中的位置。

先关注两个位置 0 ， 1显然不能变。如果0变了。

接下来看2，有两种情况。

- 0，1之内。可以在其中随便变化位置。
- 0，1之外，不可以改变位置。此时更新L，R

接下来看3同理向上面的情况进行处理。

计算贡献的方法是：如果当前检查的数字在{L，R}之内，就是R—L+1-i.用分步计算原理来理解。前面的所有数字都已经相乘上了该数字可以放的位置的所有选择。相当于一个数字一个数字，分n步的放。同时不可以影响到之前的选择。

所以对于第i步的总方案数是R—L+1-i.

#### code-

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
int mod = 1E9 + 7;
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n), pos(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        pos[a[i]] = i;
    }
    ll ans = 1, l, r;
    l = r = pos[0];
    for (int i = 1; i < n; i++)
    {
        if (pos[i] < l)
            l = pos[i];
        else if (pos[i] > r)
            r = pos[i];
        else
            ans = (ans * (r - l + 1 - i)) % mod;
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

