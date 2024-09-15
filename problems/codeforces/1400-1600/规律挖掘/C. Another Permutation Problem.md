# C. Another Permutation Problem

[Problem - C - Codeforces](https://codeforces.com/contest/1859/problem/C)

Andrey is just starting to come up with problems, and it's difficult for him. That's why he came up with a strange problem about permutations$^{\dagger}$ and asks you to solve it. Can you do it?

Let's call the cost of a permutation $p$ of length $n$ the value of the expression:

$(\sum_{i = 1}^{n} p_i \cdot i) - (\max_{j = 1}^{n} p_j \cdot j)$.

Find the maximum cost among all permutations of length $n$.

$^{\dagger}$A permutation of length $n$ is an array consisting of $n$ distinct integers from $1$ to $n$ in arbitrary order. For example, $[2,3,1,5,4]$ is a permutation, but $[1,2,2]$ is not a permutation ($2$ appears twice in the array), and $[1,3,4]$ is also not a permutation ($n=3$ but there is $4$ in the array).

安德烈刚刚开始想问题，这对他来说很难。因此，他想出了一个关于排列组合$^{\dagger}$的奇怪问题，并要求您解决它。你能做到吗？

我们把长度为$n$的排列组合$p$的代价称为表达式的值：

$(\sum_{i = 1}^{n} p_i \cdot i) - (\max_{j = 1}^{n} p_j \cdot j)$.

求所有长度为$n$的排列组合的最大成本。
 $^{\dagger}$长度为$n$的排列是一个由$n$个不同的整数组成的数组，这些整数从$1$到$n$依次排列。例如，$[2,3,1,5,4]$是一个排列，但$[1,2,2]$不是一个排列（$2$在数组中出现了两次），$[1,3,4]$也不是一个排列（$n=3$但在数组中有$4$）。

### solve

注意到数据范围比较小： 于是枚举最大位置，以及最大位置放置的情况。

1. 然后依次从大到小放置剩余的元素。 对于当前能放就放。
   1. 因为如果有一个可以与之交换。和更小的元素交换（如果属于临界态）即放在它能放置的最大位置是最优的。
   2. 注意到找到mx的位置之后，下一个元素的最大，总在 pos - 1 , pos + 1出现。 双指针不断更新即可。

**为什么赛时做那么慢？**

1. 不够大胆，猜测。并且思路的延展性比较差，思考的密度，效率都比较低。
2. 解决方法是：
   1. 一定时间，整场vp。
   2. 保持一定量的构造问题的训练。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 1E6 + 10;

void work(int testNo)
{
	int n;
	cin >> n;
	//贪心的选择能放的最大位置：
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			bool flag = true;
			ll temp = 0;
			int mx;
			if (j == n) {
				mx = n - 1;
			} else mx = n;
			int l = min(i * j / mx , n);
			if (l == i) l--;
			int r = l + 1;
			if (r == i) r++;
			while (mx) {
				if (r <= n && mx * r <= i * j) {
					temp += mx * r;
					r++ , mx--;
					if (r == i) r++;
					if (mx == j) mx--;
				} else {
					if (l == 0 || l * mx > i * j) flag = false;
					temp += mx * l;
					l-- , mx--;
					if (l == i) l--;
					if (mx == j)mx--;
				}
			}
			if (flag) ans = max(ans , temp);
		}
	}
	cout << ans << "\n";
}

signed main()
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



