**D. Super-Permutation**

[Problem - D - Codeforces](https://codeforces.com/contest/1822/problem/D)

![image-20230501111048610](image-20230501111048610.png)

![image-20230501111103046](image-20230501111103046.png)

#### solve

mod 数： 逐步渐近。一道非常精彩的题；



#### code

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using i64 = long long;
using ull = unsigned long long;
using ld = long double;
using uint = unsigned int;
using pii = pair<int , int>;
using pli = pair<ll , int>;
using pll = pair<ll , ll>;


#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define pb push_back
#define fi first
#define se second

const int inf = 1 << 29;
const ll INF = 1LL << 60;
const int N = 1E6 + 10;
int ans[N];

void work(int testNo)
{
	int n;
	cin >> n;
	if (n == 1) {
		cout << 1 << "\n";
		return;
	}
	if (n % 2) {
		cout << -1 << "\n";
		return;
	}
	ans[1] = n;
	ans[2] = n - 1;
	for (int i = 3; i <= n; i++) {
		if (i % 2) ans[i] = n + 1 - ans[i - 1];
		else ans[i] = n - 1 - ans[i - 1];
	}
	for (int i = 1; i <= n; i++)
		cout << ans[i] << " \n"[i == n];
}

signed main()
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

