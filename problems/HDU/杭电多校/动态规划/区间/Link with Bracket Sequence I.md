# Link with Bracket Sequence I

[K-Link with Bracket Sequence I_"蔚来杯"2022牛客暑期多校训练营2 (nowcoder.com)](https://ac.nowcoder.com/acm/contest/33187/K)

**Please pay attention to the unusual memory limit.**  

Link is playing a game, called _NIO's Game_.  

In this game, a level consists of several worlds. Each world consists of $m$ nodes and some directed roads. The player starts on node $1$ of the first world. In each world, the player can either stay at current node or go through exactly one road that exists in that world. After that, the player will be teleported to the next world without changing the ID of the node where he stays. If there is no next world, the game ends. The player wins if he ends on node $m$.  
Link is editing a new level, he has already made $n$ worlds (numbered from $1$ to $n$) and wants to choose a **continuous subsegment** of them to form a new level. **The only limit is that there should be at least one way to win.**  
Link doesn't want to **use** too many worlds. What is the **minimum** number of worlds Link needs to use in the new level?

链接有一个长度为 $n$的括号序列 $a$，它是长度为 $m$的有效括号序列 $b$的**子序列**。
林克不记得$b$，所以他想知道可能的序列数$b$。
如果一个括号序列满足以下任何一个条件，那么它就是有效的：  
- 其长度为 $0$。
- 它可以表示为 $(A)$，其中 $A$是一个有效的括号序列。
- 可以表示为$AB$，其中$A$和$B$都是有效的括号序列。
序列 $a$是序列 $b$的子序列，如果 $a$可以通过删除几个（可能是零或全部）元素从 $b$得到。

### solve

关于括号的合法性问题的处理，有一个经典的技巧与角度：（关注 ， 记录多出的左括号的人数量。）在任何一个前缀中，一个合法的括号序列都要满足前缀的左括号序列比右括号多。

**状态设计：**
$f_{i , j , k}$ 表示当前s串前i项，和t串前j项匹配，左括号比右括号多k个的方案个数。
其中记录的即是s_{1....i} 到 t_{1....j}即最大匹配。

**状态转移方程：**

求解$f_{i , j , k}$ 考虑当前位置放什么符号：

1. 考虑放置')'

   1. $f_{i - 1 , j - 1 , k + 1}$ : 前提t[j] = ')'
   2. $f_{i - 1 , j , k + 1}$   : 前提t[j + 1] $\ne$ ')'
2. 考虑放置'('
   1. $f_{i - 1 , j - 1 , k - 1}$ : 前提t[j] = '(' , k > 0
   2. $f_{i - 1, j , k - 1}$ ： 前提t[j + 1] $\ne$ '(' , k > 0


**生长思考：**
写这问题时，状态设计时是带猜测意味的。并没有详细的证明正确性；

1. 首先对于某个规模的问题，任一方案都落在某一个记录状态中。
2. 对于计数问题，同规模，不同特征问题的解之间显然没有重复。

### code

```cpp
const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 210;
const int mod = 1E9 + 7;
/*
1
2 4
)(
*/
void work(int testNo){
	int n, m;
	cin >> n >> m;
	vector<vector<vector<int>>> f(m + 1, vector<vector<int>>(n + 1, vector<int>(m + 2, 0)));
	string s;
	cin >> s;
	s = ' ' + s + ' ';
	f[0][0][0] = 1;
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			// cout << "i : " << i << " j : " << j << "\n";
			for (int k = 0; k <= m; k++) {
				if (s[j] == ')')
					(f[i][j][k] += f[i - 1][j - 1][k + 1]) %= mod;
				if (s[j + 1] != ')')
					(f[i][j][k] += f[i - 1][j][k + 1]) %= mod;
				if (s[j] == '(' && k > 0)
					(f[i][j][k] += f[i - 1][j - 1][k - 1]) %= mod;
				if (s[j + 1] != '(' && k > 0)
					(f[i][j][k] += f[i - 1][j][k - 1]) %= mod;
				// cout << f[i][j][k] << ' ';
			}
			// cout << "\n";
		}
	}
	cout << f[m][n][0] << "\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```

