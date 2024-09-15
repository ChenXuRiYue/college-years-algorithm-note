# E. Rearrange Brackets

https://codeforces.com/problemset/problem/1821/E

正则括号序列是指可以通过在序列的原始字符之间插入字符 "1 "和 "+"来转换成正确算术表达式的括号序列。例如

- 括号序列"()() "和"(()) "是正则表达式（得到的表达式为"(1)+(1) "和"((1+1)+1)"）；
- 括号序列")("、"("和") "则不是。

给您一个正则括号序列。您可以一次删除一对**相邻**的括号，使左边的括号是开括号，右边的括号是闭括号。然后在不改变顺序的情况下将得到的部分连接起来。此举的代价是这对括号中右括号右边的括号数。

常规括号序列的代价是使序列为空所需的最小移动总代价。

实际上，您并没有删除任何括号。相反，我们给你一个正则括号序列和一个整数$k$。您最多可以执行以下操作 $k$次：

- 从序列中提取某个括号，并在任意位置（任意两个括号之间、括号的开头或结尾；可能的话，在原来的位置）将其插入。

所有操作完成后，括号序列必须是规则的。由此得到的正则括号序列的最小代价是多少？

### solve

1. 第一个子问题：对于一个括号序列中，其花费怎么统计：
   1. 从个体的贡献角度，发现一对括号的贡献次数就是其本身包含的括号对数。
2. 由上述观察得到一个非常显然的贪心思路，就是对减少一些括号（这些括号，包含了许多括号。）这总是可以实现的。
3. 研究这种括号之间的包含关系，其角度包括：
   1. 祖先关系。
   2. 一个括号的包含括号对数：

上述天然的用一树来表达：于是将问题转变成了树上的问题，贪心的将节点数数量最大祖宗消除即可。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"

#define all(x) (x).begin(),(x).end()

const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 1E6 + 10;

void work(int testNo)
{
	int k; cin >> k;
	string s;
	cin >> s;
	int n = (int)s.size();
	vector<vector<int>> g(n);
	vector<int> par(n , -1) , sz(n , 0);
	vector<int> stk;
	// 万年一用 ，
	ll ans = 0;
	function<void (int)> dfs = [&](int u)->void{
		sz[u] = 1;
		for (auto v : g[u]) {
			dfs(v);
			sz[u] += sz[v];
		}
	};

	for (int i = 0; i < n; i++) {
		if (s[i] == '(') stk.push_back(i);
		else {
			int t = stk.back(); stk.pop_back();
			ans += (int)stk.size(); // 说明当前其深度是多少。一共有多少个父亲。
			if (not stk.empty()) {
				par[t] = stk.back();
				g[stk.back()].push_back(t);
			}
		}
	}

	for (int i = 0; i < n; i++)
		if (s[i] == '(' && par[i] == -1) dfs(i);

	sort(sz.begin() , sz.end());

	for (int i = 0; i < k && sz.size() && sz.back() != 0; i++) {
		int temp = sz.back(); sz.pop_back();
		ans -= temp - 1;
	}

	cout << ans << '\n';
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```

