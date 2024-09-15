# E. Tenzing and Triangle

![image-20230712155721070](C:/Users/86153/AppData/Roaming/Typora/typora-user-images/image-20230712155721070.png)
[Problem - E - Codeforces](https://codeforces.com/contest/1842/problem/E)

## solve

1. 对于解集： 两个三角形不相交是（更优的），用该点来指导分阶段中的策略。
### **相关状态设计以及相关的状态转移方程：**

**==$f_{L , R}$==**表示被三角形（L ， k - L）(R , k - R)覆盖的点的代价减之和减去A(R - L)。(可以简记为（L，R)）
==$dp_{i}$== 表示考虑前缀[1 , i] ， $\sum f(l_k , r_k)$ 的最大值。  ？？ 是 [0 ,i] 还是[1 , i]? 
状态转移方程：

1. i不被任何区间覆盖 : $dp_i <--- dp_{i - 1}$
2. i被[j + 1 , i] 覆盖 ， $dp_i <--- dp_j + f(j + 1 , i)$
--------------
==$g_j$==$ = dp_j + f_{j + 1 , i}$ ：：用于配合转移状态转移方程$dp_i$
从小到大枚举i ， 维护g的变化情况。 当i-1 -> i 时：

1. $g_{0....i-1}$ 减去A。
2. 对于每一点 ，(x , k - i) ,$g_0...x$ 加上点的代价。
3. 计算$dp_i$之后，修改$g_i = dp_i$ ，关注变量表示的实际意义，i点没有包含在任何区间内，可以用该点往后构造出长度为1 的 包含 [i , i + 1] 三角形的方案最优解。

### 初始化：

1. $dp_1$ 是直接给定一个初始化，还是对于 
2. 当i= 0 时， $g_0 = 0$。 
3. 初始化的原则：符合实际。

### 实现

主要是维护g。要求进行以下几种操作：
1. 区间加
1. 全局最大值。

因此可以用线段树维护。

## 生长点：

1. 初始化：
   1. 从哪个开始转移： i : 1 ... k
   2. 最小的问题是什么？
      1. 是否可以通过0这种特殊的解问题转移
      2. 直接赋值： 怎么赋值使得下一规模的子问题是正确解？
2. 这里的解空间的探究思路：
   1. 通过替换迁移，等效；贪心的发现相交的三角形可以转移到一个更优解。从而得到了一个阶段性明显的决策结构。
   2. 对g的定义其实就是对转移部分的对象的维护。从整体上看寻找相邻阶段中g的关系。
3. 线段树维护：
   1. 线段树的下标是可以从0开始维护的。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2E5 + 10;
// 该数组用来记录某个y坐标系下的x坐标值 , 以及该点的总代价。
vector<pair<int , int>> node[N];
//const int N = 201000;
//const ll mod = 1000000007;
int n, q;
struct tag {
	//维护标记。
	ll add;
};
//标记合并。用于updatetag
tag operator + (const tag &t1, const tag &t2) {
	// (x * t1.mul + t1.add) * t2.mul + t2.add
	return {t1.add + t2.add};
}
//节点的内容。数据项以及内容。
//如果维护信息比较复杂。也可以考虑将信息封装。并且如上写一个区间信息合并重载函数。
// 维护g。
struct node {
	tag t;
	ll mx;  // 维护查询区间最大值。
	int sz;
} seg[N * 4];
// [l, r]
//在modify以及建树之后。把两个儿子的信息合并。
void update(int id) {
	// 更新区间最大值。
	seg[id].mx = max(seg[id << 1 | 1].mx , seg[id << 1].mx);
}
//push down。
//完成两项东西。合并标记。
//修改区间信息。
void settag(int id, tag t) {
	seg[id].t = seg[id].t + t;
	seg[id].mx += t.add;
}
//记得将下放后将标记初始化。
void pushdown(int id) {
	settag(id * 2, seg[id].t);
	settag(id * 2 + 1, seg[id].t);
	seg[id].t.add = 0;
}

// 节点为id，对应的区间为[l, r]，修改a[pos] -> val
//记得update
//正确sertag
void modify(int id, int l, int r, int ql, int qr, tag t) {
	if (l == ql && r == qr) {
		settag(id, t);
		return;
	}
	int mid = (l + r) / 2;
	// 重要‼️
	pushdown(id);
	if (qr <= mid) modify(id * 2, l, mid, ql, qr, t);
	else if (ql > mid) modify(id * 2 + 1, mid + 1, r, ql, qr, t);
	else {
		modify(id * 2, l, mid, ql, mid, t);
		modify(id * 2 + 1, mid + 1, r, mid + 1, qr, t);
	}
	// 重要‼️
	update(id);
}
// [ql, qr]表示查询的区间
//到达终点时及时返回。
ll query(int id, int l, int r, int ql, int qr) {
	if (l == ql && r == qr) return seg[id].mx;
	int mid = (l + r) / 2;
	// 重要‼️
	pushdown(id);
	if (qr <= mid) return query(id * 2, l, mid, ql, qr);
	else if (ql > mid) return query(id * 2 + 1, mid + 1, r, ql, qr);
	else {
		// qr > mid, ql <= mid
		// [ql, mid], [mid + 1, qr]
		return max(query(id * 2, l, mid, ql, mid) ,
		           query(id * 2 + 1, mid + 1, r, mid + 1, qr));
	}
}
/*
1. 该代码处理问题：同时维护区间加，区间改变，区间乘法三种操作。
2. 调整过程
维护信息 -> build -> updata -> 区间信息合并函数
tag - > modify  -> push_down  ->  settag
query -> 返回类型，修改内容 , 信息合并。
*/
ll dp[N];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n , k , A;
	cin >> n >> k >> A;
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		int x , y , c;
		cin >> x >> y >> c;
		node[y].emplace_back(x , c);
		ans += c;
	}
	for (int i = 1; i <= k; i++) {
		//先对g进行一个更新：
		modify(1 , 0 , k , 0 , i - 1 , { -A});
		for (auto [x , c] : node[k - i]) {
			modify(1 , 0 , k , 0 , x  , {c});
		}
		dp[i] = max(dp[i - 1] , query(1 , 0 , k , 0 , i - 1));
		modify(1 , 0 , k , i , i , {dp[i]});
		// dp[i] = dp[i - 1];
		// modify(1 , 0 , k , 0 , i - 1 , {A});
		// for (auto [x , c] : node[k - i]) modify(1 , 0 , k , 0 , x , { -c});
		// dp[i] = min(dp[i] , query(1 , 0 , k , 0 , i - 1));
		// modify(1 , 0 , k , i , i , {dp[i]});
	}
	cout << ans - dp[k] << "\n";
}
```



2023.7.12







