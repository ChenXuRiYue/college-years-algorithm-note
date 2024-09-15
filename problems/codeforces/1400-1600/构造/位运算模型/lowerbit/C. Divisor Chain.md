# C. Divisor Chain (1200翻车惨案)

[Problem - C - Codeforces](https://codeforces.com/contest/1864/problem/C)

You are given an integer $x$. Your task is to reduce $x$ to $1$.

To do that, you can do the following operation:

-   select a divisor $d$ of $x$, then change $x$ to $x-d$, i.e. reduce $x$ by $d$. (We say that $d$ is a divisor of $x$ if $d$ is an positive integer and there exists an integer $q$ such that $x = d \cdot q$.)

There is an additional constraint: you **cannot** select the same value of $d$ **more than twice**.

For example, for $x=5$, the following scheme is **invalid** because $1$ is selected more than twice: $5\xrightarrow{-1}4\xrightarrow{-1}3\xrightarrow{-1}2\xrightarrow{-1}1$. The following scheme is however a valid one: $5\xrightarrow{-1}4\xrightarrow{-2}2\xrightarrow{-1}1$.

Output any scheme which reduces $x$ to $1$ with at most $1000$ operations. It can be proved that such a scheme always exists.

给你一个整数 $x$。您的任务是将$x$减为$1$。

为此，您可以执行以下操作：
- 选取$x$的除数$d$，然后把$x$改为$x-d$，即用$d$减少$x$。(如果 $d$是一个正整数，并且存在一个整数 $q$，使得 $x = d \cdot q$，那么我们说 $d$是 $x$的除数）。
还有一个额外的限制：你**不能**选择相同的 $d$值**两次以上。**两次以上。
例如，对于$x=5$，下面的方案是**无效的**，因为$1$被选择了两次以上：$5\xrightarrow{-1}4\xrightarrow{-1}3\xrightarrow{-1}2\xrightarrow{-1}1$.但下面的方案是有效的：$5\xrightarrow{-1}4\xrightarrow{-2}2\xrightarrow{-1}1$.
输出任何能以最多$1000$次运算将$x$还原为$1$的方案。可以证明这样的方案总是存在的。
### solve
赛时，对着质因数的角度硬想。想两个小时都想不出来。
那么下面是合理的思维前进：
1. 1000的可能是迷惑的
2. 100就可以了？
   1. 规模变化具有特殊。每次都是除一个大于2的质数等等。
   **那么为什么就不用二进制的角度看这个数字呢？**
   在二进制角度下， lowbit(x)必定是x 的因数。
1. 所以lowbit(x)将作为一个选择：
2. 然后惊奇的发现， lowbit(x) 至多30次减完。
最后当只剩下一个1时， 要采取特殊的处理方法：
1. 不断减半导致1前移 ， 最终变为1.
综上： 每个位的位权出现两次。

### code

```cpp
int lowbit(int x) {
	return x & -x;
}
void work(int testNo)
{
	int x;
	cin >> x;
	vector<int> ans;
	ans.push_back(x);
	while (x > 1) {
		if (x == lowbit(x)) {
			x -= x / 2;
		} else x -= lowbit(x);
		ans.push_back(x);
	}

	cout << sz(ans) << '\n';
	for (auto u : ans) {
		cout << u << " ";
	}
	cout << "\n";
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```













