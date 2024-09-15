https://codeforces.com/contest/1770/problem/C

给定一组数。是否存在一个x(x>0)使得任意两个元素ai , aj 加上x之后互质。

#### 思路

- 对于一些就在简单的现象。发现如果数组中奇数的个数和偶数都大于两个。那么无论加什么数字，都会使得至少存在两个公因数为2.
- 本质上，我们关注元素mod一个数字的余数。如果任何一个位置上都出现了两个以上，则一定无解。否则可能有解，至少有方案使得模数不会会成为两个之间的公因数。只要不使得两个元素加上一个数刚好补满即可。
- 如果系列的质因数被处理过后，球墨条件可以同时满足。涉及的质数都不会成为任何两个元素之间的公因数。
- 应用鸽巢原理只需要枚举到n/2.

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;

void solve()
{
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    bool ok = true;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] == a[j])
            {
                ok = false;
                break;
            }
        }
    for (int i = 2; i <= n / 2; i++)
    {

        vector<int> cunt(i, 0);
        for (int j = 0; j < n; j++)
            cunt[a[j] % i]++;
        if (*min_element(cunt.begin(), cunt.end()) >= 2)
        {
            ok = false;
            break;
        }
    }
    cout << (ok ? "Yes\n" : "No\n");
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

