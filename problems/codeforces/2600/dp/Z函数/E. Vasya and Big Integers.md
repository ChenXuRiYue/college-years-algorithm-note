# E. Vasya and Big Integers

[Problem - 1051E - Codeforces](https://codeforces.com/problemset/problem/1051/E)

Vasya owns three big integers — $a, l, r$. Let's define a partition of $x$ such a sequence of strings $s_1, s_2, \dots, s_k$ that $s_1 + s_2 + \dots + s_k = x$, where $+$ is a concatanation of strings. $s_i$ is the $i$\-th element of the partition. For example, number $12345$ has the following partitions: \["1", "2", "3", "4", "5"\], \["123", "4", "5"\], \["1", "2345"\], \["12345"\] and lots of others.

Let's call some partition of $a$ beautiful if each of its elements **contains no leading zeros**.

Vasya want to know the number of beautiful partitions of number $a$, which has each of $s_i$ satisfy the condition $l \le s_i \le r$. Note that the comparison is the integer comparison, not the string one.

Help Vasya to count the amount of partitions of number $a$ such that they match all the given requirements. The result can be rather big, so print it modulo $998244353$.

### solve



### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
const int inf = 1E9 + 7;;
const ll INF = 1E18 + 7;
const int N = 1E6 + 10;
const int mod = 998244353;

void add(int& x , int y) {
	x += y;
	if (x >= mod) x -= mod;
	else if (x < 0) x += mod;
}

int f[N];

vector<int> Z(string s) {
	int n = (int)s.size();
	vector<int> z(n);
	for (int i = 1, l = 0 , r = 0; i < n; ++i) {
		if (i <= r && z[i - l] < r - i + 1) {
			z[i] = z[i - l];
		} else {
			z[i] = max(0 , r - i + 1);
			while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
		}
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	z[0] = n;
	return z;
}

vector<int> Z(string s , string parten) {
	int n = (int)s.size();
	auto zz = Z(parten + '$' + s);
	vector<int> z(n);
	for (int i = 0 , id = (int)zz.size() - n; i < n; i++ , id++) {
		z[i] = zz[id];
	}
	return z;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	string a , l , r;
	cin >> a >> l >> r;
	int n = sz(a);
	f[0] = 1; f[1] = -1;
	auto zl = Z(a , l);
	auto zr = Z(a , r);
	for (int i = 1; i <= n; i ++) {
		add(f[i] , f[i - 1]);
		if (a[i - 1] == '0') {
			if (l == "0") {
				add(f[i] , f[i - 1]);
				add(f[i + 1] , -f[i - 1]);
			}
			continue;
		}

		int L , R;
		/*还有一些边界问题没有解决：*/
		L = zl[i - 1];
		// cerr << __LINE__ << " " << L << "\n";
		if (L == sz(l)) {
			L = i + L - 1;
		} else {
			if (i + L > n) continue;
			if (a[i + L - 1] < l[L]) {
				L = i + sz(l);
			} else {
				L = i + sz(l) - 1;
			}
		}
		// cerr << __LINE__ << " " << L << "\n";
		R = zr[i - 1];
		if (R == sz(r)) {
			R = i + R - 1;
		} else {
			if (i + R > n) R = n;
			else if (a[i + R - 1] < r[R]) {
				R = i + sz(r) - 1;
			}
			else R = i + sz(r) - 2;
		}
		// cout << i << " " << L << " " << R << "\n";
		if (L > R || L > n) continue;
		R = min(R , n);
		add(f[L] , f[i - 1]);
		add(f[R + 1] , -f[i - 1]);
	}
	cout << f[n] << "\n";
}
```