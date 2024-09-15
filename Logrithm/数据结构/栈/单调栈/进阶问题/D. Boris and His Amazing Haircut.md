https://codeforces.com/problemset/problem/1779/D



#### 算法描述：

从高往低减少，争取让一把剪刀减取足够多的头发。

对于每一根头发我们都必然会匹配到一把剪刀。

所以我们用一个单调栈往下搜，在这个过程中保证单调性。一旦有新的元素（不和栈中的一个某一个元素相同，就使用一把剪刀）这样一直进行。

维护剪刀的使用情况，最终就可以判断是否能够实现理想长度的头发。

注意：

- 头发比目标长度短。不可能实现。
- 头发和目标一样短，省一把剪刀。

#### 算法理解

首先将第一个元素入栈；如果当前$a_i>b_i$使用一把剪刀。使用了一把剪刀之后就入栈。否则不需要。

如果遇到比top大的，就可以全部都放出来了，因为我们保留栈是希望用当前长度的剪刀，去使得后面遇到的同要使用同一种梳子的头发也使用保留的剪刀从而实现节省一把剪刀。

如果遇到了很大的$b_i$就失效了。所以此时就重新调整单调栈。要保证中间没有比剪刀长度更高的头发才能重复利用。

#### 生长思考：

怎么有一个单调栈的意识？ 扫描一遍数组。

单调栈是一种很天然的维护方法。还得慢慢体会。





```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
int a[maxn], b[maxn], x[maxn];

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    int m;
    cin >> m;
    map<int, int> rec;
    for (int i = 1; i <= m; i++)
    {
        cin >> x[i];
        rec[x[i]]++;
    }
    stack<int> stk;
    for (int i = 1; i <= n; i++)
    {
        if (b[i] > a[i])
        {
            cout << "NO\n";
            return;
        }
        // 如果已经向等了那么就不用减。所以这里有一个特判断点。
        while (!stk.empty() && stk.top() < b[i])
            stk.pop();
        if (a[i] != b[i])
        {
            if (stk.empty() || stk.top() != b[i])
                stk.push(b[i]), rec[b[i]]--;
        }
        if (rec[b[i]] < 0)
        {

            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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

