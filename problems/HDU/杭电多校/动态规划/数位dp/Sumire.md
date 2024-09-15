# Sumire

[Sumire - HDU 7214 - Virtual Judge (vjudge.net)](https://vjudge.net/problem/HDU-7214)
Calculate
$\sum _{i=l}^rf^k(i,B,d)$
where f(x,B,d) means the number of times that digit d appears in the base-B form of x (ignoring leading zeros).
In this problem, we consider that $0^0=0$.

### solve

**第一个乱搞的思路：**
设计角度： 直来直去，能记就记：

**状态设计：**

$f_{cur , j , 2 , 2}$ : 表示从cur....1 ， D出现的次数为j次， 当前是否贴上界 ， cur之前是否全为前导0的的数字个数。

**状态转移方程：**

1. 枚举当前cur数位上放置什么数码： 于是就可以枚举前缀的所有方案进行统计了：

```cpp
int mx = limit ? d[cur] : B - 1;
for (int i = 0; i <= mx; i++) {
    int x = cur - 1,  y = limit && (i == mx);
    int z = zero && (i == 0);
    dfs(x, y, z);
    int move = 0;
    if (i == 0 && D == 0 && z) move = 0;
    else if (i == D) move = 1;
    for (int j = 0; j <= len; j++) {
        // cout << f[x][y][j][z][zero] << ' ';
        add(f[cur][j + move][limit][zero] , f[x][j][y][z]);
    }
}
```

但是复杂度是 $O(N^2 \times N)$ ，（状态数，加上转移的花费）在多组询问之下，显然是无法通过的。

----

1. 记录状态：
**参考：**

1. [“杭电杯”中国大学生算法设计超级联赛（7） Sumire（数位dp）_sumire题解_zzzgw666的博客-CSDN博客](https://blog.csdn.net/qq_56877339/article/details/126288440)
2. [2022杭电多校第七场题解_sumire 数码 dd 在 xx 的 bb 进制表示下出现的次数_anonyacm的博客-CSDN博客](https://blog.csdn.net/weixin_46155777/article/details/126677406)
3. [2022杭电多校7 萌新向题解 B C D F H - 哔哩哔哩 (bilibili.com)](https://www.bilibili.com/read/cv18018497)

**状态设计：**

追求每一个状态只需要花费1次的复杂度转移： 上述状态设计中，是从局部整体的角度出发的。这样将子问题合并时，难以避免较大的开销：

整体上进行状态设计：
$f_{cur , j , 2, 2}$ :表示当前枚举到第cur位 ， 当前已经有j个数码，是否贴上界，是否有前导0。所有符合条件的后缀方案（数字）中的整体的贡献。
**状态转移方程：**
枚举后缀，发现数码的后缀数其实是等效的：下面分几种情形讨论：
关注 , 定义几个关键属性：

1. mx : 当前限制下，可以枚举数码的最大值；
2. limit : 当前的前缀是否贴上界：
3. zero : 当前的前缀是否为前导0.
4. D ： 当前问题下的数码：

分以下几类进行讨论：其实就是查找子树相同的结构：
具体转移看下述代码：

**tips**

1. 关键细节1 ： 前导零是有必要记录的： 如果当前需要记录的数码是0.如果前面是前导0 ， 这会影响统计。

### 生长思考：

1. 其实可以认为，数位dp和树形dp是极其相似的。其区别为，树形dp中面对的资源： 树形结构是给出的，并且是少有规律可行的。二数位dp，从第一位开始搜索，这天然的搜索树结构：其规模是指数级别的庞大，但由于进制，数位等事物的规律，也是有迹可循。

把握数位dp中的搜索树 ： 所需要强调关注的问题：

1. 边界： 即limit , 这个搜索分支和其它的不一致。
2. 其它分支： 如非limit : 这一类中同等地位下，后续的搜索树形是一致的。要善于使用这些结构：

如上模型，状态定义中。我们定义的整个问题就是，给子树贴上pre ，limit , zero 之后，其最后所有的分支代表的数字的贡献。显然是有大量重复的 ， 且可转移的。

###  code

**正解 ： **

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define int ll
const int N = 1E6 + 10;
const int mod = 1E9 + 7;
vector<int> d;
int k, B, D;
// 当前第几个位置， 已经有多少个， 是否贴上界：
int f[64][64][2][2];
int len;
int qpow(int x , int n) {
    if (x == 0 && n == 0) return 0;
    int res = 1;
    while (n) {
        if (n % 2) res = 1LL * res *  x % mod;
        x = 1LL * x * x % mod;
        n /= 2;
    }
    return res;
}
void add(int& a, int b) {
    a = a + b;
    if (a >= mod) a -= mod;
    if (a < 0) a += mod;
}
int dfs(int cur/*当前第几位*/ , int pre, bool limit /*是否贴上界*/, bool zero) {
    if (cur == 0) return qpow(pre , k);
    int& res = f[cur][pre][limit][zero];
    if (res != -1) return res;
    res = 0;
    int mx = limit ? d[cur] : B - 1;
    // 几个分类点：
    if (D == 0) {
        if (mx == 0)add(res , dfs(cur - 1 , pre + !zero , limit , zero));
        else {
            /*mx*/
            add(res , dfs(cur - 1 , pre , limit , false));
            /*非D， 非mx*/
            add(res , 1LL * dfs(cur - 1 , pre , false , false) * (mx - 1) % mod);
            /*D*/
            add(res , dfs(cur - 1 , pre + !zero , false , zero));
        }
    } else {
        if (D > mx) {
            /*mx*/
            add(res , dfs(cur - 1 , pre , limit , false));
            /*非mx*/
            add(res , 1LL * dfs(cur - 1 , pre , false , false) * mx % mod);
        } else if (D == mx) {
            /*mx*/
            add(res , dfs(cur - 1 , pre + 1 , limit , false));
            /*其它：*/
            add(res , 1LL * dfs(cur - 1 , pre , false , false) * mx % mod);
        } else if (D < mx) {
            /*mx*/
            add(res , dfs(cur - 1 , pre , limit , false));
            /*D*/
            add(res , dfs(cur - 1 , pre + 1 , false , false));
            /*其它*/
            add(res , 1LL * dfs(cur - 1 , pre , false , false) * (mx - 1) % mod);
        }
    }
    return res;
}

ll solve(ll x) {
    memset(f , -1 , sizeof f);
    d.clear();
    d.push_back(0);
    while (x) {
        d.push_back(x % B);
        x /= B;
    }
    len = sz(d) - 1;
    return  dfs(len, 0 , 1 , 1);
}
/*
1
2 2 0 1 5

1
1 4 3 11 45

1
10 14 11 19 198
*/
void work(int testNo)
{
    ll L, R;
    cin >> k >> B >> D >> L >> R;
    cout << ((solve(R) - solve(L - 1)) % mod + mod) % mod << "\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; i++)work(i);
}
```

**很天真的一个复杂度：** 每一个状态的转移是n次；因此做一次的复杂度是$(O(log^3_{B}R))$ , 接近1E6

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 1E6 + 10;
const int mod = 1E9 + 7;

vector<int> d;
int k, B, D;

// 当前第几个位置， 已经有多少个， 是否贴上界：
int f[64][64][2][2];
bool vis[64][2][2];
int len;

int qpow(int x , int n) {
    int res = 1;
    while (n) {
        if (n % 2) res = 1LL * res *  x % mod;
        n /= 2;
        x = 1LL * x * x % mod;
    }
    return res;
}

void add(int& a, int b) {
    a = a + b;
    if (a >= mod) a -= mod;
}

void dfs(int cur/*当前第几位*/, bool limit /*是否贴上界*/, bool zero) {

    if (vis[cur][limit][zero]) return;
    vis[cur][limit][zero] = true;
    if (cur == 0) {
        f[cur][0][limit][zero] = 1;
        return;
    }
    for (int j = 0; j <= len - cur; j++) {
        f[cur][j][limit][zero] = 0;
    }

    int mx = limit ? d[cur] : B - 1;
    for (int i = 0; i <= mx; i++) {
        int x = cur - 1,  y = limit && (i == mx);
        int z = zero && (i == 0);
        dfs(x, y, z);
        int move = 0;
        if (i == 0 && D == 0 && z) move = 0;
        else if (i == D) move = 1;
        for (int j = 0; j <= len; j++) {
            // cout << f[x][y][j][z][zero] << ' ';
            add(f[cur][j + move][limit][zero] , f[x][j][y][z]);
        }
    }
}

ll solve(ll x) {

    // memset(f, 0, sizeof f);
    memset(vis, false, sizeof vis);

    d.clear();
    d.push_back(0);
    while (x) {
        d.push_back(x % B);
        x /= B;
    }
    len = sz(d) - 1;
    dfs(len, 1, 1);
    int ans = 0;
    for (int j = 1; j <= len; j++) {
        // cout << f[len - 1][0][j][1][1] << " \n"[j == len - 1];
        add(ans, 1LL * qpow(j , k) * f[len][j][1][1] % mod);
    }
    return ans;
}
/*
1
2 2 0 1 5


1
1 4 3 11 45


1
10 14 11 19 198


*/
void work(int testNo)
{
    ll L, R;
    cin >> k >> B >> D >> L >> R;
    cout << (solve(R) - solve(L - 1) + mod) % mod << "\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; i++)work(i);
}
```
