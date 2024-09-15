**G. Garage**

[Problem - G - Codeforces](https://codeforces.com/contest/1725/problem/G)

#### 简介：

找出第n小的$b^2 - a^2$其中。a和b都是正整数。

#### solve

不妨设$b=a+1$ ， 那么$b^2-a^2 =2*a+1$
设$b= a+2$ 那么$b^2-a^2=4a+4$
设x为一个正整数：

1. 如果x为奇数。$x^2=(2*d + 1)^2=4d^2+1+4*d$此时mod 4结果为1.

2. 如果x味为偶数,$x^2=(2d)^2=4d^2$，此时mod4的结果为0.

因此由上述量种情况，已经找到了所有的解集合。这样直接计数统计即可。

1. 可以利用循环的思想。用一个计数手段直接计算。
2. 可以利用二分枚举解的方式计算：

#### code（二分操作）

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = lon long;

const int N = 1E6 + 10;
int n;
bool check(ll x) {
	ll one = (x - 1) / 2;
	ll two = x / 4 - 1;
	return one + two >= n;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	ll low = 3 , high = 1E18;
	if (n == 1) {
		cout << 3 << '\n';
		return 0;
	}
	while (low < high) {
		ll mid = (low + high) / 2;
		if (check(mid)) high = mid;
		else low = mid + 1;
	}
	cout << low + (low % 4 == 2) << '\n';
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

直接统计的方法。

```cpp
	int n; cin >> n;
	n--;
	if (n == 0)cout << 3 << '\n';
	else if (n % 3 == 1)cout << (n + 2) / 3 * 4 + 1 << '\n';
	else if (n % 3 == 2)cout << (n + 2) / 3 * 4 + 3 << '\n';
	else cout << (n + 2) / 3 * 4 + 4
```

#### 生长思考：

1. 第一个关键应该是，怎么确认第几个解。
2. 根据平方差，尝试特殊的情况，通过mod运算，发现新枚举的解之间不相交。并且观察是否充分。