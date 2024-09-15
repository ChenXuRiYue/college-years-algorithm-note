https://codeforces.com/contest/1780/problem/D

#### solve

模拟一次计算。发现一些性质就行。

初始状态下给定n；

- 观察变化可以知道最近的未知1的位置。

​	发现前后两次1的个数的差，和下一个未定1的位置之间存在关系。

​    此时我们需要关注几点内容：

​     pre : 前一个已定1的位置(用来选取合适的减数。)

​     ans 利用位运算更新答案。

- 如果后面没有1可以确定了。减去将会得到一个负数怎么办？

  显然当前已经n已经完全确定。退出即可。由上面地原理。每次确定一位。通过这个可以控制循环        次数。




#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;

ll s[100];


void work(int testNo)
{


	//位置的权重。
	int n , cunt;
	cin >> cunt;
	n = cunt;
	int pre = 0; //前一个最后的已知位。
	int ans = 0;
	while (cunt)
	{
		cout << "- " << (1 << pre) << endl;
		//记录操作后的一的个数：
		int x;
		cin >> x;
		int t = x - n + 1;//有多少个0；
		// cout << t << '\n';
		// cout << pre << '\n';
		// cout << ans << '\n';
		ans |= 1 << (pre + t);
		pre = pre + t + 1;
		n = x;
		cunt --;
	}

	cout << "! " << ans << '\n';
}


int main()
{
	// ios::sync_with_stdio(false);
	// cin.tie(0);
	s[1] = 1;
	for (int i = 2; i <= 60; i++)
	{
		s[i] = s[i - 1] * 2;
	}
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

