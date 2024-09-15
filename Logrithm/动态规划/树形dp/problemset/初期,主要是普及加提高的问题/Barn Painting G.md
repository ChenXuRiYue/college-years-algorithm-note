#### Barn Painting G

[Barn Painting G](https://www.luogu.com.cn/problem/P4084)

##### 简介

```txt
给定一颗 N个节点组成的树，你要给每个点涂上三种颜色之一，其中有K个节点已染色，要求任意两相邻节点颜色不同，求合法染色方案数。
```

#### 20min

```txt
定义f[i][j].表示当前节点i染色染成j的时候，的子树的方案总数。
那么
f[i][1]-->累乘sum->f[son][k!=1]。
如果当前子节点已经染色，那么不为这种颜色的都变成0；及时处理即可。
将f[i][j]初始化为1刚刚好。
于是状态转义，以及初始化问题都已经解决了。
```

#### $code$

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
const int maxn = 1e5 + 10;
//------code-----٩(ˊωˋ*)و ------靓仔代码-----٩(ˊωˋ*)و ----talk is cheap , show me the code--------

int c[maxn];   //表示当前颜色。如果为0说明没有颜色。
ll f[maxn][5]; //

struct tree
{
    int no;
    int to;
} e[maxn << 1];
int head[maxn], tot; //表示头节点
void add(int x, int y)
{
    e[++tot].to = head[x];
    e[tot].no = y;
    head[x] = tot;
}

int mod = 1e9 + 7;

void dfs(int now, int fa) //初始化，根部节点的初始化。
{
    for (int x = head[now]; x; x = e[x].to)
    {
        int sum[4]{};
        if (e[x].no != fa)
        {
            dfs(e[x].no, now);
            sum[1] = (f[e[x].no][2] + f[e[x].no][3]) % mod;
            sum[2] = (f[e[x].no][1] + f[e[x].no][3]) % mod;
            sum[3] = (f[e[x].no][1] + f[e[x].no][2]) % mod;
            f[now][1] = (f[now][1] * sum[1]) % mod;
            f[now][2] = (f[now][2] * sum[2]) % mod;
            f[now][3] = (f[now][3] * sum[3]) % mod; //分布计算原理；
        }
    }
    if (c[now])
        for (int i = 1; i <= 3; i++)
            if (i != c[now])
                f[now][i] = 0; //当前颜色下的为0；
}

void MAIN(){
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        f[i][1] = f[i][2] = f[i][3] = 1;
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }
    for (int i = 1; i <= k; i++)
    {
        int x, y;
        cin >> x >> y;
        c[x] = y;
    }          //表示当前点的染色情况。
    dfs(1, 0); //怎么进行初始化？
    //可以将所有都初始化为1.然后自然，
    cout << (f[1][1] + f[1][2] + f[1][3]) % mod << '\n';
}
```



