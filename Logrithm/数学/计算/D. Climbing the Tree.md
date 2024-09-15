**D. Climbing the Tree**
https://codeforces.com/contest/1810/problem/D
![image-20230401113213297](image-20230401113213297.png

![image-20230401113232052](image-20230401113232052.png)

#### solve

**关于询问1**

1. 计算出，当前信息下地最大高度以及最小高度。

手段： 关注几个量 解不等式组：
$$
d最后一次跳跃高度：\\
x , y,n(早上向上上升高度 ， 晚上向下下滑高度 , 天数)\\
d\le x\\
d + (x - y)\gt  + x\\
h_{max}=(n -1)*(x- y) + x\\
h_{min}=(n - 1)*(x-y)+y+1、、
$$
特判n = 1情况。 此时不存在上一次向上爬不到达终点地前提。所以此时 $h_{min}=h_{max} =1$

**关于询问二**

1. 根据当前地最大高度以及最小高度 ， 来计算出最长天数、最小天数。

手段：

1. 二分：

   二分天数。

2. 归纳出公式：

   符号依然使用上述体系：
   $$
   假设天数：t\\
   (x - y)*(t-1)+x\ge h\\
   t\ge\frac {(h - y)}{x-y}\\向上取整即可。
   $$
注意特判1.

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const ll inf = 1LL << 59;
const int N = 1E6 + 10;

void work(int testNo)
{
	int q;
	cin >> q;
	ll mi = 1 , mx = 2E18;
	//不断的找到最大最小高度。
	//维护， 计算可能的最快天数以及最小天数。
	while (q--) {
		ll x , y , z;
		int ch;
		cin >> ch;
		if (ch == 1) {
			cin >> x >> y >> z;
			//最高 ， 最低。
			ll a , b;
			if (z != 1) {
				a = (z - 1) * (x - y) + y + 1;
				b = (z - 1) * (x - y) + x;
			} else {
				a = 1;
				b = x;
			}
			if (a <= mx && b >= mi) {
				mi = max(mi , a);
				mx = min(mx , b);
				cout << 1 << ' ';
			} else cout << 0 << ' ';
		} else {
			cin >> x >> y;
			//cout << '\n' << mi << ' ' << mx << '\n';
			ll a , b;
			if (mi <= x) a = 1;
			else {
				a = (mi - y + x - y - 1) / (x - y);
			}
			if (mx <= x) b = 1;
			else {
				b = (mx - y + x - y - 1) / (x - y);
			}
			if (a == b)cout << a << ' ';
			else cout << -1 << ' ';
		}
	}
	cout << '\n';
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

