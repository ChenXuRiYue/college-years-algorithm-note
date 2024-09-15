**Sudoku**

https://ac.nowcoder.com/acm/contest/1014/B

#### solve

1. 状态压缩的方式，更容易维护行列中的情况。
2. 优化
   1. 对于一个位置上通过行于列判定选择可选解。使用lowbit运算快速定位到可选数字。
   2. 从可选解少的位置开始填。
3. 注意维护搜索树。

#### 总结

。。。 tm的都是啥啊。卡常被卡麻啦。已经使用了关键的几个优化。

#### code，还是被卡。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
// #define x first
// #define y second
const int N = 10;
int h[10], w[10], g[10] , sum[N][N],  ans[N][N];
int m = 0;
pii arr[N * N];
//从现在在考虑第几个位置。
bool dfs(int now) {
	if (now >= m) {
		//cout << "\n yes \n";
		return true;
	}
	//快速找到符合要求的数字。
	//枚举并且递归：
	/*
	*1. 一位接一位的枚举
	*2. 利用lowbit的技巧枚举。
	*/
	int x = arr[now].first, y = arr[now].second;
	int id = x / 3 * 3 + y / 3;
	int can = h[x] & w[y] & g[id];
	while (can != 0) {
		//cout << to << '\n';
		int temp = can & -can;
		int to = __builtin_ffs(temp);
		h[x] ^= temp;
		w[y] ^= temp;
		g[id] ^= temp;
		can = can -  temp;
		ans[x][y] = to;
		if (dfs(now + 1))
			return true;
		ans[x][y] = 0;
		h[x] ^= temp;
		w[y] ^= temp;
		g[id] ^= temp;
	}
	// for (int i = 0; i < 9; i++) {
	// 	if (!(can >> i & 1)) {
	// 		ans[x][y] = i + 1;
	// 		h[x] ^= (1 << i);
	// 		w[y] ^= (1 << i);
	// 		if (dfs(now + 1))return true;
	// 		ans[x][y] = 0;
	// 		h[x] ^= (1 << i);
	// 		w[y] ^= (1 << i);
	// 	}
	// }
	return false;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	while (true) {
		string s;
		cin >> s;
		if (s == "end")break;
		//一堆 ，初始化。
		for (int i = 0 ; i < 9; ++i) {
			h[i] = w[i] = g[i] = 0;
			for (int j = 0; j < 9; ++j)ans[i][j] = 0;
		}
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				char t = s[i * 9 + j];
				if (t != '.') {
					//保存答案数组。
					ans[i][j] = t - '0';
					h[i] |= 1 << (ans[i][j] - 1);
					w[j] |= 1 << (ans[i][j] - 1);
					int id = i / 3 * 3 + j / 3;
					g[id] |= 1 << (ans[i][j] - 1);
				}
			}
		}
		// for (int i = 0; i < 9; i++) {
		// 	for (int j = 0; j < 9; j++)
		// 		cout << ans[i][j] << " \n"[j == 8];
		// }
		m = 0;
		int t = (1 << 9) - 1;
		for (int i = 0; i < 9; ++i) {
			h[i] ^= t;
			w[i] ^= t;
			g[i] ^= t;
		}
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (ans[i][j] == 0) {
					arr[m++] = { i , j };
					int id = i / 3 * 3 + j / 3;
					int t = h[i] & w[j] & g[id];
					//记录当前有多少个位置可以选择。
					sum[i][j] = __builtin_popcount(t);
				}
			}
		}
		//用1来表示，减少常数。
		//111111111
		sort(arr, arr + m, [&](const auto & a, const auto & b) {
			return sum[a.first][a.second] < sum[b.first][b.second];
		});
		dfs(0);
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j) {
				cout << ans[i][j] /*<< " \n"[j == 8]*/;
			}
		cout << '\n';
	}
}
```

#### 卡常优化角度：

1. inline大法。
2. 减少加减乘除位运算。
   1. 用空间换时间。
   2. 可以不用`__builtin_popcount()`等等。直接预处理即可。

#### 上网找的大佬代码

这份代码甚至连输入输出优化都没有开。

```cpp
#include<iostream>
#include<algorithm>
#define lowbit(x) ((x) & (-x))
using namespace std;

const int N = 9, M = 1 << N;

//ones表示0-2^9里每个数有多少个1，map快速地找出这行哪一列可以填，比如map[(10)2] = 1就知道第二列可以填1
int ones[M], map[M];
//分别表示行，列，大方格子有哪些数字没有填
int rows[N], cols[N], cell[3][3];
char s[100];

//is_set = true则在x, y填上t, 否则则把x,y处的数字删掉, t 是0-8
void draw(int x, int y, int t, int is_set) {
	if (is_set)  s[x * N + y] = '1' + t; //t 是0-8
	else s[x * N + y] = '.';

	int v = 1 << t;
	if (!is_set) v = -v;

	//如果某位没被放，则它的二进制位应该是1， 所以应该减去v
	//如果放了，它的二进制应该是0，则经过上面的取反，负负得正，-v实际上就是把二进制0变为1
	rows[x] -= v;
	cols[y] -= v;
	cell[x / 3][y / 3] -= v;
}

//x行y列可以填哪个数字, 最后得到2^i + 2^j..+..，这些i, j就是可以填的数字，最后通过map[2^i]来得到这个数字
int get(int x, int y) {
	return rows[x] & cols[y] & cell[x / 3][y / 3];
}

int init() {
	//cnt表示还剩多少个数字没有填
	int cnt = 0;
	//初始状态state的9位二进制全是1
	int state = (1 << N) - 1;

	//如果row[0] = 111111111 代表第一行可以填9个数, 这里行号是0-8
	fill(rows, rows + N, state);
	fill(cols, cols + N, state);
	fill(cell[0], cell[0] + N, state);

	for (int i = 0, k = 0; i < N; i++) {
		for (int j = 0; j < N; j++, k++) {
			if (s[k] != '.') {
				draw(i, j, s[k] - '1', true);
			}
			else cnt++;
		}
	}

	return cnt;
}

bool dfs(int cnt) {
	//填完所有数字，则返回
	if (!cnt) return true;
	//最多可以填多少个数字
	int minv = 10;
	int x, y;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (s[i * N + j] == '.') {
				//可以填的数字状态，如010001，是1则表示可以填
				int state = get(i, j);
				//选一个1的个数最少的，这样的分支数量最少
				if (ones[state] < minv) {
					minv = ones[state];
					x = i, y = j;
				}
			}
		}
	}

	//依次做lowbit操作，选择每个分支
	for (int i = get(x, y); i ; i -= lowbit(i)) {

		//这个t就是要填充的数字
		int t = map[lowbit(i)];

		//填这个数字
		draw(x, y, t, true);

		//这次填充成功，则返回
		if (dfs(cnt - 1)) return true;

		//失败则回溯
		draw(x, y, t, false);
	}

	return false;
}

int main() {
	//打表，快速地知道可以哪一个数字
	for (int i = 0; i < N; i++) map[1 << i] = i;

	//ones记录每个状态有多少个1，用于选择分支少的开始搜索, 其中M = 1 << N
	for (int i = 0; i < M; i++) {
		for (int j = i; j; j -= lowbit(j)) {
			ones[i] += 1;
		}
	}

	while (cin >> s, s[0] != 'e') {
		int k = init();
		dfs(k);
		puts(s);
	}

	return 0;
}
```



