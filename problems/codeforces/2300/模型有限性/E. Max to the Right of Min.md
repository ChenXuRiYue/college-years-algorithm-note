# E. Max to the Right of Min

[Problem - E - Codeforces](https://codeforces.com/contest/1849/problem/E)

You are given a permutation $p$ of length $n$ — an array, consisting of integers from $1$ to $n$, all distinct.

Let $p_{l,r}$ denote a subarray — an array formed by writing down elements from index $l$ to index $r$, inclusive.

Let $\mathit{maxpos}_{l,r}$ denote the **index** of the maximum element on $p_{l,r}$. Similarly, let $\mathit{minpos}_{l,r}$ denote the index of the minimum element on it.

Calculate the number of subarrays $p_{l,r}$ such that $\mathit{maxpos}_{l,r} \gt \mathit{minpos}_{l,r}$.

给你一个长度为 $n$ 的排列 $p$ - 一个数组，由从 $1$ 到 $n$ 的整数组成，所有整数都是不同的。

让$p_{l,r}$表示一个子数组--由写下从索引$l$到索引$r$（包括索引$r$）的元素组成的数组。

让$\mathit{maxpos}_{l,r}$表示$p_{l,r}$上最大元素的**索引**。同样，让 $\mathit{minpos}_{l,r}$ 表示其上最小元素的索引。

计算子数组 $p_{l,r}$的个数，使得 $\mathit{maxpos}_{l,r} \gt \mathit{minpos}_{l,r}$.

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

int a[N] , stk[N] , top = 0;
int lmi[N] , rmi[N] , lmx[N] , rmx[N];
ll ans = 0;


/*扫描左边的情况下需更加特殊的处理。*/
void LL(int l , int x , int r) {
	int q = inf , pos = x;
	for (int i = x - 1; i >= l; i--) {
		if (a[i] < q) {
			q = a[i];
			pos = rmi[i] - 1;
		}
		ans += min(pos - x , r - x);
	}
}

void RR(int l , int x , int r) {
	int q = inf , pos = x;
	for (int i = x  + 1; i <= r; i++) {
		if (a[i] < q) {
			q = a[i];
			pos = lmi[i];
		}
		ans += max(0 , pos - l + 1);
	}
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	/*单调栈：求出几个信息：*/

	a[n + 1] = 0;
	for (int i = 1; i <= n + 1; i++) {
		while (top != 0 && a[stk[top]] > a[i]) {
			rmi[stk[top]] = i;
			top--;
		}
		stk[++top] = i;
	}
	top = 0;
	a[n + 1] = inf;
	for (int  i = 1; i <= n + 1; i++) {
		while (top != 0 && a[stk[top]] < a[i]) {
			rmx[stk[top]] = i;
			top--;
		}
		stk[++top] = i;
	}
	top = 0;
	a[0] = 0;
	for (int i = n; i >= 0; i--) {
		while (top != 0 && a[stk[top]] > a[i]) {
			lmi[stk[top]] = i;
			top--;
		}
		stk[++top] = i;
	}
	top = 0;
	a[0] = inf;
	for (int i = n; i >= 0; i--) {
		while (top != 0 && a[stk[top]] < a[i]) {
			lmx[stk[top]] = i;
			top--;
		}
		stk[++top] = i;
	}
	for (int i = 1; i <= n; i++) {
		int l = lmx[i] + 1 , r = rmx[i] - 1;
		if (r - i < i - l) {
			RR(l , i , r);
		} else LL(l , i , r);
		ans += i - l;
		// cout << l << " " << i << " " << r << "\n";
		// cout << ans << "\n";
	}
	cout << ans << "\n";
}
```





