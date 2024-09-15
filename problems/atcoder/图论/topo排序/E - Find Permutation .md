## **E - Find Permutation** 

(https://atcoder.jp/contests/abc291/tasks/abc291_e

对于一个未知的 ， 长度为 n的排列。给定m对关系 
$$
x_i , y_i\\
P_{x_i} < P_{y_i}
$$


如果可以根据已知信息推出排列  , 则 输出排列。否则输出No。

### solve

通过这些关系建立一个图。然后就图上进行推导。发现如果要推出一个排列。满足几个性质。

1. 图的深度为m。
2. 不能有回路。

如果最终可以构造出一组解：那么最终这组解和topo相关。topo序对应位置在排列的位置，就是1.....n。

### code

实现topo序有两种经典方法。

1. 删根法。  
2. dfs法。

##### 删根法

关注删根过程中可以得到的信息。如果每一次删根，不存在1个以上的入度为0的节点即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;
vector<int> g[N];
int deg[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		deg[y]++;
	}
	queue<int> que;
	for (int i = 1; i <= n; i++) {
		if (deg[i] == 0) que.push(i);
	}
	int tot = 0;
	vector<int>ans(n + 1);
	while (que.empty() == false) {
		if (que.size() != 1) {
			cout << "No\n";
			return 0;
		}
		int u = que.front(); que.pop();
		ans[u] = ++tot;
		for (auto v : g[u]) {
			deg[v]--;
			if (deg[v] == 0)
				que.push(v);
		}
	}
	if (tot != n) { cout << "No\n"; return 0; }
	cout << "Yes\n";
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " \n"[i == n];
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

#### dfs深搜法

对于深搜法 ， 就是求出最大深度。同时可以根据每个位置上的值。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin >> n >> m;
	vector<vector<int>>G(n);
	for(int i=0;i<m;i++){
		int x,y;
		cin >> x >> y;
		x--,y--;
		G[x].push_back(y);
	}
	
	vector<int>length(n,-1);
	auto dfs=[&](int v,auto dfs){
		if(length[v]!=-1)return length[v];
		length[v]=0;
		for(auto vv:G[v])length[v]=max(length[v],dfs(vv,dfs)+1);
		return length[v];
	};
	
	int d=0;
	for(int i=0;i<n;i++)d=max(d,dfs(i,dfs));
	if(d==n-1){
		cout << "Yes" << endl;
		for(auto x:length)cout << n-x << ' ';
	}else{
		cout << "No" << endl;
	}
}
```



