**F. The Boss's Identity**
https://codeforces.com/contest/1847/problem/F
![image-20230710160041504](C:/Users/86153/AppData/Roaming/Typora/typora-user-images/image-20230710160041504.png)
用或运算相关的方式，构造出一个数组，基于该数组 ， 解决的经典首个大问题：

#### 20mins
1. 如果只是给定一个静态的数组，怎么去解决上述问题？
   1. 基础的离散化。
   2. 记录某一个离散值的最小位置。
   3. 使用前缀和优化。
2. 题目中的或运算，显示出了什么信息？
   1. 无限的推演下去，最后是否稳定？
      1. 稳定与整个数组的或和。
      2. 数组中出现的不同的元素值的组合方式是$n^2$，数量非常多，因此不能从整体上进行一个统计后处理。
   2. 怎么确定某一个值？ 打表。
      1. 分为若干类型： 2 ， 3 ， 4 ， 5。各个数的所有匹配方式都将会被考虑到。
   3. 给定一个值后怎么check。
      1. 分类讨论：
         1. 前面n个没有更加大的。
         2. 最多选择30不同的元素或运算，可能就可以表达出能表达的所有数字。
      2. 变成选择某一些数字，再定位这个数字的最小的位置在何处的问题。

### solve

参考题解：

[Codeforces Round 882 (Div. 2) A - D, F - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/642054672)

关键：

1. 关注到有效或字段的有限性。
2. 整理后，进行一个二分。

![image-20230710164354755](C:/Users/86153/AppData/Roaming/Typora/typora-user-images/image-20230710164354755.png)

#### 实现的几个关键：

1. 怎么整理出不同右端点下，有效的子段？
2. 怎么在上述基础上进行一个二分？



模仿 

Heltion's code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    for (cin >> t; t; t -= 1) {
        int n, q;
        cin >> n >> q;
        vector<int> a(2 * n);
        for (int i = 0; i < n; i += 1) {
            cin >> a[i];
            a[i + n] = a[i];
        }
        vector<pair<i64, int>> ans;
        ans.emplace_back(0, a[0]);
        vector<pair<int, int>> f = {{a[0], 0}};
        for (int i = 1; i < 2 * n; i += 1) {
            f.emplace_back(0, i);
            vector<pair<int, int>> g;
            for (auto [x, y] : f) {
                x |= a[i];
                if (not g.empty() and g.back().first == x) {
                    g.pop_back();
                }
                g.emplace_back(x, y);
            }
            f.swap(g);
            if (i > n) {
                for (auto [x, y] : f) {
                    ans.emplace_back(i64(i - y) * (n - 1) + i - n, x);
                }
            }
        }
        ranges::sort(ans);
        vector<pair<int, i64>> res;
        for (auto [x, y] : ans) {
            if (res.empty() or y > res.back().first) {
                res.emplace_back(y, x);
            }
        }
        for (int i = 0, v; i < q; i += 1) {
            cin >> v;
            auto it =
                ranges::upper_bound(res, pair(v, numeric_limits<i64>::max()));
            if (it == res.end()) {
                cout << "-1\n";
            } else {
                cout << it->second + 1 << "\n";
            }
        }
    }
}
```

#### 吸收

1. 得到各个子段和的方法：

   1. 基于上一轮的子段和进行拓展，并且尽量使其更短： 左边界靠右。

   2. 去重问题：

      1. 上述的代码是利用了连续或子段的性质：

      ```cpp
      for (auto [x, y] : f) {
          x |= a[i];
          if (not g.empty() and g.back().first == x) {
              g.pop_back();
          }
          g.emplace_back(x, y);
      }
      对于他们是连续存放的。这意味着有一个长度上升的连续关系。那么先入的更长。并且如果存在两段相等，必然是相邻入g的。（或运算的特殊性质）
      ```

2. 将所有的段进行一个权值分配，使得排序后既满足二分的条件，也满足其选择策略的优先级别：

   1. 这里的方法是：通过几个特征构造一个数字：

      1. 其长度，越小越好
      2. 右边界，越小越好。

   2. 于是将其整合成：

      ```
      (i - y) * (n - 1) + i - n , x
      其实这个数字就是第几个。
      ```

3. 怎么基于上述的整合值进行二分？

```cpp
// 先根据第一维进行一个排序。
ranges::sort(ans);
vector<pair<int, i64>> res;

// 反过来升序去重。
for (auto [x, y] : ans) {
    if (res.empty() or y > res.back().first) {
        res.emplace_back(y, x);
    }
}
// 总的来说，为了减少麻烦，Heltion对这个数组进行了多次的处理。

for (int i = 0, v; i < q; i += 1) {
    cin >> v;
    // 这个函数的作用是返回内置类型的最大值。
    auto it =
        ranges::upper_bound(res, pair(v, numeric_limits<i64>::max()));
    if (it == res.end()) {
        cout << "-1\n";
    } else {
        cout << it->second + 1 << "\n";
    }
}
```
