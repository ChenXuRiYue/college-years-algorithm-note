[248.G](https://www.luogu.com.cn/problem/P3146)

```txt
对于一个数组，
将两两相同的数字进行合并；
合并之后，变成一个原数字上加1的数字。
求总多方案之中得到方案的最大值。
```

#### $20mins$

```txt
最初设计的状态为
f[i][j][k];是否可以将[i,j]进行合并，然后得到大小为k的数字。
于是复杂度高达O(n^4)
发现如果可以合并一个区间，
最终它的数字必然只有唯一解。
于是直接的枚举，几段区间，能合就合。不用担心后效性。
记录最大解即可。
```

```cpp
void MAIN(){
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        ans = max(ans, a[i]);
        f[i][i] = a[i];
    }
    for (int len = 2; len <= n; len++)
        for (int low = 1, high = low + len - 1; high <= n; low++, high++) //这里怎么优化？
            for (int mid = low; mid < high; mid++)
            {
                if (f[low][mid] == f[mid + 1][high] && f[low][mid] != 0)
                    f[low][high] = f[low][mid] + 1, ans = max(ans, f[low][high]);
            }
    cout << ans << '\n';
}
```



