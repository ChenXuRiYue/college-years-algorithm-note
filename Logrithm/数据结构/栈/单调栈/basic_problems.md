https://www.luogu.com.cn/problem/P5788

# 【模板】单调栈

## 题目背景

模板题，无背景。  

2019.12.12 更新数据，放宽时限，现在不再卡常了。

## 题目描述

给出项数为 $n$ 的整数数列 $a_{1 \dots n}$。

定义函数 $f(i)$ 代表数列中第 $i$ 个元素之后第一个大于 $a_i$ 的元素的**下标**，即 $f(i)=\min_{i<j\leq n, a_j > a_i} \{j\}$。若不存在，则 $f(i)=0$。

试求出 $f(1\dots n)$。

## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个正整数 $a_{1\dots n}$。

## 输出格式

一行 $n$ 个整数 $f(1\dots n)$ 的值。

## 样例 #1

### 样例输入 #1

```
5
1 4 2 3 5
```

### 样例输出 #1

```
2 5 4 5 0
```

## 提示

【数据规模与约定】

对于 $30\%$ 的数据，$n\leq 100$；

对于 $60\%$ 的数据，$n\leq 5 \times 10^3$ ；

对于 $100\%$ 的数据，$1 \le n\leq 3\times 10^6$，$1\leq a_i\leq 10^9$。

--------

## solve

和一般的暴力做法相比

利用单调栈：

一直维护，如果出现了一个比栈顶高的元素，就进行更新。如果某一个更新失败了。更底部的元素就不需要再进行更新了。这样就大大的降低了复杂度。

单调栈本质上就维护了这样一个关系。很多问题的解决，需要利用这种关系信息。比方说最大正方形等等。



```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3E6 + 10;

int a[N];
int ans[N];
int stk[N], top = 0;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;

	for ( int i = 1; i <= n ; i++ ) {
		cin >> a[i];
		while (top != 0 && a[stk[top]] < a[i]) {
			ans[stk[top]] = i;
			top--;
		}
		stk[++top] = i;
	}
	for (int i = 1 ; i <= n  ; i++) {
		cout << ans[i] << ' ';
	}
	cout << '\n';

}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```





