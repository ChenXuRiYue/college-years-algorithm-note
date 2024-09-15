**C. Quiz Master**

[Problem - C - Codeforces](https://codeforces.com/contest/1777/problem/C)

#### 简介

从一组数$a_1...a_n$中找到一子集。满足，该子集的因数集合包含集合$\left \{1...m\right \} $
找出符合题意子集中最大元素减去最小元素得最小值。

#### solve

发现一个性质。值关注最大最小值，夹在两者之之间得值不影响结果。所以能选就选。这样枚举一个最小值，然后找到第一个填满因数得最大值即可。
**关于细节处理**
怎么快速确定有边界？
1. 对于上一次最小值得枚举。显然可以重新利用。
   1. 假设上一次枚举到[l  , r]。当枚举l + 1为最小值时。那么有边界r 必定至少为r。反证法证明即可。否则，对于l，有边界应该更小。
2. 对于维护，可以维护几个变量：
   1. cunt , 表示当前有多少个数被覆盖。（1.....m）
   2. c[N] ， 表示当前 i 这个因数被贡献多少次。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int inf = 0x0fffffff;
const int N = 1E6 + 10;

void work(int testNo)
{
	int n, m; cin >> n >> m;
	vector<int> a(n), cunt(m + 1, 0);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	vector<vector<int>> g(n);

	int ans = inf;
	int c = 0;
	for (int low = 0, high = 0; low < n; low++) {
		while (c < m && high < n) {
			for (int i = 1; i * i <= a[high]; i++) {
				if (a[high] % i == 0) {
					if (i <= m) {
						g[high].push_back(i);
						int j = a[high] / i;
						if (i != j && j <= m)
							g[high].push_back(j);
					}
				}
			}
			for (auto j : g[high]) {
				cunt[j]++;
				if (cunt[j] == 1)
					c++;
			}
			++high;
		}
		if (c == m && high - 1 < n) {
			ans = min(a[high - 1] - a[low], ans);
		}
		for (auto j : g[low]) {
			cunt[j]--;
			if (cunt[j] == 0) {
				c--;
			}
		}
	}
	if (ans >= inf)ans = -1;
	cout << ans << '\n';
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```
