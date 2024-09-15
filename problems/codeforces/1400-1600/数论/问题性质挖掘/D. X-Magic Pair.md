https://codeforces.com/contest/1612/problem/D

tag : 数论 连续操作的抵消性质挖掘。

#### solve

连续操作之下：

变长称为长操作，变短称为短操作。

模拟可知，

1. 短 短-》等效于没凑操作操作。

8 5 -》8  3 -》 8  5

2. 短长-》等效于一次长操作

8  5 - 3  8 -》8 5

​    3. 长  长

8  5 - 3 5 -2 3

4. 长短

8  5  -》3 5 - 5  2  和长长相同的数字。

5. 长短长

长长

6. 长短短

长

所以一些列的操作都可以等效为 

长 长 长...... 这样的操作。

我们考虑将这些段进行一个分割。

a ，b的长短变化过程中，a不断地减去 b直到小于 a，我们进行同一种操作。此时如果x<a.

对同模那么就在路径上。



综上，总复杂度将会是$log(MAX)$

-------

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 2E5 + 10;

void work(int testNo)
{
	ll a , b , x;
	cin >> a >> b >> x;
	while (a && b) {
		if (a < b)
			swap(a, b);
		if (a >= x && a % b == x % b) {
			cout << "YES\n";
			return;
		}
		a %= b;
	}
	cout << "No\n";

}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(t);
}
```

----

#### 生长思考：

- 1600的问题，最终题解都是可以理解的。不要总想着有什么高深的结论。没有方向通过小规模问题模拟，取找出结论。

