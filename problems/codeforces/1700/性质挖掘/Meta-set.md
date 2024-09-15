https://codeforces.com/problemset/problem/1735/D

- 这里存在若干张牌，上面有k个数字。
- 选出五张牌，我们将其称为好牌组—>可以选出两种（以上）三张，其中每一组fecture是good
- feactur是good的条件是：同一个feacture是相同的，或者两两之间不一样。

#### 20MINS

- 暴力枚举角度，就是找出所有的情况：然后在这些三三之间进行一个配对。
- 这种卡的分组问题，一种常见的思路是，转化为图，关注这张图的一些特性。
  - 无法定位他们之间的一些关系。使得它们建图。
- 发现当，两张牌确定之后，剩下的一张进行确定，就是说，五张以内其情况是
  - 选定3张，剩下两张牌和三张的其中一张进行一个配对。
- 快速定位一张牌，可以通过哈希方法进行。

![](1210.1.jpg)

#### tutorial

<img src="1210.2.png" style="zoom:50%;" />

- 两个结论
  - 两定，第三定。
  - 两对于同一张。；，其组合除了本身没有其它的相交牌。可以直接基于该量进行贡献计算。

- 可以通过一个map记录来实现，复杂度为$klog(n)*n^2$

```cpp
#include <iostream>
#include <vector>
#include <map>
using namespace std;
vector<vector<int>> ku;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    ku.resize(n);
    map<vector<int>, int> rec; //这也行。
    for (int i = 0; i < n; i++)
    {
        ku[i].resize(k);
        for (auto &j : ku[i])
            cin >> j;
    }
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            vector<int> temp;
            for (int t = 0; t < k; t++)
            {
                if (ku[i][t] == ku[j][t])
                    temp.push_back(ku[i][t]);
                else
                {
                    for (int tt = 0; tt < 3; tt++)
                        if (tt != ku[i][t] && tt != ku[j][t])
                            temp.push_back(tt);
                }
            }
            rec[temp]++;
        }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int now = rec[ku[i]];
        ans += (now) * (now - 1) / 2;
    }
    cout << ans << '\n';
}

```



#### 生长思考：

##### stl的应用：                                               

- 学习一下stl的应用技巧。

`map<vector,int>rec;`

- 理解vector中大于，小于重载函数

##### 某些问题下的处理技巧：

- 问题表达形式：
  - 给定若干个数字：如果相同，ans=0;如果不同就是一个数域中的缺省值（这一系列的数如果不相同，就是连续的一个数域中的数字。）
- 方法
  - 不同情况之下，由简单的方程，直接sum-now即可。
  - 相同情况之之下。虽然 是加一个特判就好。
  - `res[i] = (6 - (a[i] + b[i])) % 3;`
  - 那么多问题要解决。当一个思维趣味儿思考题。



```cpp
a1=4*j
a2=a1
```

