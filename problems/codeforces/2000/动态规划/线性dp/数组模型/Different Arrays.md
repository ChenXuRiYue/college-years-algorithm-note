# Different Arrays
https://codeforces.com/problemset/problem/1783/D

## 题面翻译

给你一个有 $n$ 个元素的序列，你需要进行 $n-2$ 次操作。

对于第 $i$ 次操作，你可以选择让 $a_i-a_{i+1}$ 且 $a_{i+2}+a_{i+1}$ 或者可以选择让 $a_i+a_{i+1}$ 且 $a_{i+2}-a_{i+1}$

问最后能产生多少个不同的序列。

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

You have to perform the sequence of $ n-2 $ operations on this array:

- during the first operation, you either add $ a_2 $ to $ a_1 $ and subtract $ a_2 $ from $ a_3 $ , or add $ a_2 $ to $ a_3 $ and subtract $ a_2 $ from $ a_1 $ ;
- during the second operation, you either add $ a_3 $ to $ a_2 $ and subtract $ a_3 $ from $ a_4 $ , or add $ a_3 $ to $ a_4 $ and subtract $ a_3 $ from $ a_2 $ ;
- ...
- during the last operation, you either add $ a_{n-1} $ to $ a_{n-2} $ and subtract $ a_{n-1} $ from $ a_n $ , or add $ a_{n-1} $ to $ a_n $ and subtract $ a_{n-1} $ from $ a_{n-2} $ .

So, during the $ i $ -th operation, you add the value of $ a_{i+1} $ to one of its neighbors, and subtract it from the other neighbor.

For example, if you have the array $ [1, 2, 3, 4, 5] $ , one of the possible sequences of operations is:

- subtract $ 2 $ from $ a_3 $ and add it to $ a_1 $ , so the array becomes $ [3, 2, 1, 4, 5] $ ;
- subtract $ 1 $ from $ a_2 $ and add it to $ a_4 $ , so the array becomes $ [3, 1, 1, 5, 5] $ ;
- subtract $ 5 $ from $ a_3 $ and add it to $ a_5 $ , so the array becomes $ [3, 1, -4, 5, 10] $ .

So, the resulting array is $ [3, 1, -4, 5, 10] $ .

An array is reachable if it can be obtained by performing the aforementioned sequence of operations on $ a $ . You have to calculate the number of reachable arrays, and print it modulo $ 998244353 $ .

### solve

考虑按照题目中要求的过程模拟一遍： 发现如果模拟到一个阶段时候，在前缀必然不同的前提下，如果当前$a_{i + 1}$为0。 那么其两种方案下的前缀都是相同的，这对后续状态的贡献分布乘法的贡献只有一次。如果不为0，那么有两种转移。

**状态定义：**
$f_{i , j}$ 表示当前考虑第i位，且当前第i位为j时的不同的前缀数目。
**状态转移方程：**
枚举+- 或者 -+两种方式：
1. j 等于0 -> 只对后续得状态贡献一次。$f_{i + 1 , a_{i + 1} + j} \quad += f_{i , j}$
2. j 不等于0 -> 两种方案，都可以得到唯一前缀。 
   $$
   f_{i + 1, a_{i + 1} + j} \quad += f_{i , j}\\
   f_{i + 1 , a_{i + 1} - j} \quad += f_{i , j}\\
   $$
#### 实现细节：
1. 确定范围：
   每一个数只能加减n -  2 次。因此上限可以设置为： $300\times 300 $ ， 同理可以设置下限。实现的过程中小心由于转移的范围也是整个范围，加上偏移量导致越界的问题；
2. 处理负数的手段： 偏移的技巧:
   1. 比较容易理解实现的方式是：加个小转移即可。
3. 实现过程中，若要减少常数。对加减法的取mod可以优化。如下：
   ```cpp
   void update(int& x , int y) {
   	x += y;
   	while (x >= mod)
   		x -= mod;
   }
   ```
### code
```cpp
// 注意便宜。
const int N = 300 , M = N * N;
const int mod = 998244353;
int f[2 * M +  2 * N] , g[2 * M + 2 * N];
//g[M + N];
int a[N];
// 卡一点点常数的方法。
void update(int& x , int y) {
	x += y;
	while (x >= mod)
		x -= mod;
}
// 出现了许多麻烦：
// 1. 转移方程中的偏移不大习惯。
// 2. 转移方程不够明确。 边界条件没有处理好。
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	f[a[2] + M] = 1;
	// 往后贡献的形式
	for (int i = 2; i < n; i++) {
		// 枚举转移的问题
		// 下界是什么？
		// 刷表法之一
		for (int j = 0; j <= 2 * M; j++) {
			g[j] = f[j];
			f[j] = 0;
		}
		for (int j = -M + a[i + 1]; j <= M - a[i + 1]; j++) {
			if (j == 0) {
				update(f[j + a[i + 1] + M] , g[j + M]);
			} else {
				update(f[j + a[i + 1] + M] , g[j + M]);
				update(f[j - a[i + 1] + M] , g[j + M]);
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= 2 * M; i++) {
		update(ans , f[i]);
	}
	cout << ans << "\n";
}
```