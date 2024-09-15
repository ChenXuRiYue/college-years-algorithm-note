**C. The Very Beautiful Blanket**

[Problem - C - Codeforces](https://codeforces.com/contest/1802/problem/C)

#### 简介

构造一个举证。满足矩阵中的每一个4*4的矩阵中满足如下条件

1. $a_{11}\oplus a_{12}\oplus a_{21}\oplus a_{22}=a_{33}\oplus a_{34}\oplus a_{43}\oplus a_{44}$
2. $a_{13}\oplus a_{14}\oplus a_{23}\oplus a_{24}=a_{31}\oplus a_{32}\oplus a_{41}\oplus a_{42}$

找出一个元素种数最多的矩阵。

#### solve

特殊的，构造一个矩阵满足以下形式：任何一个四块的异或和都为0.

如果一个数字上的某个位置上有1怎么消除？并且要保证两两不同：

1. 对于最高的位置上： 不同的行打1个1.于是同行的两个必然可以消掉。行与行的数字之间就不会有交叉。
2. 对于较低的位置上，从1开始填比较低的位置。这样任意两行之间，上下两个元素就可以把低位的1给中和掉。于是无论怎么圈，都可以找出一个异或和为0的正方形：

#### code

```cpp
void work(int testNo)
{
	int n , m;
	cin >> n >> m;
	cout << n*m << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0 ; j < m; j++)
			cout << (i << 10) + j << " \n"[j == m - 1];
	}
}
```

