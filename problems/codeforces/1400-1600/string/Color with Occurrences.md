### $Color\quad with \quad Occurrences:$

```txt
问题简介：
给定一个字符串，以及两个模板串，
可以在字符串中找到子串模板串的字符串染色，
对于一个字符进行重复染色没有影响。
问，是否可以将该字符串所有字符染色。
并且求出当前的最小操作数。
```

#### $20min$:

```txt
通过字符串匹配，可以在O（n）的花费之下，将所有子串找出。
然后问题转化为：
在所有线段之中，寻找到以组数量最小，并且能够覆盖字符串的一个解。
然后贪心即可。
从第一个开始，寻找已经染色的范围，并且更新。
然后从更新区的后边开始寻找。
一直在范围之内选择，突破最大的选择。
```

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve()
{
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<string> k(n);
    for (auto &i : k)
        cin >> i;
    int flag = 0;
    //实现细节
    //拓展区，
    int low = 0, high = 0;
    vector<pair<int, int>> ans;
    while (high < s.size()) //已经拓展成功的区域。
    {
        int mmax = high - 1;
        int wi, pi;
        for (int i = low; i <= high; i++)
            for (int j = 0; j < k.size(); j++) //枚举当前的位置
            {
                int h = 0; //暴力匹配。
                while (i + h < s.size() && h < k[j].size() && k[j][h] == s[i + h])
                    h++;
                if (h == k[j].size()) //说明匹配成功。
                    if (mmax < i + h - 1)
                        wi = j + 1, pi = i + 1, mmax = i + h - 1;
            }
        if (mmax < high)
        {
            cout << -1 << '\n';
            return;
        }
        else
            ans.push_back({wi, pi});
        low = high + 1, high = mmax + 1;
    }
    cout << ans.size() << '\n';
    for (auto i : ans)
        cout << i.first << ' ' << i.second << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
}
```

#### 生长思考：

- 相关的量
  - $mmax$:  当前确定染色的最大区间右端。
  - $low,high$，当前循环中尝试拓展的区间。就是以某一个点作为染色段的左端。找出一个使$mmax$最长的合法的方案。

- 关键的问题：

  - 最外层循环退出的标记。

    - 记录标记已经染色的区间，当前已经染色的区间如果等于当前的区间长度之后，就退出即可。定义

    ​        了$high$当循环开始时，$high-1$就代表了已染色区间。当$high>=n$时说明已经完成染色。

    







