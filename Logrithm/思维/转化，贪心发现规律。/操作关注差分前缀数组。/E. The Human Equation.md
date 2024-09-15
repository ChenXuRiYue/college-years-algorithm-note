https://codeforces.com/contest/1775/problem/E



对于任何一个操作。

如果选择奇数位-1。可以发现相当于在前缀数组上进行区间减。反之等效于在区间上进行区间加操作。

所以问题转变成了，连续的区间加操作，区间减操作。使得前缀数组变成0。

我们处理最大的高度的时候，区间减，顺便把其它的也全部减掉。操作数为max(0,max_elements)

同理处理最小的时候，把其它的负数区间也处理掉。操作数为min(0,min_elements);



##### 生长思考

感受这两个问题的等效性。

1. 观察到所有的数组上的原始操作，都可以对应一个前缀数组上的操作。一一匹配。
2. 一一匹配的两方面的操作数是相等。
3. 所以前缀数组的下界对应着数组操作的下界。

​                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;

int a[N];
ll sum[N];

void work(int testNo)
{
    int n;
    cin >> n;
    ll mx = -1E18;
    ll mi = 1E18;
    for ( int i = 1; i <= n ; i++)
    {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
        mx = max(mx , sum[i]);
        mi = min(mi , sum[i]);
    }
    cout << max(0LL,mx) - min(mi, 0LL) << '\n';
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++)work(i);
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

