#### A.Doremy's IQ

[address](https://codeforces.com/problemset/problem/1707/A)

```txt
给出一组数。
定义一个变量
初始状态下，该变量为q;
现在遍历数组。
对于每一个数，有两个选择：
选择一个大于q的数，当前q--;
其它情况不变：

寻找一个方案，使得选择的数的数量最多。
```

#### $solve$

- 二分搜索：

```txt
对于一个最优方案，总有这样一个特征：
存在一个索引 X，
当i小于 x时，所有的好比赛都已经打了。
当i大于等于 x时无论比赛降不降智都打了。
x越小，其答案越大。


```

- 想办法发现一些东西
  - 第一个，探究解空间，来发现规律。
  - 对于任何一个解，一天的选择可以有多种属性标记。具体的定义如下：
    -  $a:没降智商，选择了的比赛。$
    - $b:会降智商，但是没有选择的比赛。$
    - $c:会降智商，但是勇敢选择的比赛。$
    - $d:智商已经为0，完全没有能力向下选择的情况。$

```txt
aaabbccccbb
-> aaabbbbcccc或 aaabbbbccaa;或 aaabbbbcccc
保持相同；
cccaaabcaca->
b??aaaccaca->  b(aa)aaaccaca;
           ->  b(ac)aaaccaca
           ->  b(ca)aaaccaca
           这里有什么启发？更优。
babaccdd->相当于 babaccbb
和上面情况相似。


对于一个最优方案，总有这样一个特征：
存在一个索引 X，
当i小于 x时，所有的好比赛都已经打了。
当i大于等于 x时无论比赛降不降智都打了。
x越小，其答案越大。

理由：像上面几种类型（有后缀d类型，有前缀后缀b类型。）的结构，都可以在上面找到一个上面这种形式的等价替换。
    且可以发现，当前面的数越大，前面得到的a类可能性就越大，同时 因为后面所有都已经选了。
    所以一个完整的解空间，就是讨论上面的情况，而且，当x越小时，ans越大。
    直接dfs找出最小x即可。当x小到一定程度时，会出现后缀d。
    其下方，所有的x都呈现这一个特性。
    当x足够大时，其后方都可以选。
    比它更大的x同时满足这一个性质。
    综上，满足一个二分搜索的前提：
                            1.最优在分界点。
                            2.同时，连续单调的特性。
```

#### $code$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int n, q;

int a[maxn];
bool choose[maxn];

bool check(int mid)
{
    int t = q;
    for (int i = 1; i < mid; i++)
        if (a[i] <= t)
            choose[i] = true;
        else
            choose[i] = false;
    for (int i = mid; i <= n; i++)
        if (a[i] <= t)
            choose[i] = true;
        else
            choose[i] = true, t--;
    if (t < 0)
        return false;
    else
        return true;
}

void solve()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int low = 1, high = n;
    while (low < high) //
    {
        int mid = (low + high) >> 1;
        if (check(mid))
            high = mid;
        else
            low = mid + 1;
    }
    check(high);
    for (int i = 1; i <= n; i++)
        cout
            << choose[i];
    cout << '\n';
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

- 关于解空间的分析：
  - 像这种解空间的分析，解空间比较大，其中涉及的量是数字，变化也非常大。入手难度探究上，遇到比较多的麻烦，不能够构造出一个非常清晰的解空间研究。
  - 向上面，对于一个方案，一个步骤可能存在多种选择，用一个抽象的符号来表述出一个选择，然后从整体上来分析一个等效。
- 一个完全的解空间，可能并不显示出，二分搜索前提，但是从完全的解空间中，可以找出一些特征解之类的等效解系列，然后可以发现出，它们就符合了一个解空间中的二分搜索的前提特征。
  - 解空间单调的特征。
  -  对于解答的$check()$函数，前面部分和后面部分是两类的结果。
  - 关注的最优解，是在分界点上。

