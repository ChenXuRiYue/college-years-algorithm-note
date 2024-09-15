https://codeforces.com/contest/1766/problem/D

```txt
给定两个数字 
x 和 y
令找出最大的d使得  （x , y）.....(x+d，y+d)互质。
```

###  solve

- 模拟一遍增加的过程，发现这个过程中，两个量之间的差是不会发生变化的。
- 两个数字可以表示为：$d=y-x,y=x+d$
- 发现若d和 x互质，那么x，y互质。因此只需要枚举所有的最接近x的与d不互质的数即可。

  - 有点质数在连续数域上划分，进而筛掉所有被当前划分数字整除的数字。这是一种数论问题非常常见的技巧。

  

  - 由于质因数得到的结果更优。整体质因数来计算可以代表最小的解空间。

### $code$

- 首先实现： 欧拉筛法。将所有的素数筛选出来。
  - 学到jls的一个很优秀的模板。学到一些处理质数的操作。
  - 和之前的模板不一样，他将flag变成了记录下标的最小质因数。
  - 同时通过这种质因数的除法，来枚举出所有的质因数。



#### $jls's\quad code$

```cpp
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1E7;

int mp[N + 1];
std::vector<int> primes;

void solve() {
    int x, y;
    std::cin >> x >> y;
    
    int d = y - x;
    if (d == 1) {
        std::cout << -1 << "\n";
        return;
    }
    
    int ans = 1E9;
    while (d > 1) {
        int p = mp[d];
        d /= p;
        ans = std::min(ans, (p - x % p) % p);
    }
    
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    for (int i = 2; i <= N; i++) {
        if (!mp[i]) {
            mp[i] = i;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > N) break;
            mp[i * p] = p;
            if (i % p == 0) break;
        }
    }
    
    int t;
    std::cin >> t;
    
    while (t--) solve();
    
    return 0;
}
```

#### 自己的代码几乎就是模仿的，但还是给出来吧

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e7;
int mp[maxn + 1];
vector<int> primes;

void solve()
{
    int x, y;
    cin >> x >> y;
    int d = y - x;
    //开始枚举和d有关的质因数。
    if (d == 1)
    {
        cout << -1 << '\n';
        return;
    }
    int ans = 1e9;
    while (d > 1)
    {
        int p = mp[d];
        ans = min((p - x % p) % p, ans); //如果等于t就是0所以再取一个mod
        d /= p;
    }
    cout << ans << '\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    for (int i = 2; i <= maxn; i++)
    {
        if (!mp[i])
        {
            mp[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes)
        {
            if (p * i > maxn)
                break;
            mp[i * p] = p;
            if (i % p == 0)
                break;
        }
    }
    int t;
    cin >> t;
    while (t--)
        solve();
}
```

#### 生长思考；

- 抓住变化过程中的不变量（特殊的地方）。然后发掘一些与问题紧密相关的性质
  - 最大的边界和差之间的关系。
- 欧拉筛法的另外模板，以及这种模板下，更加灵活的一些处理素数问题的基本操作。
  - 枚举一个数的所有质因数

```cpp
 //枚举d的所有质因数：   
 while (d > 1) {
        int p = mp[d];
        d /= p;
        ans = std::min(ans, (p - x % p) % p);
    }
```





