#### infected tree

chenjiuri_infectedtree2022112

[tree infection](https://codeforces.com/problemset/problem/1665/C)

- 简介

```txt
对一颗树进行操作
每一秒钟，有两种情况：
已经被感染的节点，继续感染它的兄弟，注意只能够感染一个。
选择一个节点进行感染。
感染整一棵树，找出最短的感染上时间。
```

- 转换思维
  - 抽象出若干个数，表示同一个双亲的关系的若干个划分中，节点的个数。
  - 将这些数排个序。
  - 于是问题转换为，每一秒钟选择一个数字。使得其减少1.并且之后它会不断减少。求出使得所有数字变成零的最少时间。

- 贪心
  - 优先从最大到最小进行感染。
  - 看来是极度好玩的大模拟。

- 具体的步骤
  - 从大到小，先对所有的点染一次。
  - 把已经染完的数（小于等于0）的数全部筛除。
  - 选出最大的继续进行染色。
  - 模拟就说明，时间是充裕的。多多使用stl中的函数。使得代码更加简洁。


#### code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;

int ans;

void moni(vector<int> a) //每一秒钟的情况。
{
    if (a.empty())
        return;   //已经感染完了
    int last = 0; //
    int n = a.size();
    while (last < n && a[last] == a[0])
        last++;
    last--; //当前指向的就是最后一个最大的。
    a[last]--;
    ans++;
    for (int i = 0; i < n; i++)
        a[i]--;
    while (!a.empty() && a.back() <= 0)
        a.pop_back();
    moni(a);
}

void solve() //
{
    int n;
    ans = 0;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int x;
        cin >> x;
        a[x]++;
    }
    a.emplace_back(1);
    sort(a.rbegin(), a.rend());
    while (!a.empty() && a.back() <= 0)
        a.pop_back();
    n = a.size();
    for (int i = 0; i < n; i++)
    {
        a[i] -= n - i;
        ++ans;
    }
    sort(a.rbegin(), a.rend());
    while (!a.empty() && a.back() <= 0)
        a.pop_back();
    moni(a);
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

#### szsk

- 可以学到一些语言应用。君子善假于物也。
  - 对一个vector容器排序。
    - sort( a.rbegin( ) , a.rend( ) );
    - sort(a.begin( ) , a.end( ) );reverse(a.begin() , a.end( ) );
- 模拟大法。模拟关键面向过程，分离出几个独立相区分的过程，进行模拟。
  - 定义相关函数，减少代码量。
  - 合理应用相关的stl类库的容器。



