# D. Berland Fair
[Problem - D - Codeforces](https://codeforces.com/contest/1073/problem/D)

XXI Berland Annual Fair is coming really soon! Traditionally fair consists of $n$ booths, arranged in a circle. The booths are numbered $1$ through $n$ clockwise with $n$ being adjacent to $1$. The $i$\-th booths sells some candies for the price of $a_i$ burles per item. Each booth has an unlimited supply of candies.

Polycarp has decided to spend at most $T$ burles at the fair. However, he has some plan in mind for his path across the booths:

-   at first, he visits booth number $1$;
-   if he has enough burles to buy **exactly one** candy from the current booth, then he buys it immediately;
-   then he proceeds to the next booth in the clockwise order (regardless of if he bought a candy or not).

Polycarp's money is finite, thus the process will end once he can no longer buy candy at any booth.

Calculate the number of candies Polycarp will buy.

**Input**

The first line contains two integers $n$ and $T$ ($1 \le n \le 2 \cdot 10^5$, $1 \le T \le 10^{18}$) — the number of booths at the fair and the initial amount of burles Polycarp has.

The second line contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le 10^9$) — the price of the single candy at booth number $i$.

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

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	ll T;
	cin >> n >> T;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	ll ans = 0 , s = 0;
	do {
		s = 0;
		/*表示能够购买的糖果数量*/
		ll sum = 0;
		for (int i = 1; i <= n; i++) {
			if (s + a[i] <= T) {
				s += a[i];
				sum++;
			}
		}
		if (s == 0) break;
		ans += sum * (T / s);
		T %= s;
	} while (s > 0);
	cout << ans << "\n";
}
/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

