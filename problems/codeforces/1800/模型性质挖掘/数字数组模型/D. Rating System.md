# D. Rating System

[Problem - D - Codeforces](https://codeforces.com/contest/1845/problem/D)
## 题面翻译
给定一个长度为 $n$ 数列 $a$，保证每项都不为 $0$。初始时 $x=0$，然后对于 $1\le i\le n$，按顺序进行如下操作：
- 如果 $x\ge k$，则 $x\rightarrow \max(k, x+a_i)$，否则 $x\rightarrow x+a_i$。
你需要求出 $k$，使得 $x$ 的值尽量大。
## solve
当选定一个k ， 并且rating恰好到达k之后 ：
1. 接下来连续的一段如负数的段和，等效于这段rating的变化操作无效。
   1. 于是找到最长的一段最大的负数段，其余的总和减去该段即为后续的rating变化.即，最终的答案是k + remain - 前缀（没有则表示0） ===> k + 最大后缀。
   关于k的选择：
1. 关注a数组的前缀和， 选择前缀和上数组的值作为k是更优的：
   1. 对于k迁移到离他最近的sum数组元素值， 效果不会更差：
      证明如下：
      1. 选择更大的元素： 
      
      两个的最大后缀其实是一样的。因此，此时k越大越好。
      如果只有更小的最近，说明，将k移动到该值，能保证其结果为更小的最近前缀和，结果不会更坏。
      补充： 注意
## 生长思考
1. 数组模型的关注角度，总是比较明确的。
   1. 前后缀。
   2. 选择前缀值为k。
   3. 策略的等效替换。

## code

```cpp
void work(int testNo)
{
	int n;
	cin >> n;
	vector<ll> a(n + 1) , pre(n + 1 , 0) , suf(n + 2 , 0);
	// 后缀加上最大前缀。
	ll ans = 0;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++) {
		pre[i] = a[i] + pre[i - 1];
	}
	for (int i = n; i >= 1; i--) {
		suf[i] = max(suf[i + 1] , pre[n] - pre[i - 1]);
	}
	ll mx = suf[1];
	for (int i = 1; i <= n; i++) {
		if (pre[i] + suf[i + 1] > mx) {
			ans = pre[i];
			mx = pre[i] + suf[i + 1];
		}
	}
	cout << max(ans , 0LL) << "\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```
