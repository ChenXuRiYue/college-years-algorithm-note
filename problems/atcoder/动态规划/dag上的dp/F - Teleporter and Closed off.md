## **F - Teleporter and Closed off**

https://atcoder.jp/contests/abc291/tasks/abc291_f

通过一些字符串 ， 给定一个dag。并且这个dag上没有回路。

求出删去一个点之后 ， 点1到N的最小距离。

### solve

考虑dag上的动态规划。

​       从两边开始动态规划。由于图没有成回路，发现两个方向的动态规划划是不会共享资源的。这意味着删去一个点之后，可以通过原有的问题的解，来解决现在新的问题的解。
然后枚举K的点（由于边的跨度最多为10.所以枚举m以内的点即可）。

总复杂度是$O(M*M*N)$

#### code

下面是一个非常可能被卡爆的做法： 完全不注意常数上的限制。常数上感觉都到了最大值。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;
string can[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> g(n + 1);
	vector<vector<int>> t(n + 1);
	for (int i = 1; i <= n; i++) {
		string& s = can[i];
		cin >> s;
		for (int j = 0; j < (int)s.size(); j++) {
			if (s[j] == '1') g[i].push_back(j + i + 1), t[j + i + 1].push_back(i);
		}
	}

	vector<vector<int>> e;
	vector<int>d1, d2, d(n + 1, 0x000fffff);
	vector<bool>vis(n + 1, false);
	function<void(int)> dfs = [&](int u)->void {
		if (vis[u]) return;
		vis[u] = true;
		for (auto v : e[u]) {
			dfs(v);
			d[u] = min(d[u], d[v] + 1);
		}
	};
    
	d[n] = 0; e = g;
	dfs(1);
	d1 = d; e = t; d = vector<int>(n + 1, 0x000fffff); d[1] = 0;
	vis = vector<bool>(n + 1, false);
	dfs(n);
	d2 = d;
    
	for (int i = 2; i < n; i++) {
		int ans = 0x000fffff;
		for (int u = max(1, i - m + 1); u < i; u++) {
			for (int v = i + 1; v <= min(i + m, n); v++) {
				if (v - u <= m && can[u][v - u - 1] == '1') {
					ans = min(ans, d2[u] + d1[v] + 1);
				}
			}
		}
		if (ans >= 0x000fffff) cout << -1 << " \n"[i == n - 1];
		else cout << ans << " \n"[i == n - 1];
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

上面的写法中常数偏大。

1. 不必用dfs写。可以换个角度。可以用BFS写。
2. 可以转换成线性dp.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define INF (int)1e+9

int main(void) {
	int n,m,ans;
	cin>>n>>m;
	vector<string> s(n);
	for(int i=0;i<n;i++)cin>>s[i];

	vector<int> dp0(n,INF),dp1(n,INF);
	dp0[0]=0;
	for(int i=1;i<n;i++){
		for(int j=1;j<=min(m,i);j++){
			if(s[i-j][j-1]=='1')dp0[i]=min(dp0[i],dp0[i-j]+1);
		}
	}
	dp1[n-1]=0;
	for(int i=n-2;i>=0;i--){
		for(int j=1;j<=min(m,n-1-i);j++){
			if(s[i][j-1]=='1')dp1[i]=min(dp1[i],dp1[i+j]+1);
		}
	}
  
	for(int k=1;k<n-1;k++){
                ans=INF;
		for(int i=max(k-m+1,0);i<k;i++){
			for(int j=k+1;j<min(n,k+m);j++){
				if(s[i][j-i-1]=='1')ans=min(ans,dp0[i]+dp1[j]+1);
			}
		}
                if(ans==INF)cout<<-1;
		else cout<<ans;
		if(k<(n-2))cout<<" ";
		else cout<<endl;
	}	
	return 0;
}
```

