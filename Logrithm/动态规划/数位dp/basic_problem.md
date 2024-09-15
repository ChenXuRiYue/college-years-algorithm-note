#### $\huge 笔记简述$

- 数位$dp$的启蒙问题；
- 下面的问题，主要使用记忆化送搜索的方法实现。



#### $\huge 1\quad数字计数$

- 难度： 提高+，较难。

[数字计数](https://www.luogu.com.cn/problem/P2602)

```txt
给定一个区间，求出该区间内，各个数码的出现数字和。
```

#### 25min

```txt
采用动态规划的方式记录一些结果。

对于一个数而言，低位向高位逐渐递进的过程中。位之间的变化是相似的。于是一些结果可以利用来计算更大的区间的一个范围。
```

#### $solve$

```txt
d[i]表示放前i位的每个数字出现的个数。
那么 
d[i]=10*d[i-1]+10^(i-1)
现在没有考虑前导0.有重复贡献。

注意
这一些贡献可以求出来：
假定i为最大长度。前导0的贡献为
m[i-1]+m[i-2]+....m[1];
分步计数原理。当前k位确定之后，后缀的所有的可能后缀个数为 m[i-k]

最长：
len位
1,,,,a[i]-1第一位：m[i-1];
//设最高位的数字为 head
0 < head < a[len];
其后缀就是将后位填满的所有可能。每个数字的贡献=f[len-1];

当head=a[len];
a[len]的贡献为n-temp-a[i]*m[i-1];

形象化表述：
想象将数字从小到大排。往上叠高。
那么发现一个统一的规律。
向下遍历
a[len-1]-->a[1];


当前位上： 如果小于a[i];
后缀是随意满可能的。
d[j]+=a[i]*f[i-1];//一共有a[i]种小于a[i]的数，0也是合法的。
对于当前位本身类型的个数：m[i-1]的贡献。

当当前位等于a[i]时问题转化为，求00000---temp-a[i]*m[i-1]中各项的贡献。
这样又回到了上面的过程。
右边上矩形不断地变小。位数为1.


(a[i]-2)*f[i-1]。


a[i]位为首位的数字的贡献；
a[i]*m[i-1]----mmax;

temp=n;

直到为到第一位。

更低位的数字的各个码的贡献：
发现d[len-1]中和更低位的贡献非0的数码贡献相等。
而其中的0，多余的部分就是m[i-1]+m[i-2]+m[i-3]...m[1];
```

#### code

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int maxn = 20;

ll f[maxn];
ll m[maxn];
int a[maxn], len;
ll ans1[maxn], ans2[maxn];

void solve(ll s, ll *ans)
{
    ll temp = s;
    len = 0;
    while (s)
        a[++len] = s % 10, s /= 10;
    for (int i = len; i >= 1; i--)
    {
        for (int j = 0; j < 10; j++)
            ans[j] += a[i] * f[i - 1];
        for (int j = 0; j < a[i]; j++)
            ans[j] += m[i - 1];
        temp -= m[i - 1] * a[i];
        ans[a[i]] += temp + 1;
        ans[0] -= m[i - 1];
    }
}

int main()
{
    ll s, t;
    cin >> s >> t;
    m[0] = 1;
    for (int i = 1; i <= 13; i++)
        m[i] = m[i - 1] * 10, f[i] = 10 * f[i - 1] + m[i - 1];
    solve(s-1, ans1);
    solve(t, ans2);
    for (int i = 0; i < 10; i++)
        cout << ans2[i] - ans1[i] << ' ';
   cout << '\n';
}
```

#### $\huge 2\quad不要62$

```txt
区间范围之内，不会出现62 和4的数字的个数。
```

#### 题解

```txt
记忆化搜索：
dfs(int x,bool limt,bool can2);
这一个状态向下搜索。
返回满足该状态以及后题意的后缀总数。
```

#### 调试了半天的一个迷糊bug

- 关于前后$dfs$函数的比较：
- 下方是错误的代码。

```cpp
ll dfs(int now, bool limit, bool can2) //分别表示现在第几位.现在可否放2。
{
    if (now == 0)
        return 1LL;
    int tt
    if (f[now][limit][can2] != -1)
        return f[now][limit][can2];
    ll rec = 0;
    int flag = limit ? a[now] : 9;
    for (int i = 0; i < flag; i++)
    {
        if (i == 2 && can2)
        {
            res+=dfs(now-1,false,false);
            continue;
        }
        if (i == 4)
            continue;
        rec += dfs(now - 1, false, i != 6);
    }
    if (flag == 4 || (flag == 2 && !can2))
        return f[now][limit][can2] = rec;
    rec += dfs(now - 1, limit, flag != 6);
    return f[now][limit][can2] = rec;
}
ll solve(ll x)
{
    // if (x == -1)
    //     return 0;
    memset(f, -1, sizeof(f));
    int len = 0;
    ll temp = x;
    while (temp)
    {
        a[++len] = temp % 10;
        temp /= 10;
    }
    return dfs(len, true, true);
}

```

- 生长思考这种小bug。if语句用的分流没做好。算法中某一种情况，执行语句块之后，应该及时退出 memset(f, -1, sizeof(f));。但是这里没有实现。并且有漏掉未处理的情况。



#### $code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int f[20][2][2];
int a[20];
ll mod = 1e9 + 7;

ll dfs(int now, bool limit, bool can2) //分别表示现在第几位.现在可否放2。
{
    if (now == 0)
        return 1LL;
    
    if (f[now][limit][can2] != -1)
        return f[now][limit][can2];
    
    ll rec = 0;
    int flag = limit ? a[now] : 9;
    for (int i = 0; i < flag; i++)
    {
        if (i == 2 && !can2)
            continue;
        if (i == 4)
            continue;
        rec += dfs(now - 1, false, i != 6);
    }
    if (flag == 4 || (flag == 2 && !can2))
        return f[now][limit][can2] = rec;
    rec += dfs(now - 1, limit, flag != 6);
    return f[now][limit][can2] = rec;
}
ll solve(ll x)
{
    // if (x == -1)
    //     return 0;
    memset(f, -1, sizeof(f));
    int len = 0;
    ll temp = x;
    while (temp)
    {
        a[++len] = temp % 10;
        temp /= 10;
    }
    return dfs(len, true, true);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    ll a, b;
    while (true)
    {
        cin >> a >> b;
        if (a == 0 && b == 0)
            break;
        cout << /*b << ":" <<*/ solve(b) - solve(a - 1) << '\n';
    } // int c = true;
    // cout << c << '\n';
}
```

-----

#### $\huge3\quad wind数$

```txt
不含前导0，以及且相邻两个数字之差至少为2的数。
求A和B之间的windy数。
```

#### 30min

```txt
定义一个记忆化搜索
dfs(int now, int pre, bool _);
记忆化搜索。
事实上，虽然记忆化搜索具有自明性。
但是实现起来，出现不少问题，
由于代码的不简洁，多个步骤之间的额不统一，导致了比较多的分类讨论。
代码调了一个小时。
面对这种debug用了非常多的时间。应该想办法处理
```

#### 模仿得到的整洁，不容易出错代码。

```CPP
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;

int f[20][20][2];
int a[20];

int dfs(int now, int pre, bool hi) 
{
    if (now == 0)
        return 1;
    if (!hi && f[now][pre][hi] != -1)
        return f[now][pre][hi];
    //统一各种枚举。
    int rec = 0;
    int mmax = hi ? a[now] : 9;
    for (int i = 0; i <= mmax; i++) //如果是自由的
    {
        if (abs(i - pre) < 2)
            continue;
        if (i == 0 && pre == 11)
            rec += dfs(now - 1, 11, hi & i == a[now]);
        else
            rec += dfs(now - 1, i, hi & i == a[now]);
    }
        f[now][pre][hi] = rec;
    return rec;
}

int solve(int x){
    memset(f, -1, sizeof(f));
    int len = 0;
    while (x)
        a[++len] = x % 10, x /= 10;
    return dfs(len, 11, 1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int a, b;
    cin >> a >> b;
    cout << solve(b) - solve(a - 1) << '\n';
}
```

##### $之前的代码：（又臭又长，又垃圾）并且是错误的。$

```cpp
int f[20][20][2][2];
int a[15];
int dfs(int now, int pre, bool limit, bool is) //前导零的影响。前面是否为一连串的前导零。
{
    if (now <= 0)
        return 1;
    if (f[now][pre][limit][is] != -1)
        return f[now][pre][limit][is];
    int rec = 0;
    int mmax = limit ? a[now] : 9;
    if (is)
    {
        rec += dfs(now - 1, 0, false, true);
        for (int i = 1; i <= 9; i++)
            rec += dfs(now - 1, i, false, false);
    }
    else if (pre + 2 <= mmax)
    {
        for (int i = pre + 2; i < mmax; i++)
            rec += dfs(now - 1, i, false, false);
        rec += dfs(now - 1, mmax, limit, false);
    }
    if (mmax > pre - 2)
        mmax = pre - 2;
    for (int i = 0; i < mmax; i++)                           //这里一点出错了。
        rec += dfs(now - 1, i, i == a[now] && limit, false); //必然不是前导
    return f[now][pre][limit][is] = rec;
}

int solve(int x)
{
    memset(f, -1, sizeof(f));
    int len = 0;
    while (x)
    {
        a[++len] = x % 10;
        x /= 10;
    }
    int ans = 0;
    ans += dfs(len - 1, 0, false, true);
    for (int i = 1; i < a[len]; i++)
        ans += dfs(len - 1, i, false, false);
    if (len != 0)
        ans += dfs(len - 1, a[len], true, false);
    return ans;
}
```



--------

#### $\huge 4\quad 数字游戏two$

```txt
acwing
统计A到B之中有多少个数字满足，它们之和modN为0；
```

#### 30mins

```txt
设计递归函数：
dfs(now,mod,limit)分别表示，当前选择的位置，当前的数的取mod结果情况。

然后终于一次就做对了。卧槽。
```

#### $code$

```cpp
#include <bits/stdc++.h>
using namespace std;

int mod;
int a[20];
int f[20][110][2];

int dfs(int th, int s, bool limit)
{
    if (th == 0)
        return s == 0;
    if (f[th][s][limit] != -1)
        return f[th][s][limit];
    int mmax = limit ? a[th] : 9, rec = 0;
    for (int i = 0; i <= mmax; i++)
        rec += dfs(th - 1, (s + i) % mod, i == mmax && limit);
    return f[th][s][limit] = rec;
}

int solve(int x)
{
    memset(f, -1, sizeof(f));
    int len = 0;
    while (x)
        a[++len] = x % 10, x /= 10;
    return dfs(len, 0, true);
}

int main()
{
    int a, b;
    while (cin >> a >> b >> mod)
        cout << solve(b) - solve(a - 1) << '\n';
}
```



#### $\huge 5\quad 度的数量$

```
求给定区间 [X,Y] 中满足下列条件的整数个数：这个数恰好等于 K 个互不相等的 B 的整数次幂之和。

例如，设 X=15,Y=20,K=2,B=2，则有且仅有下列三个数满足题意：

17=2^4+2^0
18=2^4+2^1
20=2^4+2^2
数的范围，在int类型之内：
```

### 10min

```txt
各个位置上的数字最多只有82位。
所以预处理的时候，直接枚举出所有可能。三重循环。
flag[]用于判断。

这里的复杂度就非常大，判断条件也只能用mmap判断。

dfs(len,sum,limit)//前面的总和。
f[len,sum,limit]//一样的道理。
//那么怎么去判定这一个条件呢？
最多搞100*10*2次就可以算出基本上所有的dp。

但是该解法并不是最简洁的解法。
是从枚举十进制数到相对应是否符合条件。
```

#### $参考题解(数位dp的思想并没有非常鲜明的体现。)$

```txt
从B进制的角度出发。
问题转化为，求B进制数，每个位置上只能为0或者为1且1的个数并不超过k;
求满足题意得B进制数的数量。

首先将目标范围的十进制内的数字转化为一个B进制的数字。
然后对于进制数字上的一些思考。
进行一些计算统计。

从高到低位进行检索。
假设当前遍历的位置是 第I位。当前的位置上的数字是x.

从最大的一个位开始看。

1.x>1; 
   当前位选择1后面可以任意取；
   当前取0后面可以任意取。计数
2.x=1;
   当前取0，后面可以任意取；
   当前取1，保证前缀要不大于上界数字。并不可以随意取组合数。
   所以后面的具体方案应该是：继续吧遍历，位置，考虑当前位置上的所有情况。
3.x=0;
   这种情况只能发生在遍历过程之中。当前位置上此时只可以取0；
   
这样的取法：
   1.直接用数学计数来实现。
   2.用记忆化搜索的方法来实现。


dfs(int now ,int sum,bool limit)//分别表示当前是第几位，前面已经有多少个1.当前是否是贴着最大值走。
直到最后一位，如果当前sum已经等于0，及时返回一个1.剪枝。
如果到了最后一位，当前的节点依然不等于0.
```

#### $code$

```cpp
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int f[40][40][2]; //记忆化搜索。后面limit也记录，优化，减少if特判。且空间复杂度肯定是没有问题的
int a[40];        //用来记录当前数上的各个位置上的一些信息。
int K, b;

int dfs(int no /*第几位*/, int now /*题意关注的信息*/, int limit) // limit:用来表示前缀是否贴着上界。
{
    if (!no) //是否返回看具体题意。如果一直保证合法合法搜索得到的前缀，就返回1.否则返回判断。
        return now == 0;
    if (no < now) //说明当前无论怎么取后面都没有合法解了。
        return 0;
    if (now == 0)
        return 1;
    if (f[no][now][limit] != -1)
        return f[no][now][limit];
    int res = 0; //确认合法搜索的取值空间。如果贴着上界，要保证枚举数就在范围之内。
    // if (limit)
    //     res += dfs(no - 1, now, limit);
    // else
    //     res += dfs(no - 1, now, false) + dfs(no - 1, now - 1, a[no] == 1 & limit);
    if (limit)
    {
        if (a[no] >= 1)
            res += dfs(no - 1, now - 1, a[no] == 1);
        res += dfs(no - 1, now, a[no] == 0);
    }
    else
        res += dfs(no - 1, now, false) + dfs(no - 1, now - 1, false);
    return f[no][now][limit] = res;
}

int solve(int x)
{
    memset(f, -1, sizeof(f));
    int len = 0;
    while (x)
        a[++len] = x % b, x /= b;
    return dfs(len, K, true);
}

int main()
{
    int one, two;
    cin >> one >> two >> K >> b;
    cout << solve(two) - solve(one - 1) << '\n';
}

```









