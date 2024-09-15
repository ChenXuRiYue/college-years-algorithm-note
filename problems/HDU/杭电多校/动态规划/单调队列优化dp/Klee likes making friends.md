# Klee likes making friends

[Klee likes making friends - HDU 7296 - Virtual Judge (vjudge.net)](https://vjudge.net/problem/HDU-7296)

简介：

Klee likes to make friends,now there are n people standing in a line and Klee can make friend with the $i^{th}$ people with a cost of $a_i$, Klee has a principle that at least 2 out of m consecutive people must be her friends.Please help her calculate the minimum amount of costs she needs.

### solve

参考： [2023 杭电多校2 个人题解 ABCDEFGHIJKL 已更新完毕 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/644908897)

如果只是m个中取一个。就是经典的单调队列优化问题。但是这里取两个，分析其可行解空间的特征。发现所有可行解都满足，一个选择元素附近两空隙处的长度小于m - 1。否则必定不合法。反之必定合法。
**状态设计：**
$f_{i , j}$ 表示选择第i个人， 和上一个选择的人的距离为j的可行解中的最小花费。
**状态转移：**
$f_{i , j} = min(f_{i - j + 1} , 0...(m - j))$
**状态优化**
发现其实就是一个前缀和优化的问题。

但是该问题非常的毒瘤， 一秒跑1E8并且还卡常。机子也非常慢；

**剩下集中精力解决的问题：**

1. 解决空间限制问题： 该问题可以使用滚动数组优化。发现计算一个状态时，只可能用到长度相距离为1 ..... m - 1以内的状态。因此我们基于长度为m的数组进行dp即可。发现每一个状态其实都是偏移的过程。因此， 用mod使其变成一个环，完成滚动即可。（对滚动的空间模式选择上 ， 下功夫。）

2. 卡常：

### code

下面这份代码是tle的。总体上，其常数可以优化的点为：

1. 减少函数块中的if。
   1. 手动初始化。 减少pre的判断。
   2. 下标设置上： 前缀和的有效段从1开始，减少判断。
2. 拼一个假想的0.然后便捷的求出ans.

```cpp
const int N = 20000 + 10;
const int M = 2000 + 10;
int f[M] , mi[M][M] , a[N];
void solve() {
    int n , m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)cin >> a[i];
    n++; a[n] = 0;
    for (int i = 1; i <= n; i++) {
        int cur = (i - 1) % m + 1;
        for (int j = 0; j < m - 1; j++) {
            int pre = (i - j - 1);
            if (pre <= 0) {
                f[j] = a[i];
                goto end;
            }
            pre = (pre - 1) % m + 1;
            f[j] = mi[pre][m - j - 2] + a[i];
end:
            if (j > 0) mi[cur][j] = min(mi[cur][j - 1] , f[j]);
            else mi[cur][0] = f[0];
        }
    }
    int ans = inf;
    for (int i = 0; i < m - 1; i++) {
        ans = min(ans , f[i]);
        // cout << f[i] << " ";
    }
    // cout << "\n";
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
}
```

### code改进：

```cpp
const int N = 20000 + 10;
const int M = 2000 + 10;
int f[M] , g[M][M] , a[N];
void solve() {
    int n , m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)cin >> a[i];
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < m; j++) g[i][j] = inf;
        for (int j = 1; j < i; j++) {
            f[j] = a[i] + a[i - j];
            g[i][j] = min(g[i][j - 1] , f[j]);
        }
    }
    /*f[i][j] : 表示距离为 i , 与上一个距离为j*/
    n++; a[n] = 0;
    for (int i = m + 1; i <= n; i++) {
        int cur = (i - 1) % m + 1;
        for (int j = 1; j < m; j++) {
            int pre = (i - j - 1) % m + 1;;
            f[j] = g[pre][m - j] + a[i];
            g[cur][j] = min(g[cur][j - 1] , f[j]);
        }
    }
    int ans = inf;
    for (int i = 1; i < m; i++) {
        ans = min(ans , f[i]);
    }
    cout << ans << "\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
}
```
