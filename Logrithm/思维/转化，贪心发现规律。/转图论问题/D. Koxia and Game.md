https://codeforces.com/contest/1770/problem/D

Koxia和Mahiru正在玩一个有三个长度为n的数组a、b和c的游戏。a、b和c中的每个元素都是1到n之间的整数。

游戏由n轮组成。在第i轮，他们进行以下动作:

设S为多集{ai,bi,ci}。
Koxia选择从多重集S中移除一个元素。
Mahiru从多集S中剩下的两个整数中选择一个。
设di为Mahiru在第i轮中选择的整数。如果d是一个排列†，Koxia赢。否则，马赫鲁赢了。

目前，只有数组a和b被选中。作为Koxia的狂热支持者，您希望选择一个数组c，这样Koxia将获胜。以998244353为模，计算这样的c的个数。

注意，Koxia和Mahiru都是最佳玩法。

†长度为n的排列是由n个不同的整数以任意顺序从1到n组成的数组。例如，[2,3,1,5,4]是一个排列，但[1,2,2]不是一个排列(2在数组中出现了两次)，[1,3,4]也不是一个排列(n=3，但数组中有4个)。

#### 20 mins

无

题解：

引理 1 Koxia应当移除恰当的元素，使得mahiru的两个选择相同。

- 如果最终mahiru选择了一个排列，但是过程之中有某一步有两个选择就意味着mahiru具有最优策略使得没有选择一个排列。

引理 2 令 是一个长度为 的数组，其中 是 和 中的一者。Koxia 获胜当且仅当 可 能是一个排列。



转化为一个图上的问题，对于每一组A,B 上建立边。于是问题转变为了给每一条边分配方向，使得每一个数字都被指到，那么最终必然可以构造出一个排列。

研究具体的选择方案，我们关注每一个连通块的环

- 附加边成自环：此时c取任何值都不影响结果。
- 附加边和其他树边一起形成环。当前环中有两种方式：逆时针或者顺时针方式。

#### code

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;

int fa[maxn], passed[maxn], cunt_e[maxn], cunt_v[maxn], a[maxn], b[maxn];
int n;
int self_loop[maxn];

int mod = 998244353;

void init()
{
    iota(fa + 1, fa + 1 + n, 1);
    fill(cunt_e + 1, cunt_e + n + 1, 0);
    fill(cunt_v + 1, cunt_v + n + 1, 1);
    fill(self_loop + 1, self_loop + 1 + n, 0);
    fill(passed, passed + 1 + n, 0);
}

int getfa(int x)
{
    return fa[x] = (fa[x] == x ? x : getfa(fa[x]));
}
void merge(int x, int y)
{
    x = getfa(x), y = getfa(y);
    fa[x] = y;
    cunt_e[y] += cunt_e[x];
    cunt_v[y] += cunt_v[x];
    self_loop[y] |= self_loop[x];
}

void solve()
{
    cin >> n;
    init();

    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
    {
        if (getfa(a[i]) != getfa(b[i]))
            merge(a[i], b[i]);
        cunt_e[getfa(a[i])]++;
        if (a[i] == b[i])
            self_loop[getfa(a[i])] = 1;
    }
    ll ans = 1;
    for (int i = 1; i <= n; i++)
    {
        int par = getfa(i);
        if (passed[par] == 0)
        {
            passed[par] = 1;
            if (cunt_e[par] != cunt_v[par])
                ans = 0;
            else
                ans = ans * (self_loop[par] ? n : 2) % mod;
        }
    }
    cout << ans << '\n';
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









