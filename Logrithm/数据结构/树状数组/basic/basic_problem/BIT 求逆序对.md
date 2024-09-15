https://www.luogu.com.cn/problem/P1908

与排列的逆序对问题不一样。

这里的模型是一般的数组，而排列中的数组，每一个数字只出现一次。这里的数字可能重复并且值域过大。因此要离散化。



#### 生长思考

##### 1. 关于异常捕捉：

- 放置`modify(int x , int d);`x为0.否则会出现情况。这里可以通过assert(x!=0)来抛出异常。防止出错。
- 下面第一份代码过不了。用map实现的离散化常数过大。
  - 通过b[i]为每一个元素分配标签。nlog(n)
  - 遍历a[i]的过程中，检查a[i]   nlog(n);

##### 2.关于离散化的优化。

排序的过程中，通过一个替身。我们进行一个替身排序。有几个好处。

1. 一个no序列就是升降序。
2. 一个通过no可以访存。完成修正，数据查询。

顺便把离散化的板子给写下来。

#### code2

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5E5 + 10;

//统管线段树的长度。
int n;
int a[N];
pair<int , int> dct[N];//discretize离散化。


template <class T>
class BIT {
	//小心越界 1E6
	T c[(int)5E5 + 10];

public:
	ll query(int x) {

		ll res = 0;
		for (; x; x -= x & (-x))
			res += c[x];

		return res;
	}

	void modify(int x, ll d) {
		//捕捉不等于0的情况。
		assert(x != 0);
		for (; x <= n; x += x & (-x))
			c[x] += d;

	}
};

BIT <ll> d1; // 用来记录某一个数字的出现情况。

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	//离散化
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		dct[i] = {a[i], i};
	}
	dct[0].first = 1E9 + 10;
	sort(dct + 1, dct + 1 + n);
	for (int i = 1; i <= n; i++) {
		//要追求稳定排序吗？不需要。因为最终都上了一样的标记。
		if (dct[i].first != dct[i - 1].first)
			a[dct[i].second] = i;
		else a[dct[i].second] = a[dct[i - 1].second];
		//注意特判，这里容易出错。导致有一些位置没有修改。然后造成越界的问题。
	}
	ll ans = 0;
	//树状数组求逆序对。
	for (int i = 1 ; i <= n; i++) {
		ans += d1.query(n) - d1.query(a[i]);
		d1.modify(a[i] , 1);
	}
	cout << ans << '\n';
}
```



#### code1

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5E5 + 10;

//统管线段树的长度。
int n;
int a[N];
int b[N];
map<int, int>mp;


template <class T>
class BIT {
	//小心越界 1E6
	T c[(int)5E5 + 10];

public:
	ll query(int x) {

		ll res = 0;
		for (; x; x -= x & (-x))
			res += c[x];

		return res;
	}

	void modify(int x, ll d) {
		//捕捉不等于0的情况。
		assert(x != 0);
		for (; x <= n; x += x & (-x))
			c[x] += d;
		int k = 1;
	}
};

BIT <ll> d1; // 用来记录某一个数字的出现情况。

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	//离散化
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i] = a[i];
	}
	ll ans = 0;
	//离散化。先排序再标记
	sort(b + 1, b + 1 + n);
	for (int i = 1; i <= n; i++) {
		if (mp[b[i]] == 0)mp[b[i]] = i;
	}

	//进行逆序对的计算。
	for (int i = 1; i <= n; i++) {
		a[i] = mp[a[i]];
		ans += d1.query(n) - d1.query(a[i]);
		d1.modify(a[i], 1);
	}
	cout << ans << '\n';
}
```