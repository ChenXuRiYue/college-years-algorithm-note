**F. Copy of a Copy of a Copy**
https://codeforces.com/problemset/problem/1772/F

给定一张 $n$ 行 $m$ 列的黑白图片（下标从 $1$ 开始），每一个单元格都被涂上了黑色或白色（$1$ 或者 $0$）。

我们对这张图片进行了若干次（可能为零次）操作，每一次操作都是下列两种之一：

- 选择一个单元格，这个单元格不能在图片的边缘（即，单元格所在行不能是 $1$ 或 $n$ 行，所在列不能是 $1$ 或 $m$ 列），并且这个单元格被四个不同颜色的单元格包围（中间 $0$ 四周 $1$，反之亦然），将这个单元格涂成相反的颜色；
- 复制一份当前图片。

两种操作不一定会交替进行。

给出你初始图片与 $k$ 份复制图片，一共 $k+1$ 份图片，这 $k+1$ 份图片是被随机打乱的。

你的任务是恢复操作的顺序。若有多种可能答案，只输出其中一个即可。

所有数据保证答案一定存在。


#### solve

1. 运算的起点是什么？
2. 运算过程中 ， 资源的关键性变化。

关注二问题： 点颜色转变之后 ， 将不可复原。即连续的过程中， 可改变点的个数必定是连续变化的。

1. 由此解决问题 1 ： 起点就是可运算点的数目最大点的图。
2. 然后通过单调性 ， 就可以逐渐确定所有的过程：

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using i64 = long long;
using ull = unsigned long long;
using ld = long double;
using uint = unsigned int;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;


#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define pb push_back
#define fi first
#define se second

const int inf = 1 << 29;
const ll INF = 1LL << 60;
const int N = 1E6 + 10;

char s[110][33][33];
int sum[110];
int dx[] = { 0 , 0 , 1,  -1 }, dy[] = { -1 , 1 , 0 , 0 };
int n, m, k;
vector<pair<int, int>> update(int i, int j) {
	vector<pii> res;
	for (int x = 1; x <= n; x++)
		for (int y = 1; y <= m; y++) {
			if (s[i][x][y] != s[j][x][y]) {
				res.emplace_back(x, y);
			}
		}
	return res;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> k;
	priority_queue<pair<int, int>> que;
	for (int i = 0; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> (s[i][j] + 1);
		}
		int rec = 0;
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= m; k++) {
				if (j == 1 || j == n || k == 1 || k == m)continue;
				bool flag = true;
				for (int l = 0; l < 4; l++) {
					if (s[i][j + dx[l]][k + dy[l]] == s[i][j][k]) {
						flag = false;
					}
				}
				rec += flag == true;
			}
		sum[i] = rec;
		que.push(make_pair(rec, i));
	}
	auto cur = que.top();
	que.pop();
	cout << cur.se + 1 << "\n";
	vector<array<int, 3>> ans;
	while (que.size()) {
		auto t = que.top();
		if (t.fi == cur.fi) {
			ans.push_back({ 2 , t.se , 0 });
			que.pop();
		}
		else {
			auto res = update(cur.se, t.se);
			while (res.size()) {
				auto tt = res.back();
				res.pop_back();
				ans.push_back({ 1 , tt.fi , tt.se});
			}
		}
		cur = t;
	}
	cout << sz(ans) << "\n";
	for (auto t : ans) {
		int x = t[0], y = t[1], z = t[2];
		if (x == 1)
			cout << x << " " << y << " " << z << "\n";
		else cout << x << " " << y + 1 << "\n";
	}
}
/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```



