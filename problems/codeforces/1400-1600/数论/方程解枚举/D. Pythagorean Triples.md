**D. Pythagorean Triples**

[Problem - D - Codeforces](https://codeforces.com/contest/1487/problem/D)

#### 简介：

给定值域$[1,n]$求出范围之内的满足下面两个条件的方程的解：

1. $a^2+ b^2 = c^2$
2. $c = a^2 - b$

数学工具：等价消元，联立。式子等价变换成如下形式：
$$
c=c^2-b^2-b\\
c+b=c^2-b^2\\
c+b=(c + b)(c-b)\\
c=b+1\\
$$

$$
2c+1=a^2
$$

于是a的有效枚举域被降下来了。
继续分析该方程的性质：

1. a必须为奇数。
2. c必须为偶数，且c大于1.

所以只要a满足
$$
a\ge3\\
a
$$
枚举或者直接计算即可。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int oo = 0x0fffffff;
const int N = 1E6 + 10;
void work(int testNo){
	int n; cin >> n;
	ll ans = 0;
	for (int i = 3; i * i <= 2 * n - 1; i += 2) {
		ans ++;
	}
	cout << ans << '\n';
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```



