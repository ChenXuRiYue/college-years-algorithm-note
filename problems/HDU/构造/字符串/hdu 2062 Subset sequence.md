# hdu 2062 Subset sequence

(https://acm.hdu.edu.cn/showproblem.php?pid=2062)

题目简介：

对于一个排列，分离出它的子集。并且将它们进行字典序排序， 找出字典序第m小的数组结构。

#### solve

观察几个现象：

1. 对于字典序，可以将若干组。好比从字典中寻找abandon的位置。通过一些组的统计，就可以快速的筛选，找到第m字典序的序列的结构。

第一个问题：统计两个量： $g(n) , f(n)$ : 
$f(n):$表示当排的数字为n时 ， 有多少种子集情况。
$g(n):$表示当前所有子集中 ， 每子集的数量。

关于迁移：显然$g(n)=f(n)/n$ 。关于$f(n)$的计算思想是 ， 假设从小规模的问题开始构造出更大的结构（有点像动态规划的思想。） 
$$
f(1) = 1\\
f(2) = (f(1)+1)*n\\
.......\\
f(n)=(f(n - 1)+1)\times n\\
g(n)=f(n)/n
$$
下一个解决的问题是： 根据有顺序地不断推出m地结构。
模拟一下。
1. 通过$g(n)$确定在第几组，第m个在第几组。
2. 确定在第m个结构第几组之后 ，可以得到目标序列中第一个字符。
3. 同时可以更新 ， 目标结构在当前确定的分组 中第几个位置。
4. 重复1 ， 2 ， 3 ， 进行迭代。每一次迭代确定一个字符。

#### 思考：

关于更新m的值。

1. 每一次确定第几组之后，将前面组的总数和减去。
2. 将后续字符为空的选项减去。 - 1.

对解空间分组 ， 枚举 ， 剪枝的思想非常精彩。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int N = 1E6 + 10;
ull f[N], g[N];
int s[30];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	f[1] = 1;
	ll n, m;
	for (int i = 1; i <= 20; i++) {
		f[i] = (f[i - 1] + 1) * i;
		g[i] = f[i] / i;
	}
	while (cin >> n >> m) {
		for (int i = 1; i <= 20; i++)
			s[i] = i;
		while (n && m) {
			int t = (m + g[n] - 1) / g[n];
			m -= g[n] * (t - 1) + 1;
			// cout << "m : " << m << " n : " << n << '\n';
			n--;
			cout << s[t] << " \n"[m == 0];
			for (int i = t; i <= n; i++)s[i] = s[i + 1];

		}
	}
}
```





