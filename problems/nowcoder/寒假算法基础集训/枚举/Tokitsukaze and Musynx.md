https://ac.nowcoder.com/acm/contest/46810/I

#### 题意

数域内属于被分为若5个区间。

点落在不同的去减少上有不同的分数。

对这些点做整体移动。求出所有方案中，分数和的最大值。



#### solve

枚举所有的可能。将每一个区域中分布相同的归为同一类。

有序枚举的思想：

争取有序的枚举的情况下，从最左边开始枚举。

然后只关注点分布的变化。就是某一个点区域改变时。就关注那一类的分数。

这个变化，可以归结为一个点的挪动距离。

于是我们维护每一个点区域变化时的距离。

最后模拟过程，计算分数变化。

#### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll oo = 0x0fffffffff;
const int N = 1E6 + 10;

ll x[N];

void work(int testNo)
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> x[i];
		x[i] = x[i] - 100000000000;
	}
	ll d[5]{};
	for (int i = 1; i <= 4; i++)cin >> d[i];

	ll v[10]{};
	for (int i = 0; i < 5; i++)cin >> v[i];

	map<ll, array<int, 5>>rec;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 4; j++) {
			rec[d[j] - x[i]+ (j==4)][j]++;
		}

	ll sum[5]{ n };

	ll ans = v[0] * n;

	for (auto i:rec)
	{
		for (int j = 1; j <= 4; j++)
		{
			sum[j] += i.second[j];
			sum[j - 1] -= i.second[j];
		}
		ll temp = 0;
		for (int j = 0; j <= 4; j++)
		{
			temp += v[j] * sum[j];
		}
		ans = max(ans, temp);
	}
	cout << ans << '\n';
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

