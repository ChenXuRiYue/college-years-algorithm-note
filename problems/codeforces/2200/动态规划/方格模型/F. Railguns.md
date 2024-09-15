# F. Railguns
https://codeforces.com/contest/1840/problem/F

特马正在玩一个非常有趣的电脑游戏。

在下一个任务中，特马的角色发现自己来到了一个陌生的星球。与地球不同，这颗行星是平的，可以用一个$n \times m$长方形来表示。
特马的角色位于坐标为$(0, 0)$的点上。为了成功完成任务，他需要活着到达坐标为$(n, m)$的点。
让电脑游戏中的角色位于坐标$(i, j)$处。每秒钟，**从第一个**开始，特马可以：

- 或者使用垂直超跳技术，之后他的角色将在一秒结束时到达坐标 $(i + 1, j)$处；
- 或使用水平超跳技术，之后他的角色将在第二秒结束时到达坐标 $(i, j + 1)$处；
- 或者特马可以选择不进行超跳，在这种情况下，他的角色在这一秒内不会移动；
居住在这颗星球上的外星人非常危险且充满敌意。因此，他们会用轨道炮射击 $r$次。
每次射击都会垂直或水平完全穿透一个坐标。如果人物在射击**（第二发结束时）**时处于其影响范围内，则会死亡。
由于特马查看了游戏的源代码，所以他知道每次射击的完整信息--时间、穿透坐标和射击方向。
角色到达预期点的**短**时间是多少？如果他注定死亡，无法到达坐标为$(n, m)$的点，则输出$-1$。

### solve

观察到每一次等待都对应着一次射击，因此如果最终可以到达终点，那么一定可以在$N + M + Q$次到达终点。

直接dp即可：

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 1E4 + 10;
void work(int testNo){
	int n , m;
	cin >> n >> m;
	n++ , m++;
	int q;
	cin >> q;
	vector<vector<vector<bool>>> f(n + 1 , vector<vector<bool>>(m  + 1 , vector<bool>(n + m + 10 + q , false)));
	set<pair<int , int>> row , column;
	for (int i = 0; i < q; i++) {
		int a , b  , c;
		cin >> a >> b >> c;
		c++;
		if (b == 1) {
			row.insert({a , c});
		} else column.insert({a , c});
	}
	f[1][1][0] = true;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int t = 1; t <= n + m + q + 1; t++) {
				if (column.count({t, j}) || row.count({t, i})) {
					f[i][j][t] = false;
					continue;
				}
				f[i][j][t] = f[i - 1][j][t - 1] || f[i][j - 1][t - 1] || f[i][j][t - 1];
			}
		}
	}
	for (int t = 0; t <= n + m + q + 1; t++) {
		if (f[n][m][t]) {
			cout << t << "\n";
			return;
		}
	}
	cout << -1 << "\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```

