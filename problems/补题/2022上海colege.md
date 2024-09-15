#### $first$

[Expenditure Reduction](https://codeforces.com/group/cQGUBWxrFs/contest/403404/problem/E)

#### 简介

```txt
给定一个串F寻找，F的最小子串f，使得S依然是f的子序列。
```

#### 思路

```txt
当找到一个位置时 就看前面的一些前缀是否已经满足。
关注前缀首位置最大。

并且只需要记录一个即可，其它的无非是不成前缀，或是离得较远。
f[i]; 表示，保证前缀s1...si的最大首位置。
这样一直保持更新。一旦确定了一个最终位置，就可以更新答案。

相关方程如下。 如果 f[i]=min(f[i],f[i-1]))
关于第一位，需要特殊判断：
如果是第一位特殊处理。
```

##### code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100 + 10;
int c[maxn];

void solve(){
    vector<int> rec[123];
    string f, s;
    cin >> f >> s;
    c[0] = -1;
    for (int i = 0; i < s.size(); i++)
    {
        rec[s[i]].push_back(i + 1); //记录各个字母出现的位置。
        c[i + 1] = -1;              //第几位的最大前缀初始位置
    }
    int l = 0, r = 1e6;
    if (s.size() == 1){
        cout << s << '\n';
        return;
    }
    for (int i = 0, size = f.size(); i < size; i++){
        if (f[i] == s[s.size() - 1] && c[s.size() - 1] != -1)
        {
            if (r - l + 1 > i - c[s.size() - 1] + 1)
                l = c[s.size() - 1], r = i;
        }
        for (int j = rec[f[i]].size() - 1; j >= 0; j--)
            c[rec[f[i]][j]] = max(c[rec[f[i]][j] - 1], c[rec[f[i]][j]]);
        if (f[i] == s[0])
            c[1] = i;
        //尝试更新答案。
    }
    for (int i = l; i <= r; i++)
        cout << f[i];
    cout << '\n';
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        solve();
}
```

----

#### $second$

- [Another A +B problem](https://codeforces.com/group/cQGUBWxrFs/contest/403404/problem/A)

- 简介

  ```txt
  给出一个等式。
  形式为
  X1X2+X3X4=X5X6.
  X为0....9
  为每一个位置标记一个颜色。
  表示：
  绿色 ： 数字就在正确的位置上；
  紫色 ： 数字存在但是并不在正确的位置上；
  黑色 ： 该数字不存在。将数字细化为一个具体的个体，而不是一类数字。
  ```

- $thinking$

  - 暴力枚举

    - 完全暴力。

      ```TXT
      10000
      1.check函数怎么设计？
      某一位置上的固定的数字；
      某数字的出现次数。
      某位置上不该出现的额数字。就是该位置上的数字为紫色。
      
      关于处理上述的信息的方法：
      相关的结构：
      某一位置上固定的数字：
      sure[i];表示当前位置上确定的数字。
      
      bb[i];是否有黑色的出现。
      mmax[i]:某一个数字的个数最多为多少。当出现黑色的时候就可以进行讨论。
      
      pp[i]是否有紫色的出现。
      mmin[i],用来紫色，处理这一个数字出现至少出现多少次多少次。
      
      
      ok[i][j],当前位置上的哪一些位置不可以放置。。
      
      统一这一个信息之后，进行函数的设计。
      
      关于枚举所有可能的状态。
      方式一： 二重循环。
      方式二： dfs
      
      
      这里引发了一个思考：
      (尝试重新去，理解一个循环结构的含义。
      这里面将思写入基础语言的题上。)
      ```
      
  
  ####  $code$
  
  ```cpp
  #include <bits/stdc++.h> //怎么写这个暴力搜索？
  using namespace std;
  typedef long long ll;
  const int maxn = 2e5 + 10;
  
  int mmax[10];    //记录每一个数字是否出现的上限。出现多少次以及它的上限。
  int f[10];       //记录么某一个位置上已经确定了的位置。
  bool ok[10][10]; //哪一些位置不可以放置。
  vector<string> ans;
  int c[10];
  int rec[10];
  bool bb[10];
  bool pp[10];
  int mmin[10];
  
  int main()
  {
      ios::sync_with_stdio(false);
      cin.tie(nullptr), cout.tie(nullptr);
  
      string s, a;
      cin >> a;
      cin >> s;
  
      s = '#' + s;
      a = '#' + a;
      memset(f, -1, sizeof(f));
      for (int i = 1; i <= 8; i++)
      {
          if (i == 3 || i == 6)
              continue;
          mmax[a[i] - '0']--;
      }
      for (int i = 1; i <= 8; i++)
      {
          if (i == 3 || i == 6)
              continue;
          if (s[i] == 'G')
              f[i - (i + 1) / 4] = a[i] - '0'; //这里对应的第二位。
          else if (s[i] == 'P')
          {
              ok[i - (i + 1) / 4][a[i] - '0'] = true;
              mmax[a[i] - '0'] = abs(mmax[a[i] - '0']);
              pp[a[i] - '0'] = true;
          }
          else if (s[i] == 'B')
          {
              mmax[a[i] - '0'] = abs(mmax[a[i] - '0']);
              mmax[a[i] - '0']--;
              bb[a[i] - '0'] = true;
              ok[i - (i + 1) / 4][a[i] - '0'] = true;
          }
      }
      for (int x = 0; x <= 99; x++)
          for (int y = 0; y <= 99 - x; y++)
          {
              bool flag = false;
              memset(rec, 0, sizeof(rec));
              int z = x + y;
              c[1] = x / 10;
              rec[c[1]]++;
              c[2] = x % 10;
              rec[c[2]]++;
              c[3] = y / 10;
              rec[c[3]]++;
              c[4] = y % 10;
              rec[c[4]]++;
              c[5] = z / 10;
              rec[c[5]]++;
              c[6] = z % 10;
              rec[c[6]]++;
              for (int i = 1; i <= 6; i++)
              {
                  if (f[i] != -1 && f[i] != c[i])
                      flag = true;
                  if (ok[i][c[i]])
                      flag = true;
              }
              for (int i = 0; i < 10; i++)
              {
                  if (pp[i] && rec[i] < mmax[i])
                      flag = true;
                  if (bb[i] && rec[i] > mmax[i]) //紫色的类型必须到达规定的数量。
                      flag = true;
              }
              if (!flag)
              {
                  string tt;
                  for (int i = 1; i <= 6; i++)
                  {
                      tt = tt + char(c[i] + '0');
                      if (i == 2)
                          tt = tt + '+';
                      if (i == 4)
                          tt = tt + '=';
                  }
                  ans.push_back(tt);
              }
          }
      cout << ans.size() << '\n';
      for (auto i : ans)
          cout << i << "\n";
  }
  ```



#### 反思

- 这么多的结构，反正自己是看吐了。
- 学习别人写的代码：

