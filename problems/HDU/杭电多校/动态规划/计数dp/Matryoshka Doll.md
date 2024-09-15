# Matryoshka Doll
[Matryoshka Doll - HDU 7239 - Virtual Judge (vjudge.net)](https://vjudge.net/problem/HDU-7239)

简介：给定一个数组， 将该数组分成k个有序序列。 对于每一个序列要保证，$a_{i + 1} >= a_i + R$ 其中R给出。保证题意给出的数组是升序的。问有多少种划分方法满足题意？

### solve

大的问题没有头绪，那就尝试发散出简化版的问题，并且从中得到启发：

==**简化版问题：**==
忽略相邻元素之间的关系：朴素的划分成k组的方案数；
**状态定义：**
$f_{i ,j}$表示： 前i个元素划分成j组的方案数。
**状态转移：**
$f_{i, j} - > f_{i - 1, j - 1} , f_{i - 1 , j} * j$ , j > 0
**边界处理**
$f_{0 ,0 } = 1$

==**启发**==

单纯的转移，上述是有很多不合法方案的。有两种方法：

1. 转移过程中，记录更细节，或者更本质，更全面的属性。
2. 容斥；

这里考虑使用容斥来解决该问题：

**状态定义：**
$f_{i ,j}$ 表示考虑将1到i个元素，分为j组。合法的方案数。

**状态转移**
如简化版本一般的转移：
$f_{i ,j}->f_{i - 1 , j - 1} , f_{i - 1, j} * j$

观察重复方案的具体细节： 

1. 就是接在了不该接的一段中。
2. 这一类不能接的元素之间肯定都分别作为某一组的头部（因为它们本身显然是不可相邻的。）
3. 即每一个具体的方案中，只有j - l个头部可以接上当前考察的元素；（i之前有多少个元素是在$a_i$ - r + 1之内的。）

实现上，可以使用双指针，用较低的复杂度实现不合法范围的计算。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 5E3 + 10;
const int mod = 998244353;

void add(int& a , int b) {
    a += b;
    if (a >= mod) a -= mod;
}
void dec(int& a , int b) {
    a -= b;
    if (a < 0) a += mod;
}
int f[N][N] , a[N];
void work(int testNo)
{
    int n ,  k , d;
    cin >> n >> k >> d;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    // vector<vector<int>> f(n + 1 , vector<int>(k + 1 , 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)
            f[i][j] = 0;
    f[0][0] = 1;
    for (int i = 1 , l = 1; i <= n; i++) {
        for (int j = 1; j <= min(i , k); j++) {
            add(f[i][j] , f[i - 1][j - 1]);
            while (l < i && a[l] <= a[i] - d)
                l++;
            add(f[i][j] , 1LL * f[i - 1][j] * (j - (i - l)) % mod);
        }
    }
    cout << f[n][k] << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++)work(i);
}
```

