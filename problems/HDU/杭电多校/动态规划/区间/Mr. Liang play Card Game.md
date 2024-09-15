# Mr. Liang play Card Game

[Mr. Liang play Card Game - HDU 7277 - Virtual Judge (vjudge.net)](https://vjudge.net/problem/HDU-7277)

给定一个牌组数组 ， 每张牌上标记了牌的种类以及等级。对这些牌组进行一下两种操作：

1. 选择一张牌打出，得到一个分数$p ^{leval}V_i$ ，level表示该牌的等级。$V_i$ 表示该牌对应种类的一个固有的元素。
1. 对两个相邻的同类型，同级别的牌进行合并。合并后你两张牌消息，得到一个等级+1的牌。

求问最大收益。

### solve

很显然的区间dp问题：

1. 数据范围是 1.... 100；非常可行。
2. 转移过程中，规模不断变小。
3. 相邻合并。

**状态设计：**
$f_{L , R , ty , level}$ : 表示将区间[L , R]合并成ty类型，level等级的最大收益。
$g_{L , R}$ 表示将区间[L , R]整个处理完毕的最大收益。

**状态转移方程**

对于$f数组$ ： 合并区间有多种可能：定义 left , right表示 分割出来的左右区间。

1. left -> level - 1 , right -> level - 1;
2. left -> 空 ， right -> level
3. left - > level , right -> 空

对于$g数组：$

1. 整个数组合并成一个牌，再消掉。
2. 整个数组分左右两端独立按照最优花费消掉。

**生长思考：**

1. 这种dp设计，是否考虑了所有的方案：


1. 初始化得到的dp数组显然是正确的。
2. 对于一个区间（某个规模下的问题：）上述的几种转移方向中，都涉及到将了划分成两个区间处理。 考察对于该问题的任意解： 不断地合并或者拿走。考察一个方案的最后一步操作 ： 两个牌合并，或者取出一张牌。而得到两张牌（或者一张牌X （可以看成一张空牌，和X））利用的资源，必定是两相斥的区间。如果确定了其利用到了什么资源（即这个结果是基于哪一区间中操作得到的。）确定终点（即最后变为空，或者某种牌。）找最优，显然是最优的。（相同资源，相同操作终点 ， 所有方案中取最优。）

上面可以是对一般的区间动态规划问题的解法的合法性分析：几个关键如下：

1. 发现每一个方案中，最后都是两个合成对象之间的合并。
2. 两个合成对象之间，所涉及的区间资源，必然是两相斥的区间。
3. 综上枚举两区间的分界点，以及合成对象的类型，就可以不重不漏的记录并且计算所有规模问题下的最优方案。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 101;
const int P = 21;


int a[N] , v[N];
ll f[N][N][P][8];
ll g[N][N];
int sum[N][P];
ll p2[P];

void work(int testNo)
{
	int n , m , R , p;
	cin >> n >> m >> R >> p;
	R = min(R , 7);
	p2[1] = 1;
	for (int i = 2; i <= R; i++) {
		p2[i] = p2[i - 1] * p;
	}
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	for (int i = 1; i <= m; i++)
		cin >> v[i];
	// 处理输入的过程：


	// 进行相关信息的初始化：
	for (int i = 1; i <= n; i++) {
		// 一般数组整体的初始化：
		for (int j = i; j <= n; j++)
			for (int k = 0; k <= m; k++)
				for (int pp = 0; pp <= R; pp++) {
					f[i][j][k][pp] = -1;
					g[i][j] = 0;
				}

		// 当前数组的信息：
		f[i][i][a[i]][1] = 0;
		g[i][i] = v[a[i]];

	}

	for (int d = 0; d < n; d++) {
		for (int l = 1; l + d <= n; l++) {
			int r = l + d;
			for (int mid = l; mid < r; mid++) {
				// 合并成的ty的最大值：、
				// 可是具体的行为怎么办？
				// 可能会追求不同的等级：
				// 如一维度，
				for (int ty = 1; ty <= m; ty++) {
					for (int pp = 1; pp <= R ; pp++) {
						if (f[mid + 1][r][ty][pp] != -1) {
							f[l][r][ty][pp] = max(f[l][r][ty][pp] , g[l][mid] + f[mid + 1][r][ty][pp]);
						}
						if (f[l][mid][ty][pp] != -1) {
							f[l][r][ty][pp] = max(f[l][r][ty][pp] , g[mid + 1][r] + f[l][mid][ty][pp]);
						}
						if (f[l][mid][ty][pp - 1] != -1 && f[mid + 1][r][ty][pp - 1] != -1) {
							f[l][r][ty][pp] = max(f[l][r][ty][pp] , f[l][mid][ty][pp - 1] + f[mid + 1][r][ty][pp - 1]);
						}
					}
				}
				g[l][r] = max(g[l][r] , g[l][mid] + g[mid + 1][r]);
			}
			for (int ty = 1; ty <= m; ty++) {
				for (int pp = 1; pp <= R ; pp++) {
					if (f[l][r][ty][pp] != -1)
						g[l][r] = max(g[l][r] , 1LL * p2[pp] * v[ty] + f[l][r][ty][pp]);
				}
			}
		}
	}
	cout << g[1][n] << "\n";
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```

