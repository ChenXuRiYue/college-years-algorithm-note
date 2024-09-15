**E. Two Chess Pieces**
https://codeforces.com/contest/1774/problem/E

![image-20230711090507015](C:/Users/86153/AppData/Roaming/Typora/typora-user-images/image-20230711090507015.png)

### solve
从另外一个角度出发：

1. 当我们知道a应该走到那个点时 ， 由两者最大距离不超过d。可以得到b哪些点也是必走的。
2. 于是根据两者的必走点，可以推出所有必走点。

推出必走点：分几种情况

1. 对于u , 在以u为根的子树中，两者都有必走点。那么u两者都必走。

2. 如果只有一个有，找出要到达的最大深度，即可计算出u到最大深度的距离。关注d ，从而判断是

   另外一个角色是否必须经过该点。

由必走点推出距离：

1. 发现往返，其答案就是（sum - 1)*2

**实现：**
1. 简单跑一遍dfs ， 做一个非常基础的树形dp即可。
### code
```cpp
const int inf = 1 << 29;
const ll INF = 1LL << 60;
const int N = 1E6 + 10;

vector<int> g[N];
ll cnt0 , cnt1;
int dep[N] , n ,  d;
bool vis1[N] , vis2[N];

void getdep(int u , int fa , int d) {
	dep[u] = d;
	for (auto v : g[u]) {
		if (v != fa) {
			getdep(v , u , d + 1);
		}
	}
}

// pair<int , int> 这里是用来访问
pair<int , int> dfs(int u , int fa ) {
	pair<int , int> rec;
	if (vis1[u])
		rec.fi = dep[u];
	if (vis2[u])
		rec.se = dep[u];

	for (auto v : g[u]) {
		if (v == fa) continue;
		auto t = dfs(v , u);
		rec.fi = max(t.fi , rec.fi);
		rec.se = max(t.se , rec.se);
	}
	if (rec.fi) {
		cnt0++;
		if (rec.se) cnt1++;
		else if (rec.fi - dep[u] >= d)
			cnt1++;
	} else {
		if (rec.se) {
			cnt1++;
			cnt0 += (rec.se - dep[u] >= d);
		}
	}
	return rec;
}


signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> d;
	for (int i = 1; i < n; i++) {
		int u , v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int x; cin >> x;
	for (int i = 0; i < x; i++) {
		int y; cin >> y;
		vis1[y] = true;
	}
	cin >> x;
	for (int i = 0; i < x; i++) {
		int y; cin >> y;
		vis2[y] = true;
	}

	getdep(1 , 0 , 1);
	dfs(1 , 0);
	cout << 2 * (cnt0 + cnt1 - 2) << "\n";
}
```

