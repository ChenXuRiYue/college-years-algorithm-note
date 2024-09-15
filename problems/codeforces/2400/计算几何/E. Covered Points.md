# E. Covered Points

[Problem - E - Codeforces](https://codeforces.com/contest/1036/problem/E)

You are given $n$ segments on a Cartesian plane. Each segment's endpoints have integer coordinates. Segments can intersect with each other. No two segments lie on the same line.

Count the number of distinct points with **integer coordinates**, which are covered by at least one segment.

![img](764899a97d2a0d7f8af59dc98dd8848e30f26922.png)

### solve

非常简单的容斥：（并且保证了两条直线不会共线）

计算直线上的整数点： （exgcd）

[P5656 【模板】二元一次不定方程 (exgcd) - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P5656)

求出两条直线的交点，判断是否为整数点，并且去重。
计算几何模板。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;;
const ll INF = 1E18 + 7;
const int N = 1E3 + 10;


typedef long double db;
const db EPS = 1e-9;

// 确定一个数的符号。同时避免精度问题。
inline int sign(db a) { return a < -EPS ? -1 : a > EPS; }

// 避免精度问题。
inline int cmp(db a, db b) { return sign(a - b); }

struct P {
	db x, y;
	P() {}
	P(db _x, db _y) : x(_x), y(_y) {}
	P operator+(P p) { return {x + p.x, y + p.y}; }
	P operator-(P p) { return {x - p.x, y - p.y}; }
	P operator*(db d) { return {x * d, y * d}; }
	P operator/(db d) { return {x / d, y / d}; }

	bool operator<(P p) const {
		int c = cmp(x, p.x);
		if (c) return c == -1;
		return cmp(y, p.y) == -1;
	}

	bool operator==(P o) const {
		return cmp(x, o.x) == 0 && cmp(y, o.y) == 0;
	}

	db dot(P p) { return x * p.x + y * p.y; }
	db det(P p) { return x * p.y - y * p.x; }

	db distTo(P p) { return (*this - p).abs(); }
	db alpha() { return atan2(y, x); }
	void read() { cin >> x >> y; }
	void write() {cout << "(" << x << "," << y << ")" << endl;}
	db abs() { return sqrt(abs2());}
	db abs2() { return x * x + y * y; }
	P rot90() { return P(-y, x);}
	P unit() { return *this / abs(); }
	int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
	P rot(db an) { return {x * cos(an) - y * sin(an), x * sin(an) + y * cos(an)}; }
};

#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

// 直线 p1p2, q1q2 是否恰有一个交点
bool chkLL(P p1, P p2, P q1, P q2) {
	db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return sign(a1 + a2) != 0;
}

// 求直线 p1p2, q1q2 的交点
P isLL(P p1, P p2, P q1, P q2) {
	db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}

// 判断区间 [l1, r1], [l2, r2] 是否相交
bool intersect(db l1, db r1, db l2, db r2) {
	if (l1 > r1) swap(l1, r1); if (l2 > r2) swap(l2, r2);
	return !( cmp(r1, l2) == -1 || cmp(r2, l1) == -1 );
}

// 线段 p1p2, q1q2 相交
bool isSS(P p1, P p2, P q1, P q2) {
	return	intersect(p1.x, p2.x, q1.x, q2.x) &&
	        intersect(p1.y, p2.y, q1.y, q2.y) &&
	        crossOp(p1, p2, q1) * crossOp(p1, p2, q2) <= 0 &&
	        crossOp(q1, q2, p1) * crossOp(q1, q2, p2) <= 0;
}

// 线段 p1p2, q1q2 严格相交
bool isSS_strict(P p1, P p2, P q1, P q2) {
	return crossOp(p1, p2, q1) * crossOp(p1, p2, q2) < 0 && crossOp(q1, q2, p1)
	       * crossOp(q1, q2, p2) < 0;
}

// m 在 a 和 b 之间
bool isMiddle(db a, db m, db b) {
	/*if (a > b) swap(a, b);
	return cmp(a, m) <= 0 && cmp(m, b) <= 0;*/
	return sign(a - m) == 0 || sign(b - m) == 0 || (a < m != b < m);
}

bool isMiddle(P a, P m, P b) {
	return isMiddle(a.x, m.x, b.x) && isMiddle(a.y, m.y, b.y);
}

// 点 q 在线段 p1p2 上
bool onSeg(P p1, P p2, P q) {
	return crossOp(p1, p2, q) == 0 && isMiddle(p1, q, p2);
}
// 点 p 严格在 p1p2 上
bool onSeg_strict(P p1, P p2, P q) {
	return crossOp(p1, p2, q) == 0 && sign((q - p1).dot(p1 - p2)) * sign((q - p2).dot(p1 - p2)) < 0;
}

// 求 q 到 直线p1p2 的投影（垂足） ⚠️ : p1 != p2
P proj(P p1, P p2, P q) {
	P dir = p2 - p1;
	return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}

// 求 q 以 直线p1p2 为轴的反射
P reflect(P p1, P p2, P q) {
	return proj(p1, p2, q) * 2 - q;
}

// 求 q 到 线段p1p2 的最小距离
db nearest(P p1, P p2, P q) {
	if (p1 == p2) return p1.distTo(q);
	P h = proj(p1, p2, q);
	if (isMiddle(p1, h, p2))
		return q.distTo(h);
	return min(p1.distTo(q), p2.distTo(q));
}

// 求 线段p1p2 与 线段q1q2 的距离
db disSS(P p1, P p2, P q1, P q2) {
	if (isSS(p1, p2, q1, q2)) return 0;
	return min(min(nearest(p1, p2, q1), nearest(p1, p2, q2)), min(nearest(q1, q2, p1), nearest(q1, q2, p2)));
}

// 极角排序
array<P , 2> line[N];
int x[N][2] , y[N][2];

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x[i][0] >> y[i][0];
		cin >> x[i][1] >> y[i][1];
		line[i][0] = {x[i][0] , y[i][0]};
		line[i][1] = {x[i][1] , y[i][1]};
	}
	ll ans = 0;
	int res = 0;
	for (int i = 1; i <= n; i++) {
		int dx = abs(x[i][0] - x[i][1]);
		int dy = abs(y[i][0] - y[i][1]);
		// ans += dx / (dx / __gcd(dx , dy)) + 1;
		int sum = 0;
		if (dx == 0) {
			sum = dy + 1;
		} else if (dy == 0) {
			sum = dx + 1;
		} else {
			sum = max(dx / (dx / __gcd(dx , dy)) , dy / (dy / __gcd(dx , dy))) + 1;
		}
		ans += sum;
		res += sum;
		set<pair<int , int>> rec;
		for (int j = i + 1; j <= n; j++) {
			if (isSS(line[i][0] , line[i][1] , line[j][0], line[j][1])) {
				P mid = isLL(line[i][0] , line[i][1] , line[j][0] , line[j][1]);
				// cerr << __LINE__ << mid.x << " " << mid.y << "\n";
				/*怎么判单当前是整数点？*/
				bool fx = cmp(mid.x , (int)mid.x) == 0 || cmp(mid.x , (int)mid.x + 1) == 0;
				bool fy = cmp(mid.y , (int)mid.y) == 0 || cmp(mid.y , (int)mid.y + 1) == 0;
				if (fx && fy) {
					// cerr << __LINE__ << " "  << i << " " << j << "\n";
					rec.insert({mid.x , mid.y});
				}
			}
		}
		ans -= rec.size();
	}
	// cout << res << "\n";
	cout << ans << "\n";
}
```



