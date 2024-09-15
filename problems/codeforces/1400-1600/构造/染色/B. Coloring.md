https://codeforces.com/problemset/problem/1774/B

B    Coloring

#### 题意

给数组染色。每种颜色规定使用次数。连续k个格子之间的颜色不能相同。



#### solve

将数组分成若干段
$$
sum =\left \lceil \frac {n}{k}  \right \rceil 
$$
记录$a_i = sum$的颜色的个数。

1. $\sum(a_i==sum) <= (n - 1)\%k + 1$



如果上面条件得到了满足，一种可行的构造方法是：

接下来用其他的颜色不停循环的填某一个数组子段。

用同一种颜色 1....k ... 1 ... k .... 1一种颜色用完了就用另外一种。

1. 显然可以填满。
2. 在此过程中可以保证同一种颜色之间的两两之间的间距大于k。
   1. 中间过程中不必说。前后距离为k。
   2. 首尾端， 由于颜色的数量总数小于段数。因此必然是首尾之间的段向中间方向必然相差一个段。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;

int a[N];

void work(int testNo)
{
	int n , m , k;
	cin >> n >> m >> k;
	int mx = (n + k - 1) / k;
	//那么应该怎么处理放那不满的情况？
	bool flag = false;
	int sum = 0;
	for (int i = 1; i <= m; i++) {
		cin >> a[i];
		if (a[i] == mx) {
			sum ++;
		}
		else if (a[i] > mx) {
			flag = true;
		}
	}
//	flag |= (sum > ((n - 1) % k));
	if (sum > (n - 1) % k + 1)flag = true;
	if (flag)cout << "NO\n";
	else  cout << "YES\n";

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

#### 生长思考：

1. 计算分段后，最后一段的元素个数。

   n % k 。简单枚举一下。发现是不行的。

   可以先对整体进行左移。然后对于一段 ， 0 ， 变成了从0 开始的有序标号。

   $(n - 1)\%k + 1$