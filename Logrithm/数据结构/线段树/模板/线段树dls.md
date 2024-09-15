#### _segement tree_

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
const ll mod = 1000000007;

int n, q;
int a[N];

struct tag {
	//维护标记。
};

//标记合并。用于updatetag
tag operator + (const tag &t1, const tag &t2) {
	// (x * t1.mul + t1.add) * t2.mul + t2.add
	return {t1.mul * t2.mul % mod, (t1.add * t2.mul + t2.add) % mod};
}

//节点的内容。数据项以及内容。
//如果维护信息比较复杂。也可以考虑将信息封装。并且如上写一个区间信息合并重载函数。
struct node {
	tag t;
	ll val;
	int sz;
} seg[N * 4];

// [l, r]

//在modify以及建树之后。把两个儿子的信息合并。
void update(int id) {
	seg[id].val = (seg[id * 2].val + seg[id * 2 + 1].val) % mod;
}

//push down。
//完成两项东西。合并标记。
//修改区间信息。
void settag(int id, tag t) {
	seg[id].t = seg[id].t + t;
	seg[id].val = (seg[id].val * t.mul + seg[id].sz * t.add) % mod;
}
//记得将下放后将标记初始化。
void pushdown(int id) {
	if (seg[id].t.mul != 1 || seg[id].t.add != 0) { // 标记非空
		settag(id * 2, seg[id].t);
		settag(id * 2 + 1, seg[id].t);
		seg[id].t.mul = 1;
		seg[id].t.add = 0;
	}
}

//建树。记得建完之后ypdate.
//以及到达终点时，将节点信息修正。
void build(int id, int l, int r) {
	seg[id].t = {1, 0};
	seg[id].sz = r - l + 1;
	if (l == r) {
		seg[id].val = {a[l]};
	} else {
		int mid = (l + r) / 2;
		build(id * 2, l, mid);
		build(id * 2 + 1, mid + 1, r);
		update(id);
	}
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
	else if (ql > mid) modify(id * 2 + 1, mid + 1, r, ql,qr, t);
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
	if (l == ql && r == qr) return seg[id].val;
	int mid = (l + r) / 2;
	// 重要‼️
	pushdown(id);
	if (qr <= mid) return query(id * 2, l, mid, ql, qr);
	else if (ql > mid) return query(id * 2 + 1, mid + 1, r, ql,qr);
	else {
		// qr > mid, ql <= mid
		// [ql, mid], [mid + 1, qr]
		return (query(id * 2, l, mid, ql, mid) + 
			query(id * 2 + 1, mid + 1, r, mid + 1, qr)) % mod;
	}
}

```

#### 使用tips :

1. 该代码处理的问题是： 同时维护区间加，区间改变，区间乘法三种操作。
2. 当遇到一个问题时，一个良好的修正是。
维护信息 - 》 build -》updata - > 区间信息合并函数
tag - > modify  - 》 push_down  - >settag
query - > 返回类型，修改内容等等。信息合并的需求等等。 