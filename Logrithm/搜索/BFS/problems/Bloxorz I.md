**Bloxorz I**

[A-Bloxorz I_0x25 搜索-广度优先搜索 (nowcoder.com)](https://ac.nowcoder.com/acm/contest/1017/A)

[172. 立体推箱子 - AcWing题库](https://www.acwing.com/problem/content/description/174/)

#### solve

考虑bfs。
集中精力解决下面的问题：

1. 图的终点是什么？怎么表示？
2. 图上状态表示的方法
3. 优化迁移方案，减少代码量。

**关于图的起点**：3种情况

1. 一个格子。立起来
2. 两个格子
   1. 打横
   2. 打竖

因此要进行一些预处理判断起点的情况。

**关于状态表示：**

点上的状态标记几个维度：x , y ,lie。分别表示其最接近原点端的坐标。（x最小，y最小。）

**优化转移方案**

用一些数组来标记转移变化：
`next_x[3][4]`
`next_y[3][4]`
`next_lie[3][4]`

0 站， 1 横躺， 2竖躺。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N =  510;
char s[N][N];
struct node {int x , y , lie;};
node st , ed;
int n , m;
int d[N][N][4];
//优化转移减少if冗余。
//0 ， 1 ， 2 ， 3 左右上下
//0 , 1 , 2 站 ， 横躺 ， 竖躺
int next_x[3][4] = {{0 , 0 , - 2 , 1} , {0 , 0 , -1 , 1} , {0 , 0 , - 1 , 2 }};
int next_y[3][4] = {{ -2 , 1 , 0 , 0} , { -1 , 2 , 0 , 0} , { -1, 1, 0 , 0}};
int next_l[3][4] = {{1 , 1 , 2 , 2} , {0 , 0 , 1 , 1} , {2 , 2 , 0 , 0}};
int dx[4] = {0 , 0 , 1 , -1} , dy[4] = { -1 , 1, 0 , 0};
void get_st_ed() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			if (s[i][j] == 'X') {
				for (int k = 0 ; k < 4; k ++) {
					int x = i + dx[k];
					int y = j + dy[k];
					if (s[x][y] == 'X') {
						s[i][j] = s[x][y] = '.';
						st.x = min(x , i);
						st.y = min(y , j);
						st.lie = k < 2 ? 1 : 2;
					}
				}
				if (s[i][j] == 'X') {
					st.x = i; st.y = j;
					st.lie = 0;
				}
			} else if (s[i][j] == 'O') {
				ed.x = i; ed.y = j; ed.lie = 0;
				s[i][j] = '.';
			}
	}
}
bool check(int x, int y) {
	return x <= n && x >= 1 && y <= m && y >= 1;
}
bool valid(node next) {
	if (!check(next.x , next.y)) return false;
	if (s[next.x][next.y] == '#') return false;
	if (next.lie == 0 && s[next.x][next.y] != '.')return false;
	if (next.lie == 1 && s[next.x][next.y + 1] == '#')return false;
	if (next.lie == 2 && s[next.x + 1][next.y] == '#')return false;
	return true;
}
int bfs() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 0 ; k < 3; k ++)
				d[i][j][k] = -1;
	queue<node> que;
	que.push(st);
	d[st.x][st.y][st.lie] = 0;
	while (que.empty() == false) {
		node cur = que.front(); que.pop();
		for (int i = 0; i < 4; i++) {
			int x = cur.x + next_x[cur.lie][i];
			int y = cur.y + next_y[cur.lie][i];
			int l = next_l[cur.lie][i];
			if (valid({x , y , l}) == false)continue;
			if (d[x][y][l] != -1)continue;
			d[x][y][l] = d[cur.x][cur.y][cur.lie] + 1;
			que.push({x , y , l});
			if (x == ed.x && y == ed.y && l == ed.lie) {
				return d[x][y][l];
			}
		}
	}
	return -1;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	while (true) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			cin >> (s[i] + 1);
		}
		if (n == 0)return 0;
		get_st_ed();
		int ans = bfs();
		if (ans == -1) {cout << "Impossible\n"; }
		else cout << ans << '\n';
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













