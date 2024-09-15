**D. Maximum Subarray**
https://codeforces.com/contest/1796/problem/D
#### 简介
给定n组数组。每一个数组长度为m。
定义一种运算。选定数组$a , b$ 进行与运算 ，运算结果为$c_i = max(a_i ,  b_i)$ 。选定任意两个数组，运算得到值域{$c$}.找出, $min (max(b_i))$.

#### solve

1. 第一个点是敏锐的感受到是二分查找问题。
   1. 设计check函数上：枚举x。对于任意一个数组 ， 都映射到一个长度为n数字d上。如果$b_i >= x$ . $d_i =1 $else $d_i = 0$。如果存在两个数组之间进行max运算之后的最小值大于等于x。那么必然运算的结果是所有二进制位上都为1的数字。
2. 投射到小值域。鸽笼定理：只需要关注解的存在性。高达$2^5$的数组数量。对于d的集合。必然都映射到d的集合上。这样就将数字分成了若干类。只需要枚举$0  <= d <=1^m - 1$这几类的数字d即可。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;
int a[N][11];
int  n , m;
int a1 , a2;

bool check(int x)
{
	int t = 1 << (m);
	vector<int> rec(t , - 1);
	//然后
	for (int i = 0; i  < n; i++) {
		int now = 0;
		for (int j = 0; j < m; j++) {
			if (a[i][j] >= x) now |= (1 << j);
		}
		rec[now] = i;
	}
	t --;
	if (rec[t] != -1) {
		a1 = a2 = rec[t];
		return true;
	}
	for (int i = 0; i < t; i++)
		for (int j = i + 1; j <= t; j++) {
			if (rec[i] != -1 && rec[j] != -1 && (i | j) == t) {
				a1 = rec[i]; a2 = rec[j];
				return true;
			}
		}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];
	int low = 0 , high = 1E9 + 10;
	while (low < high) {
		int mid = (low + high + 1) / 2;
		if (check(mid))
			low = mid;
		else high = mid - 1;
	}
	cout << a1  + 1 << ' ' << a2 + 1 << '\n';
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```



