https://codeforces.com/contest/1610/problem/C

#### solve

二分

开party

1. 检查二分的前提:

​			发现如果x人数能实现。小于等于x的一定能够实现。因为少一个人对某个结构下的满意度不产生影响。

2. check函数设计

    check(x). 如果存在满足x人的一个结构。我们抓住x这个属性。发现每一个元素的$a_i$只要满足一定的性质即可。
   $$
   x_1\quad a_1:0\quad b_1:x-1\\
   x_2\quad a_2:1\quad b_2:x-2\\
   ................
   \\
   x_i\quad a_i:i-1\quad b_i:x-i
   $$
   假设现在寻找第i个。我们扫描的过程中，如果发现了一个满足当前寻找的对象的元素。就立刻放入。此时就是最优方案。

   假设选择后面的某一些结构满足方案。必然也可以去掉首部的某一些位置然后接在后边形成合法解。



二分对构造思维，处理解空间发现性质的思维的要求比较高。

1. 二分意识：使用二分之前要检查二分得可行性。

2. 挖掘性质设计check函数。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 2E5 + 10;

int a[N], b[N];

void work(int testNo)
{
	int n;
	cin >> n;
	for (int i = 1; i <= n ; i++)cin >> a[i] >> b[i];
	auto f = [&] (int x)
	{
		int cur = 0;
		for (int i = 1; i <= n ; i++)
		{
			if (b[i] >= cur && a[i] >= x - cur - 1 && cur <= x - 1 )
			{
				cur++;
			}
		}
		return cur == x;
	};

	int low = 1, high = n;
	while (low < high)
	{
		int mid = (low + high + 1) >> 1;
		if (f(mid))
			low = mid;
		else high = mid - 1;
	}
	cout << low << '\n';
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





