# M. Moving Both Hands

https://codeforces.com/contest/1725/problem/M

两只手，分别在点1和p。 两只手在有向图上独立的移动，问这两只手相遇的最短时间。



### solve

有两个解法：

1. 分层图
2. 一些建图技巧。



#### 分层图：

参考博客：[分层图总结_best_brain的博客-CSDN博客](https://blog.csdn.net/x052xiao/article/details/125957769)
相似思想：[P4568 [JLOI2011\] 飞行路线 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P4568)

建立分层图：一旦选择到第二层后，只能走反边：（并且是不能回到第一层。）

1. 于是在上述图中的路径，全部满足： 先走正向边，或者一转全部走反边。

然后在上述图走一遍最短路即可。

#### 建图技巧的解法：

先跑完所有能直接到达的点。然后在这些点的基础上，建立一个反图 , 具体如下:

1. 跑出最短路之后： 得到$d$最短路数组：
   1. 对于能够到达的点，就使用上述替代，给1和这些点建立一条边。
   2. 正向便前部忽略。建立反向边。
2. 然后在上述图中跑最短路即可。

### code

```cpp
const int inf = 1 << 29;
const ll INF = 1LL << 60;
const int N = (int)2E5 + 10;

vector<pair<int , int>> e[N];
ll d[N];
bool done[N];

struct node {
	int u;
	ll d;
	bool operator <(const node& t)const {
		return d > t.d;
	}
};
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n , m ;
	cin >> n >> m;
	fill(d , d + 2 * n + 1, INF);
	for (int i = 1; i <= n; i++) {
		e[i].push_back({i + n , 0});
	}
	for (int i = 0; i < m; i++) {
		int u , v , w;
		cin >> u >> v >> w;
		e[u].push_back({v , w});
		e[v + n].push_back({u + n , w});
	}

	priority_queue<node> que;
	fill(done , done + 2 * n + 1 , false);
	d[1] = 0;
	que.push({1 , 0});
	while (not que.empty()) {
		int u = que.top().u; que.pop();
		if (done[u]) continue;
		done[u] = true;
		for (auto [v , w] : e[u]) {
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				que.push({v , d[v]});
			}
		}
	}
	for (int i  = 2; i <= n; i++) {
		if (d[i + n] == INF) cout << -1;
		else cout << d[i + n];
		cout << " \n"[i == n];
	}
}
```

