## Sending a Sequence Over the Network

[adr](https://codeforces.com/problemset/problem/1741/E)

- 问题简介

```txt
对于一个序列
a1，a2,a3,a4,a5,a6,a7.....
将它分割为若干段，在每一段两边添加它的长度。
然后按顺序将他们拼接。
给出一个序列b；
问按照上述的规则，是否存在一个序列使得，按照上述规则转化后得到序列b?
```

- $20min$

```txt
问题转化为，抽取出若干个数，使得分别管理一个区间。

向下遍历过程中，对于每一个数字，两个状态；选择，作为左边还是作为右边。
设d[i]表示从头部长度为i可以找到一组解。考虑管左边管右边，不断更新即可。无论哪一种选择，必须保证，其另外一边可以独立的找出一个合法的a序列。

注意判断是否会越界。
k=i+a[i];
if(f[i-1]&&k<=n)f[k]=true;
k=i-a[i];
if(k>=1&&f[k-1])f[i]=true;
```

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
int a[maxn], f[maxn];

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        f[i] = false;
    }
    for (int k, i = 1; i <= n; i++)
    {
        k = i + a[i];
        if (k <= n && f[i - 1])
            f[k] = true;
        k = i - a[i];
        if (k >= 1 && f[k - 1])
            f[i] = true;
    }
    if (f[n])
        cout << "Yes" << '\n';
    else
        cout << "No" << '\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t;
    cin >> t;
    f[0] = true;
    while (t--)
        solve();
}
```

