[P6323 [COCI2006-2007#4\] ZBRKA - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P6323)

找出逆序对总数等于k的排列总数。

#### $15mins$

猜测复杂度应该是$O(nk)$。

#### $solve$

怎么提子问题？怎么将一些重复解的结构，并于一类作为重复利用？

题解的思路是怎么关注解空间的？

##### 状态设立：

$f_{i,j}$表示放置了1....i，其中逆序对个数为j的方案个数。

##### 状态转移方程为：

在前面的子问题中，把i填到1.....j-1的排列中。

$f_{i , j} = \sum f_{i - 1,j......(j-i+1)}$

发现，转移使用的量，是数组中连续的元素相加。所以考虑对数组前缀和优化。



#### 生长思考：

1. 构造一个解，和平时的数组不同，就是在后面某个位置上做出什么选择。（这个位置上只有一些选择。）

   所以我们的子问题就是把关键的某一步的结果浓缩记录。

   比方说，背包，某步中的多种选择问题（状态机模型。）

2. 这里的构造方式中，不断地在尾部放数字的构造方式，某一步既要考虑剩余的选择数。同时又要考虑计算逆序对数。是不可记录的。

3. 但是另一种插入方法的构造方式中，可以枚举完所有的方式。并且可以转移，容易记录。

​		所以设计子问题的时候，就是考虑一种从小到大的解结构的构造方式，同时看他是否容易记录转移。这是打开思路的状态设计思路		的一种方式。

#### $code$

- first $O(N^2\times K)$

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E3 + 10 ,  K = 10010;
const int mod = 1E9 + 7;

ll dp[K];
ll sum[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n , k;
	cin >> n >> k;
	sum[0] = 1;
	dp[0] = 1;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= k; j ++) {
			sum[j] = (sum[j - 1] + dp[j]) % mod;
		}
		for (int j = 1; j <= k; j++) {
			if ( j - i  >= 0)
				dp[j] = (sum[j] - sum[j - i] + mod) % mod;
			else dp[j] = sum[j];
		}
	}
	cout << dp[k] << '\n';
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

- second $O(N\times K)$

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E3 + 10 ,  K = 10010;
const int mod = 1E9 + 7;

ll dp[K];
ll sum[K];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n , k;
	cin >> n >> k;
	sum[0] = 1;
	dp[0] = 1;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= k; j ++) {
			sum[j] = (sum[j - 1] + dp[j]) % mod;
		}
		for (int j = 1; j <= k; j++) {
			if ( j - i  >= 0)
				dp[j] = (sum[j] - sum[j - i] + mod) % mod;
			else dp[j] = sum[j];
		}
	}
	cout << dp[k] << '\n';
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

