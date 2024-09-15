**数位dp进阶**

### 数数3

[数数3 - 题目 - Daimayuan Online Judge](http://oj.daimayuan.top/course/8/problem/248)

求区间中有多少个数字a满足存在连续三个数位 $a_i , a_{i + 1} , a_{i + 1}$使得$a_{i} < a_{i + 1}<a_{i + 2}$

 [basic.md](..\basic.md) 参照题解：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;

ll dp[20][2][20][5];


//用单词前三个的习惯。
ll dfs(int rem , int exit , int pre , int inc) {
	if (rem == 0) return exit;
	if (dp[rem][exit][pre][inc] != -1)
		return dp[rem][exit][pre][inc];

	ll &res = dp[rem][exit][pre][inc];
	res = 0;

	for (int i = 0; i <= 9; i++) {
		int inc_ = (i > pre) ? min(inc + 1 , 3) : 1;
		res += dfs(rem - 1 , exit || inc_ == 3 , i , inc_);
	}
	return res;
}

ll solve(ll x) {
	x++;//细节1
	vector<int> d;
	while (x) {d.push_back(x % 10); x /= 10;}
	//处理前导0的情况。
	ll ans = 0;
	int m = d.size();
	reverse(d.begin(), d.end());
	for (int i = 1; i < m; i++) {
		for (int j = 1; j <= 9; j++) {
			ans += dfs(i - 1, 0 , j , 1);
		}
	}
	//然后处理贴着上界走的情况。
	int exit = 0 , pre = 0, inc = 0;
	for (int i = 0; i < m; i++) {
		for (int j = (i == 0); j < d[i] ; j ++) {
			//同时要记录前缀的一些信息。
			int inc_ = (j > pre) ? min(inc + 1 , 3) : 1;
			ans += dfs(m - i - 1 , exit || inc_ == 3, j , inc_);
		}
		inc = (d[i] > pre) ? min(inc + 1, 3) : 1;
		pre = d[i];
		exit |= (inc == 3);
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	memset(dp , -1 , sizeof dp);
	ll l , r;
	cin >> l >> r;
	cout << solve(r) - solve(l - 1) << '\n';
}

```

### CF Round #739 (Div 3) F, Nearest Beautiful Number

[Problem - F2 - Codeforces](https://codeforces.com/contest/1560/problem/F2)

找到最小的 ， 满足大于等于n的， 美丽数位k的数字。

#### solve.

暴力搜索加剪枝：并不是数位dp的解法。

1. 可以估算复杂度非常小 ， 为n的字符值之和。

   1. dfs算法从可能的最小数字解开始进行枚举

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;

void work(int testNo)
{
	int  n , k; cin >> n >> k;
	vector<int> d;
	//尽量开大一点，拓展当前值域，增多可表达内容。
	int vis[10] {};
	while (n) {d.push_back(n % 10); n /= 10;}
	reverse(d.begin() , d.end());
	// x： 表示当前遍历的位置。 large，前缀是否大于规定的前缀。nums前面的k的前缀中数字的种数。
	function<bool (int , int , int , int)> dfs = [&](int x , int large , int nums , int cunt) {
		//能走到一步必然有解了。
		if (x == (int)d.size()) {
			cout << nums << '\n';
			return true;
		} else {
			//然后从哪里开始枚举呢？分情况。
			//如果已经large。那么就从0开始。否则从 d[x]开始
			for (int i = (large ? 0 : d[x]); i <= 9; i++) {
				//然后开始各种枚举枚举构造大法。
				vis[i] += 1;
				int ncunt = cunt;
				if (vis[i] == 1)ncunt += 1;
				if (ncunt <= k && dfs(x + 1 , large | (i > d[x]) , nums * 10 + i , ncunt)) {
					return true;
				}
				vis[i] -= 1;
			}
			return false;
		}
	};
	dfs(0 , 0 , 0 , 0);
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

### **乘法**
[乘法 - 题目 - Daimayuan Online Judge](http://oj.daimayuan.top/course/8/problem/185)

#### 简介：

将乘法转换成加减法组合的最小花费。

#### solve

1. 从高位到低位考虑：

   ​           定义$S_i$  = $a_{1}....a_i000000(i-1个0)$二进制串的值。T为前期操作地结果。

   1. 假设现在枚举到了第i位。要有解，必须满足：
      1. $S-T =0$或者$T-S=(1<<(i))$
      2. 否则，在低位进行任意加减操作。都不会把差异消除。

2. 状态设计

   从高位到低位对应 $i=1......i=n$

   $f_i$表示从高位开始考虑到了第i个位置。

   $g_i$表示从高位开始考虑到了第i个位置。$T_{i} - S_i=(2^{n-i})$

3. 初始化：

   1. $f_0=0,g_i=1$

4. 状态转移方程

   1. 如果$s_i='0'$
      1. 对于$f_i$有如下转移：
         1. $f_{i-1}$啥都不变。
      2. 对于$g_i$有如下方案
         1. $f_{i-1}$ , 对应方案加当前位权。
         2. $g_{i-1}$，对应方案减去当前位权。
   2. 如果$s_i='1'$
      1. 对于$f_i$
         1. $g_{i-1}$对应的方案减去当前位权。
         2. $f_{i-1}$对应的方案加上当前为位权。
      2. 对于$g_i$
         1. $g_{i-1}$对应的方案减去当前位权。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1E6 + 10;
int f[N] , g[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s; cin >> s;
	int n = s.size();
	s = ' ' + s;
	fill(f , f + 1 + n , N);
	fill(g , g + 1 + n , N);
	f[0] = 0; g[0] = 1;
	for (int i = 1 ; i <= n; i++) {
		if (s[i] == '1' ) {
			f[i] = min(f[i - 1] + 1 , g[i - 1] + 1);
			g[i] = g[i - 1];

		} else {
			f[i] = f[i - 1];
			g[i] = min(f[i - 1] + 1 , g[i - 1] + 1);
		}
		//cout << "now is  " << i << "  " << f[i] << "  " << g[i] << '\n';
	}
	cout << f[n] * 2 - 1 << '\n';
}
```
-------------
###  P3188 [HNOI2007]梦幻岛宝珠
特殊的01背包问题。
特殊点：
1. 物品的重量大小比较特殊： $w = a2^b$
2. 背包总承受重量非常大。
#### 10mins
关注数字的特殊性：
1. 数字都是一个二进制数的倍数。
2. a , b都非常小。
可以优化值域，枚举一些特殊的二进制数字。
#### solve

考虑将背包按照b分组。$s=\sum a$

##### 关注几个现象

1. 重量的形式非常特殊。考虑b类的物品时，比b更低位的位，无论怎么变化都和全0下的空间的大小是等效的。因为这点大小的空间下，无法影响某空间问题下考察的方案数。
2. 当枚举到b=15时候，是否意味着高十五位的空间变化都需要分别独立记录？参与转移
   1. 发现b = 15中的物品通过组合看，空间至多是$s\times 2^b$。 因此我们对上述空间的压缩为：留下的多少




面对这些现象可以采取什么样的策略？

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 1ll << 60;

vector<pair<int, int>> item[40];
ll f[2010], g[2010];
int n, W;

void solve() {
	int s = 0;
	for (int i = 0; i <= 30; i++) item[i].clear();
	for (int i = 0; i < n; i++) {
		int w, v;
		scanf("%d%d", &w, &v);
		int lev = __builtin_ctz(w);
		w >>= lev;
		item[lev].push_back({w, v});
		s += w;
	}
	for (int i = 0; i <= s; i++) f[i] = -inf;
	f[0] = 0; // >= 2^31的背包
	for (int i = 30; i >= 0; i--) {
		// i + 1 -> i
		for (int i = 0; i <= s; i++) g[i] = f[i], f[i] = -inf;
		int d = (W >> i) & 1;
		for (int i = 0; i <= s; i++) {
			// 上面用剩下了多少。
			// 主要是用来记录s中最大地情况。超过s的归于一类。
			f[min(2 * i + d, s)] = max(f[min(2 * i + d, s)], g[i]);
		}

		// 后缀和，表示，当前剩下有i的最大价值。
		for (int i = s - 1; i >= 0; i--)
			f[i] = max(f[i], f[i + 1]);

		for (auto p : item[i]) {
			// 做一个普通的01背包即可。
			for (int i = p.first; i <= s; i++)
				f[i - p.first] = max(f[i - p.first], f[i] + p.second);
		}
	}
	// 剩下0的最大价值。没有要求恰好装满；
	printf("%lld\n", f[0]);
}

int main() {
	while (true) {
		scanf("%d%d", &n, &W);
		if (n == -1 && W == -1)
			break;
		solve();
	}
}
```







### CCPC Changchun 2020 D, Meaningless Sequence

[CCPC Changchun 2020 D, Meaningless Sequence - 题目 - Daimayuan Online Judge](http://oj.daimayuan.top/course/8/problem/315)

注意仔细地读标号。防止读错。

第一次读这道题地时候，没有发现 & 是位于下标中的。

#### solve

~~反正只知道 ， 是我一些不懂的规律。~~

打表可以发现 ， $a_n = c^{popcunt(n)}$

特别的有 ， $a_0 = 1$

自然而然地问题转换成了一道简单地数位dp。

##### solve1

dfs过程中枚举前缀。然后直接利用组合数计算贡献即可。

##### solve2

枚举任意前缀时，发现后缀的贡献总是：

$c^{pre(1)}\times(c + 1)^{sux\_len}$

##### code of solve1

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3E3 + 10;
const ll mod = 1E9 + 7;

string s;
ll c;
ll d[N][N][2] , C[N][N] , p[N];
int n;

ll dfs(int rem ,  int sum , bool larger) {

	if (rem == 0) return p[sum];
	if (larger == false) {
		ll res  = 0;
		for (int i = 0; i <= rem ; i ++)
			res += (p[sum] * C[rem][i] % mod) * p[i] % mod;
		return res;
	}
	ll res = 0;
	for (int i = 0; i <= s[n - rem] - '0'; i++) {
		res = (res + dfs(rem - 1, sum + (i == 1) , i == (s[n - rem] - '0'))) % mod;
	}
	return res;
}

void intit() {
	cin >> s >> c;
	n  = s.size();
	p[0] = 1;
	for (int i = 1; i < N; i++) p[i] = p[i - 1] * c % mod;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0) C[i][j] = 1;
			else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	intit();
	cout << dfs(n , 0 , true) << '\n';

}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

##### code of solve2

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;
const int mod = 1E9 + 7;
ll p[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s; int c;
	cin >> s >>  c;
	int n = s.size();

	p[0] = 1;
	for (int i = 1 ; i <= n; i++) {
		p[i] = p[i - 1] * (c + 1) % mod;
	}

	ll pre = 1 , ans = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '1') {
			ans  = (ans + pre * p[n - i - 1]) % mod;
			pre = pre * c % mod;
		}
	}
	cout << (pre + ans ) % mod << '\n';
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

### **CCPC Jinan 2020 L, Bit Sequence**

[CCPC Jinan 2020 L, Bit Sequence - 题目 - Daimayuan Online Judge](http://oj.daimayuan.top/course/8/problem/316)

[L-Bit Sequence_第 45 届国际大学生程序设计竞赛（ICPC）亚洲区域赛（济南） (nowcoder.com)](https://ac.nowcoder.com/acm/contest/10662/L)

#### 简介

定义$f_{i}$为i的二进制串中的1的个数。给定一个01序列$a_{0...m-1}$。求取$[0....x-1]$中，满足对于任意$0<=i<m,f(x+i)\%2=a_i$

#### solve

观察一些现象：

1. 由于m的范围比较小。因此两个数字相加，结果相比于x， m只能影响低7位。并且低七位进一个1， 其影响是明确且容易把握的。（一段连续的位反转。）
如下记录可重复使用的信息：（研究递归树：）
```
ll f[61][2][2][2];
dfs(int cur /*第几位*/, int sum ,  int odd /*前面位置的奇偶性*/, int limit /*是否贴着上界*/, int chose/*后7位的选择情况。*/) {
```

于是每一个状态最多只使用254 * 5的花费求出。（由于最后的状态是暴力处理的。 每一次处理到最后5位，花费254 * 5 ，影响一个状态。）

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 110;

ll l;
int a[N] , m;
ll f[61][2][2][2];

vector<int> Bit;
//检查后5位置的奇偶性
int check(int x /*当前后7位的情况。*/, int pre /*前高位连续0*/, int sum/*高位0的总数奇偶性*/) {
	int flag = 1;
	for (int i = 0; i < m; i++) {
		int j = x + i;
		if (j < (1 << 7)) {
			flag &= (sum ^ (__builtin_parity(j))) == a[i];
		} else {
			flag &= ((sum ^ pre) ^ (__builtin_parity(j))) == a[i];
		}
	}
	// if (flag == 1)
	// 	cout << x << " "  << pre  << " " << sum  << "\n";
	return flag;
}

/*
3
3 10
0 1 0
1 1000
0
9 1000000
1 0 1 1 0 1 0 0 1
*/

/*
1
3 10
0 1 0
*/

ll dfs(int cur /*第几位*/, int sum ,  int odd /*前面位置的奇偶性*/, int limit /*是否贴着上界*/, int chose/*后7位的选择情况。*/) {
	if (cur > 6 && f[cur][sum][odd][limit] != -1) {
		return f[cur][sum][odd][limit];
	}
	if (cur == -1) return check(chose , odd , sum);
	int mx = limit ? Bit[cur] : 1;
	ll& res = f[cur][sum][odd][limit];
	res = 0;
	for (int i = 0; i <= mx; i++) {
		int sum_ = sum, odd_ = odd, chose_ = chose * 2;
		if (i == 1) {
			if (cur < 7) {
				chose_++;
			} else {
				odd_ ^= 1;
				sum_ ^= 1;
			}
		} else {
			if (cur  > 6) {
				odd_ = 0;
			}
		}
		res += dfs(cur - 1 , sum_ , odd_ , limit && (i == mx) , chose_);
	}
	return res;
}

void solve() {
	memset(f , 0xff , sizeof f);
	Bit.clear();
	cin >> m >> l;
	for (int i = 0; i < m; i++)
		cin >> a[i];
	for (int i = 0; i <= 60; i++) {
		Bit.push_back(l % 2);
		l /= 2;
	}
	cout << dfs(60 , 0 , 0 , 1 , 0) << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while (t--)solve();
}
```





