#### [Binary String](https://codeforces.com/problemset/problem/1680/C)

- chenjiuri_aiduvet

```txt
给定一个01字符串，
完成一个操作：
从字符串的左边移走一些字符。
从字符串的右边移走一些字符，
A: 关注移除操作中的涉及的1字符的个数。
B: 关注剩下字符中0的个数。
C: max(A,B);

也可以不移除任何一个字符。
问使得C的可能最小值。
```

#### $20mins$

```txt
直接暴力的复杂度是
n^n

考虑进行一些优化：发现一些规律。

当我们取到一个状态时：
左边取 1......l
右边取 r......n
然后如何发展；
如果是贪心，最后两个指针都必须停留在0处。
如果是0多就旭要继续往下取。
枚举的解空间还是很大：
两个指针应该往哪一边走？

进一步减小：
两个指针都向前移动，取寻求两者相等的分界点情况。最终两个指针都必须在这一个范围里面。
```

##### 题解思路

- 假设$1$的个数为$c$,
- 现在假设有一种具体方式，使得现在的花费为$k$
  - 意味着现在：删除出的字符中，1的个数至多为k个。剩下的字符中，0的个数至多为k个。
- 现在尝试寻找出一个结构较优的等效解：
  - 从单纯的只删除一端的字符。看是否可以出现一个等效解的情况。
  - 不需要管左边的方式：保留左边的删法。然后继续出发，删掉相同个数的1之后，不可以保证0的删除情况，如果之前的解受限于0，并不一定得该解。
    - $1111111111111111111111000000000000000000001111$

-------

##### 二分几步走。

- 证明二分答案的可行性
  - 解空间中满足某一个前提，当出现了k的解之后
  - 单纯考虑删除继续删除前缀，只要满足k+1<=c,就可以构造出删除k+1解的情况.
  - 已经成功证明了二分答案的可行性

- 怎么检查一个答案是否存在？也就是检查一个答案存在的充要条件。
  - 直接检查刚好删除k个的情况，
    - 定义$pos_i$为删除第到$第i个1$的位置。
    - 关注$pos_{i+c-k-1}-d_{i}$.寻找最小值。
    - 如果$min(d_{i+c-k-1}-d_{i})+1-（c-k）>k$
      - 删去大于k个1，显然不必讨论。
      - 如果删去等于k个1，必然是上述min讨论值得一个拓展，但是拓展得解中left零变多。
      - 如果小于k个1，显然中间得两个边界1之间得0必然会更多。未删除地方必然包含了$pos_{i+c-k-1}-pos_i$的部分

------

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;

int f[maxn]; //第i个1哪里。
int c;

bool check(int x)
{
    int mmin = 0xfffffff;
    for (int i = 1; i + c - x - 1 <= c; i++)
        mmin = min(mmin, f[i + c - x - 1] - f[i] + 1);
    return mmin - c + x <= x;
}

void solve()
{
    string s;
    c = 0;
    cin >> s;
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '1')
            f[++c] = i;
    int low = 0, high = c;
    while (low < high)
    {
        int mid = (low + high) >> 1;
        if (check(mid))
            high = mid;
        else
            low = mid + 1;
    }
    cout << low << '\n';
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



