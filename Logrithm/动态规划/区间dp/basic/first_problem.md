[石子合并](https://www.luogu.com.cn/problem/P1775)

#### 问题简介

```txt
将石子合并，需要花费一定的代价。其中，代价和为a两个石头的数目之和。问最小代价使他们合并成一个石头。
```

###### 自己的分析

```txt
首先考虑一些解空间
就是一个计数的问题，一共分为n步，一共有（n-1）!次的选择。虽然会有重叠性。但是这是一个有序的分步计数枚举。

考虑小规模的问题：
d{i,j}i到j合并的最小代价。
边界的合并方式可能有若干种。
d{i,j}=max(d{i,k}+d{k+1,j},i<=k<=j-1)+sum[i,j].
然后tm直接出来啦！！！

20min后出来个屁
状态方程写错
改了一下感觉没问题：
初始化出错；
正确的初始化应该为
f[i][i]=0;
而不是f[i][i]=a[i];

然后就过啦。
也算自己完成了状态迁移方程的构建；
但是初始化上出了一些小问题。
```

```cpp
for (int i = 2; i <= n; i++)// dp区间的长度，必须从小到大。来进行一个动态规划。
        for (int j = 1; j <= n - i + 1; j++) 
            for (int k = j; k <= j + i - 2; k++)
                f[j][j + i - 1] = min(f[j][j + i - 1], f[j][k] + f[k + 1][j + i - 1] + sum[j + i - 1] - sum[j - 1]);
```

#### code

```cpp
int f[maxn][maxn];
int sum[maxn]; //前缀和。
const int inf = 1e9;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            f[i][j] = inf;
    for (int i = 1; i <= n; i++){
        cin >> f[i][i];
        sum[i] = sum[i - 1] + f[i][i];
        f[i][i] = 0;
    }
    for (int i = 2; i <= n; i++)             // dp区间的长度，必须从小到大。来进行一个动态规划。
        for (int j = 1; j <= n - i + 1; j++) //区间的首部。
            for (int k = j; k <= j + i - 2; k++)
                f[j][j + i - 1] = min(f[j][j + i - 1], f[j][k] + f[k + 1][j + i - 1] + sum[j + i - 1] - sum[j - 1]); //合并这两个使用的最小代价。
    cout << f[1][n] << '\n';
}
```

