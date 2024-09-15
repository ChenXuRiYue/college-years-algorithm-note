## Fliptile

 [Fliptile - POJ 3279 - Virtual Judge (csgrandeur.cn)](https://vjudge.csgrandeur.cn/problem/POJ-3279)

https://vjudge.csgrandeur.cn/problem/POJ-3279/origin

### 简介

给定一个01矩阵。进行若干操作，选择一个点01变换。并且该点周围的点也会发生变化。问是否存在一种方案使得所有的点都为0。如果存在，输出操作次数最小的方案。

#### 20mins

1. 暴力
   1. 搜索所有某一个位置上是否翻转的方案。$2^{175}$
2. 考虑1的基础上进行一个优化：？？？？
3. 状态压缩dp搞起来？
   1. 无果

#### solve

分步枚举，将第一步的所有可能全部枚举。然后剪枝。（打开剪枝思路的常用方法：）

1. 枚举第一层。发现这样第二层的情况也将会确定。同理推到第n层。
   然后针对所有情况统计最小即可。

#### solve

```cpp
#include<iostream>
using namespace std;
const int N = 100;
const int inf = 1E9;
int  g[N];
int ans[N];
int mi = inf;
int n , m;


bool dfs(int pre , int op, int x , int sum) {
	if (x > n) {
		if (sum < mi && pre == 0) {
			mi = sum;
			return true;
		} else return false;
	}
	//t ： 用来计算方法总数。
	int t = 0;
	int op_ = pre;
	//当前行下的情况。
	int cur = g[x];
	//pre -> op_
	//g[x] + op + op_ -> cur;
	for (int i = 0 ; i < m; i++) {
		//上一次操作的影响
		if (op >> i & 1) cur ^= (1 << i);
		//该次操作的影响。
		if (op_ >> i & 1) {
			//统计次数。
			t++;
			cur ^= 1 << i & op_;
			if (i - 1 >= 0) cur ^= 1 << (i - 1);
			if (i + 1 < m) cur ^= 1 << (i + 1);
		}
	}

	bool flag = dfs(cur , op_ , x + 1 , sum + t);
	if (flag) {
		ans[x] = op_;
	}
	return flag;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			int x; cin >> x;
			g[i] += x << j;
		}
	}
	for (int i = 0 ; i < (1 << m); i++) {
		int cur = g[1];
		int t = 0;
		for (int j = 0 ; j < m; j++) {
			//计算两个变量。
			//cur1 ， op1.
			//第一层op1是枚举的。
			//g + op1 - > cur1
			if (i >> j & 1) {
				t++;
				cur ^= i & (1 << j);
				if (j - 1 >= 0) cur ^= 1 << (j - 1);
				if (j + 1 < m) cur ^= 1 << (j + 1);
			}
		}
		if (dfs(cur , i , 2 , t))ans[1] = i;
	}
	if (mi == inf) {
		cout << "IMPOSSIBLE\n";
	} else {
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < m; j++) {
				cout << (ans[i] >> j & 1) << " \n"[j == m - 1];
			}
	}
}
```

#### 生长

1. 出现了run time error的情况。这种dfs是先构造第一层的dfs。对于终点的设计要小心。
   1. 越界（无穷调用资源，爆栈）
   2. 死循环（可能会无穷调用资源，导致run time error。 也可能会判断为 time limit excessed）
