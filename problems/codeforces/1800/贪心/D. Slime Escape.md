# D. Slime Escape

https://codeforces.com/problemset/problem/1734/D
### 题意：
史莱姆初始在位置k上， 并且又初始的生命值。它可以选择从左往右，左右每一个格子的有史莱姆，当与它们相遇之后，史莱姆的生命值就会加上遇见的史莱姆的生命值。之后，其它史莱姆会消失。问史莱姆是否可以到达0 或 n + 1个格子的点。
### solve
首先可以考虑用最优策略从左边逃离，或者从右边逃离：两种方向的策略解决方法一致，因此现在考虑从左边逃离。
1. 考虑操作一种有规律可循的连续向左或者向右的操作序列。
2. 一段连续向左或者连续向右的序列为何终止？
   1. 到达了0格子上。
   2. 遇到了非常小的妖怪。
3. 面对2.2情况下，应该采取什么样的策略？
   1. 回退到过程中的最大的生命值点，然后去尝试向右得到更多的增值。
### 实现key
1. 使用双指针维护两个方向上的移动。同时记录过程中生命的最大值。
2. 细节：
   1. 贪心策略更加细节的完善：
   2. 轮到轮之间的过渡：
      1. 
   3. 发现上述过程对于l , r两个方向上的寻求都是最优策略。因此不需要额外写两个循环执行。
### 生长思考：

1. 替换：

   假设有一种方案使得[L , R]之间的所有点都被遍历： 

   其具体的行为（更新的段）

   ```txt
   LLRRLLRLRLRL 的无序的一种序列：
   1. 倘若可以使得L延长到生命值更大的点。LLL后续的对于R的操作都不会受到影响。反而会更优，更自由的变化。即是兼容后续R的更新的。
   ```

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
	int n, k;
	cin >> n >> k;
	vector<int> a(n + 2, 0);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	if (a[k] < 0) {
		cout << "NO\n";
		return;
	}

	int low = k - 1, high = k + 1;
	// 当前生命值:
	ll cur = a[k];
	int reci , recj;
	// 先处理一个方向：
	while (low && high <= n) {
		// 也写不好啊：
		ll presum = cur;


		reci = low + 1;
		ll mx = cur;
		while (low) {
			if (cur + a[low] < 0) break;

			cur += a[low];
			if (cur > mx) {
				mx = cur;
				reci = low;
			}
			low--;
		}
		//

		if (low >= 1) {
			low = reci - 1;
			cur = mx;
		} else break;

		recj = high  - 1;

		while (high <= n) {
			if (cur + a[high] < 0) break;
			cur += a[high];
			if (cur > mx) {
				mx = cur;
				recj = high;
			}
			high++;
		}
		if (high <= n) {
			cur = mx;
			high = recj + 1;
		} else break;
		if (cur == presum) break;
		// 终止的标记是什么？ 可以更新的位置：
	}
	if (low && high <= n) cout << "NO\n";
	else cout << "YES\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```



### 大佬代码：

```cpp
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n, k;
	std::cin >> n >> k;
	k--;


	std::vector<int> a(n);
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}


	std::vector<std::array<i64, 2>> l, r;

	// 这一步的作用是什么？
	for (int i = 0; i < k; i++) {

		// 合并连续的负数段：
		// 第一维度： 末区间最大负数段负数和：
		// 第二维度： 区间和：
		l.push_back({std::min(a[i], 0), a[i]});

		// 对若干负数区间进行合并：
		while (l.size() > 1 && l.back()[1] <= 0) {
			auto [x, y] = l.back();
			l.pop_back();
			l.back() = {std::min(x, y + l.back()[0]), y + l.back()[1]};
		}
	}

	// 同上；

	for (int i = n - 1; i > k; i--) {
		r.push_back({std::min(a[i], 0), a[i]});
		while (r.size() > 1 && r.back()[1] <= 0) {
			auto [x, y] = r.back();
			r.pop_back();
			r.back() = {std::min(x, y + r.back()[0]), y + r.back()[1]};
		}
	}

	i64 cur = a[k];

	//基于上述结构的贪心。
	while (!l.empty() && !r.empty()) {

		// 哪个能走走哪个， 并且保证了，每走完一步后，其生命值都会变多。后续的选择都会更加自由。
		if (cur + l.back()[0] >= 0) {

			//保证后续段都是大于0的。

			cur += l.back()[1];
			l.pop_back();
		} else if (cur + r.back()[0] >= 0) {
			cur += r.back()[1];
			r.pop_back();
		} else {
			std::cout << "NO\n";
			return;
		}
	}

	std::cout << "YES\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}
```



### 生长：

1. 本质上的贪心思路是一样的：但是这里涉及到了一些数组上段划分，段处理的细节。

