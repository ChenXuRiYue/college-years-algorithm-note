###  $数位dp$

- 简介：

  - 关于问题： 常常是某整数区间内的一些计数问题；比如，满足区间内满足某条件的整数个数。

  - 由于是连续的区间的数。所以小区间的统计和大区间的统计之间存在关系。

    ```txt
    比如说
    10000......19999 
    0....9999这段后缀的变化是相似的。
    意味着。
    如果关注的数，拥有10不相连之类的结构。0....9999。如果确认了前缀的情况。接下来可以通过限定条件，以及小规模问题的解。快速统计满足结构的数字的个数。
    ```

- 要求

  1. 掌握自己最拿手的写法。

  2. 积累更多的数字关注的结构。



#### 生长思考：

对于不同的板子：

1. 处理前导0的方式不同。
2. 处理特殊的上界的数字域不同。（就是对于某一些前缀，后缀数字不可以做任意变化。否则会超出题目要求的范围。）



#### 记忆化搜索简单的模板

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int f[20][20][2]; //记忆化搜索。后面limit也记录，优化，减少if特判。且空间复杂度肯定是没有问题的
int a[20];        //用来记录当前数上的各个位置上的一些信息。

ll dfs(int no /*第几位*/, int now /*题意关注的信息*/, int limit) // limit:用来表示前缀是否贴着上界。
{
    if(f[no][now][limit]!=-1)return f[no][now][limit];
    if (!no) //是否返回看具体题意。如果一直保证合法合法搜索得到的前缀，就返回1.否则返回判断。
        return 1;
    ll res = 0;
    int mmax = limit ? a[no] : 9, res = 0; //确认合法搜索的取值空间。如果贴着上界，要保证枚举数就在范围之内。
    for (int i = 0; i <= mmax; i++)
        res += dfs(no - 1, i, a[no] == i & limit);
    return f[no][now][limit] = res;
}

int solve(int x)
{
    memset(f, -1, sizeof(f));
    int len = 0;
    while (x)
        a[++len] = x % 10, x /= 10;
    return dfs(len, a[len], true);
}
```

其实就是搜素。但是由于解的结构复杂，所以难度变大。

#### dls的板子

[数数3 - 题目 - Daimayuan Online Judge](http://oj.daimayuan.top/course/8/problem/248)

##### solve

设计状态：

$dp_{rem,exit , pre,inc}$几个下标分别表示 ， 剩下多少位后缀 ，前缀中是否已经存在一种3个递增的结构 ， 上一次选择的数字是什么 ， 当前最近后缀中，已经有多少位递增结构。



##### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;

ll dp[20][2][20][5];


//用单词前三个的习惯。
ll dfs(int rem , int exit , int pre , int inc) {
	if (rem == 0) return exit;
	if (dp[rem][exit][pre][inc] != -1)
		return dp[rem][exit][pre][inc];

	ll &res = dp[rem][exit][pre][inc];
	res = 0;

	for (int i = 0; i <= 9; i++) {
		int inc_ = (i > pre) ? min(inc + 1 , 3) : 1;
		res += dfs(rem - 1 , exit || inc_ == 3 , i , inc_);
	}
	return res;
}

ll solve(ll x) {
	x++;//细节1
	vector<int> d;
	while (x) {d.push_back(x % 10); x /= 10;}
	//处理前导0的情况。
	ll ans = 0;
	int m = d.size();
	reverse(d.begin(), d.end());
	for (int i = 1; i < m; i++) {
		for (int j = 1; j <= 9; j++) {
			ans += dfs(i - 1, 0 , j , 1);
		}
	}
	//然后处理贴着上界走的情况。
	int exit = 0 , pre = 0, inc = 0;
	for (int i = 0; i < m; i++) {
		for (int j = (i == 0); j < d[i] ; j ++) {
			//同时要记录前缀的一些信息。
			int inc_ = (j > pre) ? min(inc + 1 , 3) : 1;
			ans += dfs(m - i - 1 , exit || inc_ == 3, j , inc_);
		}
		inc = (d[i] > pre) ? min(inc + 1, 3) : 1;
		pre = d[i];
		exit |= (inc == 3);
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	memset(dp , -1 , sizeof dp);
	ll l , r;
	cin >> l >> r;
	cout << solve(r) - solve(l - 1) << '\n';
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

##### 细节捕捉

1. 对于 ++x 的作用。

   由于程序计算贴着上界的程序的情况。如果不对x进行这样的处理。最后依然要特特殊处理这种情形。

   否则只是相当于求取了 1 .... x - 1的情况。于是我们进行加一。然后就将真正解决的问题转换成了目标问题。一种非常高明的转换思想。

2. 计算的思路步骤。

   1. 先求出所有前导0的情况。

   2. 贴着上界进行dfs.另外开几个参量跟踪前缀情况。虽然这样的实现可能繁琐一些，但是不容易出错。





