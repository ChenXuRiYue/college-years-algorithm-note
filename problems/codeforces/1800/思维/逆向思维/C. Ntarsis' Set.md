## C. Ntarsis' Set

https://codeforces.com/contest/1853/problem/C

![image-20230725112849649](C:/Users/86153/AppData/Roaming/Typora/typora-user-images/image-20230725112849649.png)

### solve

关注某个时刻： 发现每一轮迭代之前，其前会出现多少个元素。于是根据这些手段，我们就可以逐步递推出当前最后的第一位在第一轮时处于什么位置。

于是集中精力解决的问题：

1. 某个位置上其前出现多少个元素？
   1. 找出函数$f(x)$ 推出当前，x之前有多少个元素。
   2. 一定要由x到 $f_x$ 吗？
      1. 由$f_x$到x ， 双指针一步一步确定，被回溯到往后偏移1....n的个数。（注意特判$a_1 \ne 0$）
      2. 细节处理，还原上一轮删除$a_j$，将会在$a_j - j$ 之后增加一个新的数字。并且保证$a_{k,(k\ge j)} - k$大于等于$a_j - j$。 因此可以跑一遍双指针。指针j表示 j之前的元素删除操作影响到了当前ans表示的位置。

```cpp
void work(int testNo) 
{
	int n , k;
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	ll ans = 1;
	for (int i = 0 , j = 0; i < k; i++) {
		while (j < n && a[j] - (j + 1) < ans)j++;
		ans += j;
	}
	cout << ans << "\n";
}
```

