https://codeforces.com/contest/1539/problem/D

#### solve

面向一个结构操作。

操作具有非常大的随机性。

首先排序思想。在有序的结构上，往往能够找到操作最优化的角度。

对于操作过程中的某一个状态：

1. 如果当前有一些为花费为1的选择。选择任何一个花费为1的选择结果不会变坏。

   1. 以后这个商品是必须要买的。

   2. 放入前面。对于其它的商品类型而言，和选择二是等效的。就是现有商品数++；

2. 如果当前只有cost为2的选择。选择$max(b_i)$对应的商品的结果不会变差。



根据上面两个事实进行一个推导。用双指针模拟这一个贪心的过程即可。



#### 生长思考

1. 溢出了并不只是导致wa。如果这个溢出产生的影响和循环条件有关，就有可能进入死循环。导致tle
2. 双指针管理；low，high。指针怎么移动？



```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

typedef pair<ll, ll> llp;

const int N = 1E5 + 10;

llp d[N];


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int n;
	cin >> n;
	for ( int i = 0; i < n; i++)cin >> d[i].second >> d[i].first;
	sort (d  , d + n);

	int low = 0 , high = n - 1;
	//接下来进行双指针贪心的处理。一旦出现花费为1的选择。就立刻处理。
	//如果是操作数为2.选最后一个。如果是正常的选。到达最后一个时候。
	//如果还是花费为2.意味着效果等价。
	//如果当前有出现了效果为1的。必然在另一边已经有了替代。
	ll sum = 0;
	ll cost1 = 0, cost2 = 0;
	while (low <= high)
	{
		if (sum < d[low].first && low <= high)
		{
			ll t = min(d[low].first - sum, d[high].second);
			d[high].second -= t;
			sum = sum + t;
			cost2 = cost2 + t;
			if (d[high].second == 0)high -= 1 ;
		}
		if (sum >= d[low].first && low <= high)
		{
			cost1 += d[low].second;
			sum += d[low].second;
			low ++;
		}
	}
	cout << cost1 + cost2 * 2 << '\n';
	// while ( low <= high)
	// {
	// 	ll t = min(d[high].second, max(0, d[low].first - sum));
	// 	sum += t;
	// 	ans += 2*t;
	// }
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

