**D. Buying gifts**



#### solve

考虑对解空间进行枚举优化：对于第一个朋友的礼物选择。枚举一个价值最大值。于是发现可以对解空间进行。只要对每一个最大值d的所有可能枚举完全即可。

1. 关注某个最大值的解空间：
   1. 用有序的眼光考察：发现同一种（属于第一个朋友）比当前枚举最大值大的，都要选$b_j$,而比它小的任意选：考虑最优条件：必选最大值，以及通过可自由选择的一些最大值进行调整。
      1. 如果必选b中最大值大于max.那么最优方案已经确定
      2. 如果必选b中最大值小于。然后从自由选择的值中，找第一个比max大的，以及第一个小于等于max的。

#### 生长

1. contest中，满脑子想着二分。但是二分的途中就已经确定了解。
2. 有一些问题，二分check的过程中，可能就已经重复了所有的解。我相当于使用了一个最蠢的方法。每一次枚举所有的最优子集。然后看是否出过check值。但其实已经得到了所有的最优子集。在一次check的过程中就已经可以算出来。

平常的普通问题：最优子集比较庞大，或者不容易枚举。所有采用一种局部枚举的二分操作。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;

struct node {
	int x;
	int y;
} a[N];
int n;

// int pre[N];
int sux[N];
int solve() {
	set<int> rec1;
	//然后就是一直选择，一直check
	int ans = 1E9;
	for (int i = 1; i <= n; i++) {
		int mx = 0;
		if (i != n) {
			mx = sux[i + 1];
			ans = min(ans , abs(a[i].x - mx));
			//考虑从前面找一个较大值。
			if (mx < a[i].x ) {
				auto ptr = rec1.lower_bound(a[i].x);
				if (ptr != rec1.end()) ans = min(abs(*ptr - a[i].x) , ans);
				if (ptr != rec1.begin()) -- ptr;
				ans = min(ans , abs(*ptr - a[i].x));
			}
		} else {
			auto ptr = rec1.lower_bound(a[i].x);
			if (ptr != rec1.end()) ans = min(abs(*ptr - a[i].x) , ans);
			if (ptr != rec1.begin()) -- ptr;
			ans = min(ans , abs(*ptr - a[i].x));
		}
		rec1.insert(a[i].y);
	}
	return ans;
}

void work(int testNo)
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x >> a[i].y;
	}
	sort(a + 1 , a + 1 + n , [&](const node & i , const node & j) {
		return i.x < j.x;
	});
	sux[n + 1] = 0;
	for (int i = n; i >= 1; i--) {
		sux[i] = max(sux[i + 1] , a[i].y);
	}
	cout << solve() << '\n';
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```

