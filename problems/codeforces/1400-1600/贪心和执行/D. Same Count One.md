https://codeforces.com/contest/1774/problem/D

- 概述。贪心的思路想法是对的，也做出了一些证明。

#### thinking

- 判断无解情况。假设$sumof(1)\%3==0$，同时可以发现如果满足了上面的条件必然可以构造出一组解。
- 最优的交换策略：
  - 1的个数等于$\frac{sum}{n}$的不用操作。
    - 这一点怎么证明呢？
  - 将数组分成两类。$sumof(1)(>,<)avg$于是在这两类间进行一个交换。最终必然会刚好交换完。



#### code

下面这一份代码基本上都是参考了tourist的。里面应用了一很多值得学习的编写技巧。比方说lambda表达式子。stl-》（vector,array,iota,sort等等的使用）                                                                                                                                                               

```cpp
// 思路一样就是常数太大了
// 学习tourist大佬的代码。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;

void solve()
{
    int h, w;
    cin >> h >> w;
    vector<vector<int>> a(h, vector<int>(w)); // 学习vector的应用
    vector<int> cunt(h);
    int sum = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            cin >> a[i][j];
            sum += a[i][j];
            cunt[i] += a[i][j];
        }
    }
    if (sum % h != 0)
    {
        cout << "-1\n";
        return;
    }
    int avg = sum / h;
    // 这里可以学一个lambda表达式。
    vector<int> order(h);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j)
         { return cunt[i] < cunt[j]; }); // 这里发现连这个sort中的排序重载也不太懂。就是满足true时不变否则改变顺序。
    vector<array<int, 3>> ans;           // 这里又学到了一种结构。
    int i = 0, j = h - 1;
    while (i < j)
    {
        if (cunt[order[i]] == avg)
        {
            i++;
            continue;
        }
        if (cunt[order[j]] == avg)
        {
            j--;
            continue;
        }
        for (int k = 0; k < w; k++)
        {
            if (cunt[order[i]] == avg || cunt[order[j]] == avg)
                break;
            if (a[order[i]][k] == 0 && a[order[j]][k])
            {
                swap(a[order[i]][k], a[order[j]][k]);
                cunt[order[i]]++;
                cunt[order[j]]--;
                ans.push_back({order[i], order[j], k});
            }
        }
    }
    cout << ans.size() << '\n';
    for (auto t : ans)
    {
        cout << t[0] + 1 << ' ' << t[1] + 1 << ' ' << t[2] + 1 << '\n';
    }
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

#### 生长思考：

- vector的初始化方式。 [stl.md](programming language\C++&&C\basic of lanuge\stl.md) 

- iota 就是生成连续的值。一般用在vector容器上。

- array的简单使用
  - array<int,length> 定义容器的类型，定义容器的长度。
  - 如果没有需要使用pair的排序功能。就可以使用这个array<int,2>来代替简单的与容器相配合的存储功能。
  
- 一些管理技巧。
  - 将对象保存在数组之中，为其分配索引。
  - 新建数组，保存元素索引。
  - 使用sort函数，按照实际需求进行排序。最后在数组上进行操作。

- lambda表达式。 [lamada表达式.md](programming language\C++&&C\basic of lanuge\lamada表达式.md) 

- sort

  - 设计传参函数块时候。

  `bool f(int first,int second){`

  `return first<second;`

  `}`

  函数不断地对两个元素进行比较，来决定是否变化位置。前序传第一个参数，后序传第二个参数。

  - 返回false 调整顺序。
  - 返回true  




####  自己的第一份代码。相当于看个笑话。

```cpp
#include <bits/stdc++.h>
using namespace std;
int rec[100000 + 10];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<string> s(n);
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                char temp;
                cin >> temp;
                s[i]+=temp;
            } 
            for (auto k : s[i])
                if (k == '1')
                    sum++;
        }
        if (sum % n != 0)
        {
            cout << -1 << '\n';
            continue;
        }
        // 接下来//模拟这一个过程才行。
        // 然后接下来就是利用这些stl中封装得到的结构进行一个大模拟。
        vector<int> mo[2];
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int sum_si = 0;
            for (auto j : s[i])
                if (j == '1')
                    sum_si++;
            if (sum_si > sum / n)
                mo[1].push_back(i), ans += sum_si - sum / n;
            else
                mo[0].push_back(i);
            rec[i] = sum_si;
        }
        // 接下来是
        cout << ans << '\n';
        while (!mo[0].empty() && !mo[1].empty())
        {
            int smaller = mo[0].back();
            int bigger = mo[1].back();
            for (int i = 0; i < m; i++)
            {
                if (rec[smaller] == sum / n)
                {

                    mo[0].pop_back();
                    break;
                }
                if (rec[bigger] == sum / n)
                {
                    mo[1].pop_back();
                    break;
                }
                if (s[bigger][i] > s[smaller][i])
                {
                    swap(s[bigger][i], s[smaller][i]);
                    cout << smaller + 1 << ' ' << bigger + 1 << ' ' << i + 1 << '\n';
                    rec[smaller]--;
                    rec[bigger]--;
                }
                // 查看是谁先出局。
            }
        }
    }
}
```





