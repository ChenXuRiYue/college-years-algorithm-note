**D. Valiant's New Map**

[Problem - 1731D - Codeforces](https://codeforces.com/problemset/problem/1731/D)

#### 简介：

给定一个$n\times m$矩阵。找到一个最大的l满足。在矩阵中存在一个$l\times l$矩阵，且其最小值大于l.

#### solve

1. 假定l行。那么小于l的情形一定一行。符合二分前提。
2. check函数的设计。只关注数字的一个属性，是否大于等于l。将其抽象出01矩阵，在其上面进行一个前缀和判断即可。

综上复杂度为$O(nlogn)$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;


void work(int testNo)
{
	int n , m;
	cin >> n >> m;
	vector g(n  + 1 , vector<int>(m + 1 , 0));
	vector t(n + 1 , vector<int>(m + 1 , 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> g[i][j];
		}
	}

	auto check = [&](int l) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (g[i][j] < l)t[i][j] = 0;
				else t[i][j] = 1;
			}
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				t[i][j] += t[i - 1][j];
			}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				t[i][j] += t[i][j - 1];
			}
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				if (i < l || j < l)continue;
				if (t[i][j] + t[i - l][j - l] - t[i - l][j] - t[i][j - l] == l * l) {
					return true;
				}
			}
		return false;
	};

	int low = 1 , high = max(n , m);
	while (low < high) {
		int mid = (low + high + 1) / 2;
		if (check(mid)) low = mid;
		else high = mid - 1;
	}
	cout << low << '\n';
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

