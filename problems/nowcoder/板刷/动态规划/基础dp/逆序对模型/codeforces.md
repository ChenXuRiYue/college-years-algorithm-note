**codeforces**

(https://ac.nowcoder.com/acm/problem/21314)

#### 简介

看题就行。
#### solve

1. 观察所有解空间 ， 枚举任何解。对于一组具体的方案。可以先考察问题的解决顺序 ，优秀子集。各种问题的解决顺序 ， 必然满足一些上界。
   1. 优秀子集这里自定义为 ：所有枚举的解都可以在这个子集中找到更优的等效解。

顺序的探究：
对于一组解中，任意相邻的任务(假设存在两个以上的任务。不妨标记其为1 ， 2。其中分别完成时间为$t_1 , t_i$，价值损失速度为$p_1 , p_2$。开始做第一个任务时候。其分数和为sum.
关注两个量：$s_{1 , 2}$表示先1后2.$s_{2,1}$反之。
$$
s_{12} = sum - t_1p_1 - (t_1 + t_2)p_2\\
s_{21} = sum - t_2p_2 - (t_1 + t_2)p_1\\
s_{12} - s_{21}=t_2p_1-t_1p_2.\\
s_{12}-s_{21}>=0\\
\frac{p_1}{t_1}>=\frac {p_2}{t_2}
$$

利用这个递推序列排一个序。满足任何相邻的元素都满足上述关系。

2. 利用上述规则

   1. 考察任何一个方案$a$。并且从优秀子集中的方案$b$映射到该方案。
   2. 通过对b不断地调整。发现一种总分数一直减少的方案可以构造到该方案中。而一个方案只有一个结构。上述构造逐步计算的过程是等价过程。

3. 综上，在上述顺序的数组上做01背包即可。

   $f_{i , j}$表示j状态下 ,完成j道题的最大方案。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;
const ll inf = 1E18;

ll t[N] , p[N] , f[N] , v[N];
int id[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n , T; cin >> n >> T;
    for (int i = 1; i <= n; i++)
        cin >> v[i];
    for (int i = 1; i <= n; i++)
        cin >> p[i];
    for (int i = 1; i <= n; i ++)
        cin >> t[i];
    iota(id , id + n + 1 , 0);
    sort(id + 1 , id + 1 + n , [&](int i , int j) {
        return 1.0 * p[i] / t[i] > 1.0 * p[j] / t[j];
    });
    //  cerr << id[1] << '\n';
    //状态设计表示刚好完成i任务。j时间下的最大成就。
    ll ans = 0;
    for (int x = 1; x <= n; x++) {
        int i = id[x];
        for (int j = T; j  >= t[i]; j--) {
            f[j] = max(f[j] , f[j - t[i]] + v[i] - j * p[i]);
        }
    }
    for (int i = 0; i <= T; i++) {
        ans = max(ans , f[i]);
    }
    cout << ans << '\n';
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

#### 生长思考：

1. 非常精彩的解空间压缩。

   这里的解空间优化。转换成了一个01背包问题。关注了一个优秀的解集。而这个解集就是做01背包的解集。

   
