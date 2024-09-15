https://codeforces.com/problemset/problem/1765/K

- 题意比较简单，不需要记录

#### $20mins$

- 本来想着构造出了几种简单的解答。
  - 就是只考虑了一种类型的方案。1...n-2列全选上。
  - 然后剩下的自由发挥，选出一系列的类型。
  - 同时特判了n=2的情况。
- 忽略了前面操作的一些铺垫，可以构造出一些解。
- 考虑到另外一些解，导致最终只是少选了一位的情况。
  - 思路进行曲：对这些解进行一个提炼，简化关注的解空间。

<img src="E:/NOTE_of_coding/photo/%E8%8D%89%E7%A8%BF/2022%2012%203.png" style="zoom: 80%;" />

- 综上： 比较对角线上各个值得大小即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

void MAIN();
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    MAIN();
}
typedef long long ll;
const int maxn = 2e5 + 10;
//------code-----٩(ˊωˋ*)و ------靓仔代码-----٩(ˊωˋ*)و ----talk is cheap , show me the code--------

ll a[210][210];

void MAIN()
{
    int n;
    cin >> n;
    ll temp = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
            temp += a[i][j];
        }
    //下面是进行一次计算ans的情况。
    //比较出对角线上各个元素的大小。
    ll mx = 2e9;
    for (int i = n; i >= 1; i--)
        mx = min(a[i][n + 1 - i], mx);
    cout << temp - mx << '\n';
}
```

#### 最起初，我并没有关注这种特定的解的形式。

- 但是只要发现一个就好想了。
- 争取走的格子最少，走完。这样的思想来走。就可以慢慢的构造出解来。
