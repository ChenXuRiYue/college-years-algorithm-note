# G. Edge Groups

完了，签到题也这么难，如果真是在打比赛，是没有把握在一个小时之内，把这个问题解决的。
[Problem - G - Codeforces](https://codeforces.com/gym/103446/problem/G)

Given an undirected connected graph of $n$ vertices and $n-1$ edges, where $n$ is guaranteed to be odd. You want to divide all the $n-1$ edges to $\frac{n-1}{2}$ groups under following constraints:

-   There are exactly 2 edges in each group
-   The 2 edges in the same group share a common vertex

Determine the number of valid dividing schemes modulo $998244353$. Two schemes are considered different if there are 2 edges that are in the same group in one scheme but not in the same group in the other scheme.

### solve

观察到当前的结构，发现当前的解方案和其节点




```cpp
const int N = 1E6 + 10;
const int mod = 998244353;
vector<int> g[N];
int A[N] , sz[N];
ll f[N];
/*
5
1 2
2 3
2 4
2 5
*/
void dfs(int u , int fa) {
	sz[u] = 1;
	f[u] = 1;
	int sum = 0;
	for (auto v : g[u]) {
		if (v == fa) continue;
		dfs(v , u);
		sz[u] += sz[v];
		if (sz[v] % 2) sum++;
	}
	for (auto v : g[u]) {
		if (v == fa) continue;
		f[u] = f[u] * f[v] % mod;
	}
	if (sum == 0) return;
	else if (sum % 2 == 0) {
		f[u] = f[u] * A[sum - 1] % mod;
	} else {
		f[u] = f[u] * A[sum]  % mod;
	}
	// cout << u << " " << f[u] << " "  << sum << "\n";
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	A[0] = A[1] = 1;
	for (int i = 2; i < N; i++) {
		A[i] = 1LL * A[i - 2] * i % mod;
	}
	// for (int i = 0; i < 10; i++) {
	// 	cout << A[i] << " ";
	// }
	// cout << '\n';
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u , v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1 , 0);
	cout << f[1] << '\n';
}
```



# ICPC EC Final 2020 A, Namomo Sequence
[Problem - A - Codeforces](https://codeforces.com/gym/103069/problem/A)

"gshfd1jkhaRaadfglkjerVcvuy0gf" said Prof. Pang.

To understand Prof. Pang's word, we would like to calculate the number of namomo subsequences of it. The word by Prof. Pang is a string $s$ with $n$ characters where each character is either an English letter (lower or upper case) or a digit. The $i$\-th character of $s$ is denoted by $s[i]$ ($1\le i\le n$). A subsequence $t$ of $s$ is defined by a list of indices $t_1, \ldots, t_6$ such that $1\le t_1 < t_2 < \ldots < t_6\le n$. Let $compare(c_1, c_2)$ be a function on two characters such that $compare(c_1, c_2)=1$ when $c_1=c_2$ and $compare(c_1, c_2)=0$ otherwise. $t$ is a namomo subsequence of $s$ if and only if for any $1\le i<j\le 6$, $compare(s[t_i], s[t_j]) = compare(namomo[i], namomo[j])$, where $namomo[x]$ represents the $x$\-th character of the string "namomo" ($1\le x\le 6$).

Output the number of namomo subsequences of a given string $s$ modulo $998244353$.

### solve
其实就是找出形如ABCDCD的子序列个数：简单想法：

1. **记录各个位置上的情况，然后转移**

$O(N\times |S| ^ 4)$ 显然不行：

2. ****

   观察这个结构： 划分成两个层次的统计： 然后可以适用乘法定理优化复杂度：

   1. AB
   2. CDCD
   
   **相关数组设计:**
   
   $f[i][4][s_1][s_2]$ 从后往前考虑到第i位置 , 第二维取各值时其内容如下:
   
   1. 1表示$s_1s_2s_1s_2$中 $s_2$的个数:
   2. 2表示$s_1s_2$ 的个数.
   3. 3表示$s_2s_1s_2$的个数.
   4. 4就没必要记录了:
   
   
   
   枚举到cdcd之后,怎么找出符合条件的AB?
   
   1. 记录结构$cnt_i$ 表示i字符的个数。通过这些内容计算出符合条件的AB
   
   $$
   \frac {((\sum cnt_s )- cnt_i - cnt_j) ^2 - \sum cnt_s^2 + cnt_i^2 + cnt_j^2}{2}
   $$
   
   然后通过滚动数组： 惊奇的发现每次转移只需要进行小花费的修改，整体复杂度非常小：于是复杂度优化成了：
   
   $O(N\times |S|)$

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;;
const ll INF = 1E18 + 7;
const int N = 1E6 + 10;
const int SIZE = 62;
const int mod = 998244353;

string s;
// 分别表示
ll f[5][SIZE][SIZE];
// 建立索引：
ll cnt[SIZE];
ll ans = 0;
ll sum = 0 , sum2 = 0;

int id(char t) {
	if (t >= 'A' && t <= 'Z') return t - 'A';
	if (t >= 'a' && t <= 'z') return t - 'a' + 26;
	return 52 + t - '0';
}
void add(ll& a , int b) {
	a += b;
	if (a >= mod) a -= mod;
}
void add(int t) {
	sum++;
	sum2 += 2 * cnt[t] + 1;
	cnt[t]++;
}
void dec(int t) {
	sum--;
	sum2 = sum2 - 2 * cnt[t] + 1;
	cnt[t]--;
}

ll query(int j , int k) {
	return ((sum - cnt[j] - cnt[k]) * (sum - cnt[j] - cnt[k])
	        - (sum2 - cnt[j] * cnt[j] - cnt[k] * cnt[k])) / 2 % mod;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> s;
	for (int i = 0; i < sz(s); i++) {
		int j = id(s[i]);
		add(j);
	}
	for (int i = sz(s) - 1; i >= 0; i--) {
		int j = id(s[i]);
		// 然后进行更新
		dec(j);
		for (int k = 0; k < SIZE; k++) {
			// 枚举更新多个结构的变化：
			if (j == k) continue;
			add(f[1][k][j] , 1);
			add(f[3][k][j] , f[2][k][j]);
			add(f[2][j][k], f[1][j][k]);
			add(ans , f[3][j][k] * query(j , k) % mod);
		}
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

-----

# I. Modulo Permutations

Given a natural number $n$, count the number of permutations $(p_1, p_2, \ldots, p_n)$ of the numbers from $1$ to $n$, such that for each $i$ ($1 \le i \le n$), the following property holds: $p_i \text{ mod } p_{i+1} \le 2$, where $p_{n+1} = p_1$.

As this number can be very big, output it modulo $10^9 + 7$.

### solve

凭空的推数据是比较麻烦的，在这种有限的限制背景之下，一个不错的策略是打一个表找到结构的规律：

```txt
1 8 6 5 4 2 10 9 7 3
1 8 6 5 4 3 2 10 9 7
1 8 7 6 5 2 10 9 4 3
1 8 7 6 5 3 2 10 9 4
1 8 7 6 5 4 2 10 9 3
1 8 7 6 5 4 3 2 10 9
1 9 2 10 8 7 6 5 4 3
1 9 3 2 10 8 7 6 5 4
1 9 4 2 10 8 7 6 5 3
1 9 4 3 2 10 8 7 6 5
1 9 7 2 10 8 6 5 4 3
1 9 7 3 2 10 8 6 5 4
1 9 7 5 2 10 8 6 4 3
1 9 7 5 3 2 10 8 6 4
1 9 7 5 4 2 10 8 6 3
1 9 7 5 4 3 2 10 8 6
1 9 7 6 5 2 10 8 4 3
1 9 7 6 5 3 2 10 8 4
1 9 7 6 5 4 2 10 8 3
1 9 7 6 5 4 3 2 10 8
1 9 8 7 6 2 10 5 4 3
1 9 8 7 6 3 2 10 5 4
1 9 8 7 6 4 2 10 5 3
1 9 8 7 6 4 3 2 10 5
1 9 8 7 6 5 2 10 4 3
1 9 8 7 6 5 3 2 10 4
1 9 8 7 6 5 4 2 10 3
1 9 8 7 6 5 4 3 2 10
1 10 2 9 8 7 6 5 4 3
1 10 3 2 9 8 7 6 5 4
1 10 4 2 9 8 7 6 5 3
1 10 4 3 2 9 8 7 6 5
1 10 5 2 9 8 7 6 4 3
1 10 5 3 2 9 8 7 6 4
1 10 5 4 2 9 8 7 6 3
1 10 5 4 3 2 9 8 7 6
1 10 8 2 9 7 6 5 4 3
1 10 8 3 2 9 7 6 5 4
1 10 8 4 2 9 7 6 5 3
1 10 8 4 3 2 9 7 6 5
1 10 8 6 2 9 7 5 4 3
1 10 8 6 3 2 9 7 5 4
1 10 8 6 4 2 9 7 5 3
1 10 8 6 4 3 2 9 7 5
1 10 8 6 5 4 2 9 7 3
1 10 8 6 5 4 3 2 9 7
1 10 8 7 6 5 2 9 4 3
1 10 8 7 6 5 3 2 9 4
1 10 8 7 6 5 4 2 9 3
1 10 8 7 6 5 4 3 2 9
1 10 9 2 8 7 6 5 4 3
1 10 9 3 2 8 7 6 5 4
1 10 9 4 2 8 7 6 5 3
1 10 9 4 3 2 8 7 6 5
1 10 9 7 2 8 6 5 4 3
1 10 9 7 3 2 8 6 5 4
1 10 9 7 5 2 8 6 4 3
1 10 9 7 5 3 2 8 6 4
1 10 9 7 5 4 2 8 6 3
1 10 9 7 5 4 3 2 8 6
1 10 9 7 6 5 2 8 4 3
1 10 9 7 6 5 3 2 8 4
1 10 9 7 6 5 4 2 8 3
1 10 9 7 6 5 4 3 2 8
1 10 9 8 2 7 6 5 4 3
1 10 9 8 3 2 7 6 5 4
1 10 9 8 4 2 7 6 5 3
1 10 9 8 4 3 2 7 6 5
1 10 9 8 6 2 7 5 4 3
1 10 9 8 6 3 2 7 5 4
1 10 9 8 6 4 2 7 5 3
1 10 9 8 6 4 3 2 7 5
1 10 9 8 6 5 4 2 7 3
1 10 9 8 6 5 4 3 2 7
1 10 9 8 7 2 6 5 4 3
1 10 9 8 7 3 2 6 5 4
1 10 9 8 7 5 2 6 4 3
1 10 9 8 7 5 3 2 6 4
1 10 9 8 7 5 4 2 6 3
1 10 9 8 7 5 4 3 2 6
1 10 9 8 7 6 2 5 4 3
1 10 9 8 7 6 3 2 5 4
1 10 9 8 7 6 4 2 5 3
1 10 9 8 7 6 4 3 2 5
1 10 9 8 7 6 5 2 4 3
1 10 9 8 7 6 5 3 2 4
1 10 9 8 7 6 5 4 2 3
1 10 9 8 7 6 5 4 3 2
```

**规律：**

1. 1尾部接递减段， 2尾部接一个递减段：
    启发： 问题可以变成一个不断在两端放数的过程：并且是放不重的排列数，似乎见过这种模型：
    类比：[D2. Hot Start Up (hard version).md](..\..\..\..\problems\codeforces\2100\动态规划\优化\D2. Hot Start Up (hard version).md) 
    **最简单的想法：**
    **状态定义：**
    $f_{k, i , j}$ 表示考虑放置第k个的时候， 1序列的头部为i ， j的序列的头部为j的时的方案数。
    适用滚动数组可以优化成;$f_{i , j}$ 。放完第i位时 ，方案记录于$f_{i , j}$ 或者$f_{j ,i}$
    **状态转移方程：**
$$
f_{i ,j } -> f_{i + 1 , j}\\
f_{i.j} -> f_{i , i+1} ， 此时注意判断合法性：\\
$$
**复杂度分析：**
$O(N^2)$
**考虑进一步的优化：**

1. 从更加全局的角度来考虑贡献：

标答：

Let’s consider 2 arcs between the numbers 1 and 2.
First observation: a mod 2, a mod 1, 1 mod a, 2 mod a ≤ 2 for any a, so the conditions involving 1 and2 are automatically satisfied and we can forget about them.
Second observation: in each arc the numbers are strictly decreasing (if 2 < x < y on some arc, we get x mod y = x > 2, contradiction).
Now, we need to do a sieve-like dp. Let dp[x] denote the number of ways to split the numbers from n to x into 2 arcs so that x goes to the first arc and x + 1 goes to the second. We can calculate this dp for each i from n to 3 in the following manner: suppose that the numbers x + 1, . . . , k go to the second arc while k + 1 goes to the first one. Then we must have (k + 1) mod x ≤ 2, and the number of such k is ≤ 3$\frac {n}{x}$ As the sum of n/x over all x is O(n log(n)), we get O(n log(n)) solution overall.

-----

dls'code（死活理解不了啊：qaq）

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1000000007;

const int N = 1010000;
int n, dp[N];

void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int main() {
    scanf("%d", &n);
    if (n == 1) {
        puts("1");
        return 0;
    }
    dp[1] = 1;
    // 好恐怖的转移方程：
    // 被省略了一堆细节，理解不了：
    for (int j = 1; j <= n - 1; j++) {
        if (j <= 3) {
            for (int i = j + 1; i <= n; i++) add(dp[i], dp[j]);
        } else {
            for (int k = -1; k <= 1; k++) {
                for (int i = j + k; i < n; i += j) if (i > j)
                        add(dp[i], dp[j]);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i < n; i++) add(ans, dp[i]);
    printf("%lld\n", 1ll * ans * n % mod);
}
```
