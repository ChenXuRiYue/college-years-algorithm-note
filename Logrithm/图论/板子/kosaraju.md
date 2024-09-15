#### kosaraju

```cpp

const int N = 1E6 + 10;

vector<vector<int>> e , erev;

vector<vector<int>> ssc;
vector<int> c;
bool vis[N];

vector<int>out;

int n , m;

void dfs(int u)
{
	vis[u] = true;
	for (auto v : e[u]) {
		if (vis[v])continue;
		dfs(v);
	}
	out.push_back(u);
}

void dfs2(int u) {
	vis[u] = true;
	for (auto v : erev[u]) {
		if (vis[v])continue;
		dfs2(v);
	}
	c.push_back(u);
}

void kosaraju() {
	for (int i = 1; i <= n; i ++)
	{
		if (vis[i])continue;
		dfs(i);
	}
	memset(vis, false, sizeof(vis));
	reverse(out.begin(), out.end());
	for (auto u : out) {
		if (vis[u])continue;
		c.clear();
		dfs2(u);
//		sort(c.begin(), c.end());
		ssc.push_back(c);
	}
}

/*
*  1.注意建一个反图
*  2.图的初始化没有完成。
*  3.main上记得写下函数
*/
```

