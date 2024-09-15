# E. Arena

https://codeforces.com/contest/1606/problem/E
竞技场上有$n$个英雄在战斗。最初，第$i$个英雄有$a_i$点生命值。
竞技场中的战斗分几个回合进行。每轮开始时，每个活着的英雄都会对所有其他英雄造成 $1$点伤害。所有英雄的攻击同时发生。回合结束时，生命值低于 $1$的英雄被视为死亡。
如果在某一回合后，恰好有$1$个英雄仍然活着，则宣布他获胜。否则，没有获胜者。
你的任务是计算有多少种方法可以选择每个英雄的初始健康点数 $a_i$，其中 $1 \le a_i \le x$，从而使这场战斗没有赢家。方法的数量可以非常多，所以打印时要模数为 $998244353$。如果至少有一个英雄的生命值不同，则认为这两种方法是不同的。例如，$[1, 2, 1]$和$[2, 1, 1]$就是不同的。

## solve
**状态定义：**
$f_{i,j}$ 表示当前还剩下i个英雄存活， 最高血量的英雄为j。 给这i个英雄分配血量，满足最终没有赢家的方案个数。
**状态转移方程：**
给定i , j之后。通过当前轮之后的情况，分类转移： 
1. k , j - (i - 1)
2. 做一个大类之后，再作一个细节的分步乘法计数：
   1. 组合选择被淘汰元素的选择方案；
   2. 求出被淘汰的人的合法血量的所有可能方案情况。
   **初始化：**
1. 如果对于i等于1的状态记录，统一为0；
2. 关注最后一步的状态：
   $f_{i ,j }$ 
   i - 1 >= j; 直接算出方案数
### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;;
const ll INF = 1E18 + 7;
const int N = 510;
const int mod = 998244353;

void add(ll& a , ll b) {
	a += b;
	if (a >= mod) a -= mod;
}
void dec(ll& a , ll b) {
	a -= b;
	if (a < 0) a += mod;
}


const int N_c = 5E2 + 10;
int c[N_c][N_c];
void C_init() {
	for (int i = 1; i < N_c; ++i) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
}
//注意范围
//小心me
ll f[N][N];

ll qpow(ll x, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * x % mod;
		n /= 2;
		x = x * x % mod;
	}
	return res;
}
ll p[N][N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	C_init();
	int n , x;
	cin >> n >> x;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= x; j++) {
			p[i][j] = qpow(i , j);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= x; j++) {
			if (i - 1 >= j) {
				// f[i][j] = dec(qpow(j , i) , qpow(j - 1 , i));
				// 容斥：
				add(f[i][j] , qpow(j , i));
				dec(f[i][j] , qpow(j - 1 , i));
			} else {
				// 枚举这一次之后还有多少人存活：
				for (int k = 1; k <= i; k++) {
					add(f[i][j] , f[k][j - (i - 1)] * c[i][k] % mod * p[i - 1][i - k] % mod);
				}
			}
		}
	}
	ll ans = 0 ;
	for (int i = 1; i <= x; i++) {
		add(ans , f[n][i]);
	}
	cout << ans << "\n";
}
```

