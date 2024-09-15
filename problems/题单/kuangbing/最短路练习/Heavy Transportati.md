**Heavy Transportati**
https://vjudge.csgrandeur.cn/problem/POJ-1797#author=0

#### solve

求出图中最小权的最大值。  N = 1000.
类似迪杰斯特拉的贪心思路 ， 逐渐求出到每一个点的所有路径中最小边的最大值。

**算法描述**

1. 初始化：
2. 确定新的d【i】
3. 对更新的点作拓展。
4. 上述2 ， 3进行n伦直到确认所有点。

**证明：**

#### code

```cpp
#include<iostream>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E3 + 10;

int g[N][N];
int d[N];
bool vis[N];

void work(int testNo)
{
	int n , m; cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		vis[i] = false;
		d[i] = 0;
		for (int j = 1; j <= n; j++) {
			g[i][j] = 0;
		}
	}
	for (int i = 0; i < m; i++) {
		int u , v , w; cin >> u >> v >> w;
		g[u][v] = g[v][u] = w;
	}
	d[1] = 1 << 29;
	for (int i = 1; i <= n; i++) {
		int m = 0 , mx = 0;
		for (int j = 1; j <= n; j++)if (d[j] > mx && vis[j] == false)mx = d[m = j];
		vis[m] = true;
		for (int j = 1; j <= n; j++) {
			d[j] = max(d[j] , min(d[m] , g[m][j]));
		}
	}
	d[1] = 0;
	cout << "Scenario #" << testNo << ":\n";
	cout << d[n] << "\n\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
/* stuff you should look for
3* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

