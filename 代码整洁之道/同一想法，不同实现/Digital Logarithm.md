## [ Digital Logarithm](https://codeforces.com/problemset/problem/1728/C)

## 问题简述:

```txt
给定两个数组a,b。可以对数组中的元素进行操作： 
一次操作将一个数变为当前数的十进制位数。
求最小操作数使得，两个数组每个数的次数相等。即可以将一个数组按照新的排列变成另外一个数组。
```

### 算法（贪心，数据结构）

- 预处理
  - 首先去重。
  - 对于个位数，计算每个数出现数量。
  - 对于多位数，计算各种位的数的出现数量。

- 贪心处理

  - 先将，多位数的和个位数的进行匹配。每队整体贡献1；
  - 同位数和同位数整体贡献为2
  - 孤独多位数数贡献2；

  - 这样$ans$结果如下：
  - $a_1$个位数的情况。$a_2$其它位数的情况。

  $$
  t=min(a1_i,b2_i)\\
  ans=a1_i+(b2_i-t)\times 2\\
  t=min(a2_i,b1_i)\\
  ans=b1_i+(a2_i-t)\times 2
  $$

  ### 第一个代码：

  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  int a1[10];
  int a2[10];
  int b1[10];
  int b2[10];
  void solve()
  {
      map<int, int> rec;
      for (int i = 0; i < 10; i++)
          a1[i] = a2[i] = b1[i] = b2[i] = 0;
      int n;
      cin >> n;
      for (int i = 1; i <= n; i++) //这里怎么处理一次？记录就
      {
          int t;
          cin >> t;
          if (rec.count(t))
              rec[t]++;
          else
              rec.insert({t, 1});
          int c = 0;
          int tt = t;
          while (t > 0)
          {
              c++;
              t /= 10;
          }
          if (c == 1)
              a1[tt]++;
          else
              a2[c]++; //某一位的位数的情况也是要记录的。
      }
      for (int i = 1; i <= n; i++) //这里怎么处理一次？记录就
      {
          int t;
          cin >> t;
          int c = 0;
          int tt = t;
          while (t > 0)
          {
              c++;
              t /= 10;
          }
          if (rec.count(tt))
          {
              rec[tt]--;
              if (c == 1)
                  a1[tt]--;
              else
                  a2[c]--;
              if (rec[tt] == 0)
                  rec.erase(tt);
          }
          else
          {
              if (c == 1)
                  b1[tt]++;
              else
                  b2[c]++;
          }
      }
      int ans = 0;
      for (int i = 2; i <= 9; i++)
      {
          //现在计算匹配的情况。
          int t = a2[i] - b1[i];
          if (t >= 0)
              ans += b1[i], a2[i] -= b1[i];
          else
              ans += b1[i], a2[i] = b1[i] = 0;
          t = b2[i] - a1[i];
          if (t >= 0)
              ans += a1[i], b2[i] -= a1[i];
          else
              ans += a1[i], a1[i] = b2[i] = 0;
          t = min(a2[i], b2[i]);
          ans += (a2[i] - t) * 2 + (b2[i] - t) * 2 + 2 * t;
      } //这里还有其它的处理。
      cout << ans << '\n';
  }
  int main()
  {
      int t;
      cin >> t;
      while (t--)
          solve();
  }
  //先用map去重
  //然后相对应。先把一次的处理完，再去处理2次的。再去处理三次
  ```

  - ### 改进分析

    - 比如求位数的函数可以封装成块。
    - 计算$ans$的步骤中，分类讨论过多。按照算法，直接计算即可。
    - 关于map的使用不够熟练。比如说【 】。如果即使没有它也会帮你创建一个。所以不需要分类讨论。

  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  int a1[10],a2[10],b1[10],b2[10];
  int g(int t){
      int c = 0;
      while (t > 0){
          t = t / 10;
          c++;
      }
      return c;
  }
  void solve(){
      map<int, int> rec;
      for (int i = 0; i < 10; i++)
          a1[i] = a2[i] = b1[i] = b2[i] = 0;
      int n;
      cin >> n;
      for (int i = 1; i <= n; i++) {
          int t;
          cin >> t;
          rec[t]++;
          int c = 0;
          c = g(t);
          if (c == 1)
              a1[t]++;
          else
              a2[c]++; //某一位的位数的情况也是要记录的。
      }
      for (int i = 1; i <= n; i++) //这里怎么处理一次？记录就
      {
          int t;
          cin >> t;
          int c = 0;
          c = g(t);
          if (rec[t]){
              rec[t]--;
              if (c == 1) a1[t]--;
              else        a2[c]--;
          }
          else{
              if (c == 1) b1[t]++;
              else        b2[c]++;
          }
      }
      int ans = 0;
      for (int i = 2; i <= 9; i++){
          //现在计算匹配的情况。
          int t = min(a1[i], b2[i]);
          b2[i] -= t;
          ans += a1[i];
          t = min(a2[i], b1[i]);
          a2[i] -= t;
          ans += b1[i];
          t = min(a2[i], b2[i]);
          ans += t * 2 + (a2[i] - t) * 2 + (b2[i] - t) * 2;
      } //这里还有其它的处理。
      cout << ans << '\n';
  }
  int main(){
      int t;
      cin >> t;
      while (t--)
          solve();
  }
  //先用map去重
  //然后相对应。先把一次的处理完，再去处理2次的。再去处理三次的。
  ```

### $final$贪心法的证明：

- 可以将问题转化：对于两个数组，筛选出一对数。研究每组数对答案的贡献。求贡献和最小。

  - 证明贪心角度1：随便假设一个匹配序列。对于如果在两个数组中分别存在两个相等的数，但是他们没有进行匹配。
    $$
    a_1=b_1;\\
    a_2!=b_2;\\
    a_1!=a_2;\\
    此时a_1——b_2,a_2——b_1\\
    假设sum1为其它对的总贡献，sum2为关注的两对的总贡献。\\
    ans=sum1+sum2\\
    原来的贡献情况为：\\
    sum2>=4;(不相等必然，两两变化)\\
    将这一个相同的匹配之后。\\
    无论几个数的位数是哪一种情况都可以抱证\\
    sum2`<sum2;证明
    $$

- 进一步改进：
  - 去重之后，多位数，必然会进行一次操作。
  - 先对多位数做一次操作。
  - 然后进行去重，多余的数再进行一次操作。
  - 所以直接用一个优先队列来模拟。

```cpp
#include <bits/stdc++.h>
using namespace std;

priority_queue<int> a, b;

int g(int k){
    int ans = 0;
    while (k)
    {
        k /= 10;
        ans++;
    }
    return ans;
}

void solve(){
    int ans = 0;
    int n;
    cin >> n;
    for (int i = 1, t; i <= n; i++)
    {
        cin >> t;
        a.push(t);
    }
    for (int i = 1, t; i <= n; i++)
    {
        cin >> t;
        b.push(t);
    }
    while (!a.empty() && !b.empty())
    {
        int c1 = a.top();
        int c2 = b.top();
        if (c1 == c2)
            a.pop(), b.pop();
        else if (c1 > c2)
        {
            a.pop();
            ans++;
            a.push(g(c1));
        }
        else
        {
            ans++;
            b.pop();
            b.push(g(c2));
        }
    }
    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
}
```





​               