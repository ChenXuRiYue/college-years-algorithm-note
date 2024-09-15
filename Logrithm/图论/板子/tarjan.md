#### tarjan

```cpp

const int N = 1E6 + 10;

vector<int> e[N];
int dfn[N] , low[N] , bel[N], ins[N] , id;

vector<vector<int>> ssc;
stack<int>stk;

void dfs(int u) {

	dfn[u] = low[u] = ++id;
	ins[u] = true;
	stk.push(u);

	for (auto v : e[u]) {
		if (!dfn[v]) dfs(v);
		if (ins[v]) low[u] = min(low[v] , low[u]);
	}

	//说明已经没有收割的空间了：
	if (low[u] == dfn[u]) {
		vector<int> s;
		while (true) {
			int v = stk.top();
			stk.pop();
			s.push_back(v);
			ins[v] = false;
			bel[v] = ssc.size();
			if (v == u)break;
		}
		//sort(s.begin(), s.end());
		ssc.push_back(s);
	}
}

void tarjan()
{
	for (int  i = 1; i <= n; i++) {
		if (dfn[i] == 0)
			dfs(i);
	}
}
```

#### lambda封装版本

```cpp
void tarjan()
{
	int n , m;
	cin >> n >> m;
    
    //建图
    //情景不同数组可能开更大。注意
	vector<vector<int>> e(n + 1);

	for (int i = 0; i < m; i ++) {
        /*处理边输入*/
	}

	vector<int> dfn(n + 1) , low(n + 1) , bel(n + 1) , ins(n + 1);
	int id = 0;
	stack<int> stk;
	int cnt = 0;
    
    vector<vector<int>> ssc(n + 1);

	function<void(int)> dfs = [&](int u) {
		dfn[u] = low[u] = ++id;
		ins[u] = true;
		stk.push(u);

		for (auto v : e[u]) {
			if (!dfn[v]) dfs(v);
			if (ins[v]) low[u] = min(low[v] , low[u]);
		}

		if (low[u] == dfn[u]) {
			++cnt;
            vector<int> c;
			while (true) {
				int v = stk.top();
				stk.pop();
				ins[v] = false;
				bel[v] = cnt;
				if (v == u) break;
			}
            ssc.push_back(c);
		}
	};

	for (int i = 0; i < 2 * n; i++) {
		if (dfn[i] == 0) dfs(i);
	}
}
```

