[Problem - A - Codeforces](https://codeforces.com/contest/1630/problem/A)

#### 简介

给定一个 0 .... n -1的排列。对它们进行一些匹配操作。尝试构造出 n / 2对 。 每一个元素至少出现在其中一对中。尝试构造出一组解。满足$\sum a_i\&b_i =k$

#### 15mins

1. 关注k的二进制。
2. 关注数的取反，补充等等操作。



==显然关于n - 1无解。==$错误结论。

然后k可以通过  k 以及无关位置取反得到。

1. 剩下的除了上一步构造k已经用到的两个数字的取反值。其余的情况都可以找到一个唯一取反的。

2. 上一步已经用到的两个数字的取反值之间进行and也是为0.

#### solve

1. n - 1 除了4 其余情况均有解。

#### 生长思考

1. 取反操作 (取反段落的长度为len , n = 1 << len)

   `int f(int x , int n){`

   `return x ^ (n - 1)`

   `   }     `

   

   `int f(int x , int n){`

   `unsigned t = x;`

   `return ~t&(n - 1);`

   `}`

#### *code*

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;

int n , k;
int f(int x) {
	return x ^ (n - 1);
}

int a[N] , b[N];

void work(int testNo)
{
	cin >> n >> k;
	if (k == 0) {
		for (int i = 0; i < n / 2; i++) {
			a[i] = i;
			b[i] = f(i);
		}
	}
	else if ( k < n - 1) {
		int small = min(k , f(k));

		a[small] = n - 1;
		b[small] = k;
		a[0] = 0;
		b[0] = f(k);

		for (int i = 1; i < n / 2; i++) {
			if ( i != k && i != f(k)) {
				a[i] = i;
				b[i] = f(i);
			}
		}
	}
	else if (k == n - 1) {
		if (k == 3) {
			cout << -1 << '\n';
			return;
		}
		for (int i = 0; i < n / 2; i++) {
			a[i] = i;
			b[i] = f(i);
		}
		a[0] = 0;
		b[0] = 2;
		a[1] = n - 3;
		b[1] = 1;
		a[2] = n - 1;
		b[2] = n - 2;
	}
	for (int i = 0; i < n / 2; i++) {
		cout << a[i] << ' ' << b[i] << '\n';
	}
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

