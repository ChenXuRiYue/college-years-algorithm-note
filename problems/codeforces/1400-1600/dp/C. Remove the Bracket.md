# Remove the Bracket

## 题面翻译

### 题目描述

RSJ 得到了一个长为 $n$ 的序列 $a_1,a_2, \ldots, a_n$ 和一个正整数 $s$，他想要计算 $\prod\limits_{i=1}^n a_i$。对于 $a_2,a_3, \ldots, a_{n-1}$ 中的每一个，他都选取了一对**非负整数** $x_i,y_i$ 使得 $x_i + y_i = a_i$ 且 $(x_i-s) \cdot (y_i-s) \geq 0$。他使用如下的方法计算：

$$
\begin{aligned}
\text{Product} &= a_1 \cdot a_2 \cdot a_3 \cdot \ldots \cdot a_n \\
&= a_1 \cdot (x_2+y_2) \cdot (x_3+y_3) \cdot (x_4 + y_4) \cdot \ldots \cdot (x_{n-1}+y_{n-1}) \cdot a_n \\
&\overset{\text{?}}{=} a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n
\end{aligned}
$$

但是他在计算时出现了错误，不小心把括号弄丢了（式子第 $3$ 行）。于是，他想要知道写错了的式子（$F = a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n$）的最小值是多少。

~~这是原本的题面，审核改成了现在的样子（真就 remove the bracket 了，导致赛时式子有歧义，在此向大家道歉~~

### 输入格式

输入第一行一个正整数 $t$（$1\le t\le 10^4$）表示数据组数。

每组数据两行，第一行两个正整数 $n,s$（$3 \le n \le 2 \cdot 10^5$，$0 \le s \le 2 \cdot 10^5$），含义见题目描述。

第二行 $n$ 个正整数 $a_1,a_2,\ldots,a_n$（$0 \le a_i \le 2 \cdot 10^5$）表示序列 $a$。

保证所有测试数据的 $n$ 之和不超过 $2\cdot 10^5$。

### 输出格式

每组测试数据输出一行一个正整数表示 $F$ 的最小值。

## 样例 #1

### 样例输入 #1

```
10
5 0
2 0 1 3 4
5 1
5 3 4 3 5
7 2
7 6 5 4 3 2 1
5 1
1 2 3 4 5
5 2
1 2 3 4 5
4 0
0 1 1 1
5 5
4 3 5 6 4
4 1
0 2 1 0
3 99999
200000 200000 200000
6 8139
7976 129785 12984 78561 173685 15480
```

### 样例输出 #1

```
0
18
32
11
14
0
16
0
40000000000
2700826806
```

## 提示

In the first test case, $ 2\cdot 0+0\cdot 1+0\cdot 3+0\cdot 4 = 0 $ .

In the second test case, $ 5\cdot 1+2\cdot 2+2\cdot 2+1\cdot 5 = 18 $ .

-----------

#### solve

研究枚举空间，做一些解空间压缩：

1. 对于一种数字最优的选择是，分出一个最大值，一个最小值。

2. 转移过程中研究
   $$
   g(i)=a_1\times x_2 + .... +y_{i-1}\times  x_i + y_i
   $$
   对于一个数字有两种选择，最大的放前面，和前面的结构相乘，或者放后面。

   **状态定义：**

   $f_{i,0/1}$，处理到第i位。第i位选择最小/最大在前面的结构中，$g(i)-y_i$的最大值。

   **状态转移方程**

   $f_{i,0}=min(f_{i-1,0}+mx_{i-1}mi_{i},f_{i-1,1}+mi_{i-1}mi_i)$

   $f_{i,1}=min(f_{i-1,0}+mx_{i-1}mx_{i},f_{i-1,1}+mi_{i-1}mx_i)$

   **初始化**

   由于这种解的结构非常特殊，上述转移只适用于2.....n-1个状态。然后直接算出答案即可。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;

ll a[N];
ll mi[N] , mx[N];
ll f[N][2];

void work(int testNo)
{
	int n , s; cin >> n >> s;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (a[i] >= 2 * s) mi[i] = s , mx[i] = a[i] - s;
		else mi[i] = max(a[i] - s , 0LL) , mx[i] = a[i] - mi[i];
	}
	//状态设计表示大的放前面。
	f[2][0] = a[1] * mi[2];
	f[2][1] = a[1] * mx[2];
	for (int i = 3; i < n; i++) {
		f[i][0] = min(f[i - 1][0] + mx[i - 1] * mi[i] , f[i - 1][1] + mi[i - 1] * mi[i]);
		f[i][1] = min(f[i - 1][0] + mx[i - 1] * mx[i] , f[i - 1][1] + mi[i - 1] * mx[i]);
	}
	cout << min(f[n - 1][0] + mx[n - 1]*a[n] , f[n - 1][1] + mi[n - 1]*a[n]) << '\n';
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







