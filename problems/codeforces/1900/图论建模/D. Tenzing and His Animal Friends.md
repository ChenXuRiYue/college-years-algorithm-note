**D. Tenzing and His Animal Friends**
https://codeforces.com/contest/1842/problem/D

![image-20230711152217951](C:/Users/86153/AppData/Roaming/Typora/typora-user-images/image-20230711152217951.png)

## solve

1. 无穷大解的判定：
     凭借限制构造一个图，如果发现1 和 n不在同一个连通块。那么将1所在的连通块一直做游戏，且时间无穷不违反题意。否则，由于n被孤立在外，1所在的连通块规模会不断减少。这意味着最终会有一个终点。

2. 最优解策略：
     1. 人数选择上： 每一次游戏，将能与1参加游戏的所有人一起全被列入：

        ==证明==
     
     2. 时间选择上： 关注两个集合，可以与1参与游戏的集合，不可以与1参与游戏的集合。在这两个集合之间选择最短边。作为游戏时长。
     
        1. 如果大于关注最短边就违背规则。
     
        2. 如果小于关注最短边，在1的贪心规律下，迟早将该最短边的时长给用完。
     


## code

```cpp
struct DSU {
	std::vector<int> f, siz;

	DSU() {}
	DSU(int n) {
		init(n);
	}

	void init(int n) {
		f.resize(n);
		std::iota(f.begin(), f.end(), 0);
		siz.assign(n, 1);
	}

	int find(int x) {
		while (x != f[x]) {
			x = f[x] = f[f[x]];
		}
		return x;
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}

	bool merge(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) {
			return false;
		}
		siz[x] += siz[y];
		f[y] = x;
		return true;
	}

	int size(int x) {
		return siz[find(x)];
	}
};

vector<array<int , 3>> edge;
bool can[N];
ll have[N]; // 总的单人游玩时间。

struct node {
	string s;
	ll t;
};
vector<node> ans;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n ,  m;
	cin >> n >> m;
	DSU dsu(n);
	for (int i = 0; i < m; i++) {
		int u , v , w;
		cin >> u >> v >> w;
		u-- , v--;
		dsu.merge(u , v);
		edge.push_back({u , v , w});
	}

	if (not dsu.same(0 , n - 1)) {
		cout << "inf\n"; return 0;
	}
	// 然后维护两个集合，寻找最短边。
	can[n - 1] = true;
	// 寻找两个集合之间的最短边。
	// 直到不再存在该点。
	// 分别表示总游戏时间
	ll time = 0;
	int sum = 0;

	while (!can[0]) {
		int mi = INF;
		for (auto [u , v , w] : edge) {
			if (can[u] != can[v]) {
				// 已经一起共同游玩的时间。
				mi = min(mi , w);
			}
		}
		string res;
		for (int i = 0; i < n; i++) {
			if (not can[i]) {
				res += "1";
			} else {
				res += "0";
			}
		}
		ans.push_back({res , mi});
		sum++;
		time += mi;
		// 然后对两个集合进行更新。
		vector<array<int , 3>> g;
		vector<int> rrec;
		for (auto &[u , v , w] : edge) {
			if (can[u] != can[v]) {
				w -= mi;
				if (w == 0) {
					// 注意这个后效性。
					// can[u] = can[v] = true;
					rrec.push_back(u);
					rrec.push_back(v);
				}
			}
		}
		for (auto v : rrec) {
			can[v] = true;
		}
	}

	cout << time << " " << sum << "\n";
	for (auto [s , t] : ans) {
		cout << s << " " << t << "\n";
	}
}
```

