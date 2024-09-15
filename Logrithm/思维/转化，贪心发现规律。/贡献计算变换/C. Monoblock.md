https://codeforces.com/contest/1715/problem/C

#### solve

将计算从两个角度每一个断点的角度进行贡献。

两两不同的分界点处，对ans的贡献为：\[1....i][i+1....n]，断点存在于这一些区间之中，都产生了1的贡献。

这样优化了计算的结构之后，可以非常容易处理修改问题。



量计算角度优化。反过来看，每个具有该断点的段因为这个断点产生1.总体上来看。反过来看，1个断点对包含它每一段都产生了1的

的贡献。如果一处断点发生变化。其它的断点整体上的贡献数目是不会变化的。只需要新得到的断点和消失的的变化和即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;

void solve()
{
    ll n, m;
    cin >> n >> m;
    vector<int> a(n + 2, 0);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    ll ans = 0;
    for (int i = 1; i < n; i++)
        ans += (a[i] != a[i + 1]) * (n - i) * i;

    while (m--)
    {
        int i, x;
        cin >> i >> x;
        ans -= (a[i] != a[i - 1]) * (i - 1) * (n - i + 1);
        ans -= (a[i] != a[i + 1]) * i * (n - i);
        a[i] = x;
        ans += (a[i] != a[i - 1]) * (i - 1) * (n - i + 1);
        ans += (a[i] != a[i + 1]) * (i) * (n - i);
        cout << ans + (n + 1) * n / 2 << '\n';
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t;
    t=1;
    while (t--)
        solve();
}
```



#### 生长思考：

- 

