#### A. Tokitsukaze and Strange Inequality

[address](https://codeforces.com/problemset/problem/1677/A)

#### statu

```txt
给定一个排列，关注一种序列
pa pb pc pd i<j<k<l
满足条件 pa<pc  ,pb>pd;
求出满足上序列的组数。
```

#### 30min

```txt
直接暴力枚举，枚举四个数，复杂度为 n^4

转化问题：
将一个关系表示为一个一条线。找出有多条线是相交的并且满足，第一种线在前方。
第二种线在后方，同时一定要有相交段。
动态规划找出第二条线的种线的数量。 
d[i][j]表示头部在i,j尾部在j+1....n的线的数量。
小规模问题是 内嵌的更小区间 d[i-1][j];然后同时找新增加的关于 i作为首部的贡献。
枚举i -> j -> 寻找j的贡献。一共是O(n^3);
计算ans  先枚举第一段，然后是第二段。直接算出来O（n^3）

问题在于，怎么优化使得前面的O(n^3)的复杂度变低。
```

##### 题解

```txt
f[j]表示后一种形式中从j+1---n中小于a[j]的个数。
然后枚举a c。注意顺序：先枚举c，再枚举a。
这样本质上选择了一种使用数据的过程，计算c时  ，1....c中的都已经不需要再计算，此时f[i]应该为（i<=c）c...n中小于a[i]的元素的数量。
枚举c时就对f进行处理即可。这样累
```

```cpp
int a[maxn];
int f[maxn];
int sum[maxn];
void solve(){
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            if (a[i] > a[j])
                f[i]++;
    ll ans = 0;
    for (int c = 2; c <= n; c++)
    {
        for (int i = 1; i < c; i++)
            if (a[i] > a[c])
                f[i]--;
        sum[c] = 0;
        for (int i = c - 1; i >= 2; i--)
            sum[i] = sum[i+1] + f[i];
        for (int i = 1; i <= c - 2; i++){
            if (a[i] < a[c])
                ans += sum[i + 1];
        }
    }
    cout << ans << '\n';
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

