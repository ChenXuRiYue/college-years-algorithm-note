# D. Circular Spanning Tree
https://codeforces.com/contest/1682/problem/D

对1 .... n的点根据顺时针排列：对这些点之间进行连边， 要求这些连边之间不能存在焦点。同时给定一个01字符串，限制约束了当前各个点的奇偶性： 请给出一个构造方案，或者说不存在合法方案：

![img](https://espresso.codeforces.com/402c10979a8035063e99b5370877562ae422c628.png)

##  solve
自己的解法是： 
关注了几个属性：
首先将：判断一些无解的情况：

1. 对一颗树的基本认识： 总度数和为偶数，这意味着奇数度数的节点必然要有偶数个。



更一般的寻找一个解法：

1. 关于根节点的选取：
   1. 偶数节点
   2. 奇数节点；

2. 一种特殊的手段，尽量圆内连点，避开更多的考虑空间。将圆划分成一段一段的。用偶数节点作为根节点，就容易处理好每一段。

具体的规则如下图：

![笔记](C:/Users/86153/Desktop/%E7%AC%94%E8%AE%B0.png)

三个关键如上：

1. 怎么划分段？ 从根节点开始偶 ....偶 奇 直到 最后一段特殊段：
2. 一般段处理？
3. 最后段怎么处理。上述都已经用绿色的线条强调完毕。

## 生长思考：

1. 非常美妙的角度挖掘：本质上依然是一个原理，

   1. 一般性
      1. 分几类之后，发现这种构造，可以唯一解决。
   2. 简洁性
      1. 成段连续。
      2. 简单明了的操作过程。
   3. 局部构造的统一到整体构造的统一。
      1. 局部段构造，到整体的构造。
   4. 递归构造。
      1. 同三
   5. 观察，定义，或者关注属性：
      1. 奇偶性
      2. 段
      3. 根节点。

   不断的面对一些模型进行构造，这几个构造手段都会更加娴熟，高明。

## code

```cpp
void work(int testNo)
{
	int n;
	string s;
	cin >> n >> s;
	int c[2] {};
	for (int i = 0; i < n; i++) {
		c[s[i] == '1']++;
	}
	if (c[1] & 1 || c[1] == 0) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	int root = 0;
	if (c[0]) {
		// 随便找一个根节点。
		while (s[root] == '1') root++;
		// 同一个方向上分类。
		// 准备将奇数度数的节点把被处理了。
		int sum = 1;
		int ptr = (root + 1) % n;
		while (sum < c[1]) {
			sum++;
			cout << root + 1 << " " << ptr + 1 << "\n";
			// 继续将其它情况处理。
			int pre;
			while (s[ptr] == '0') {
				pre = ptr;
				ptr = (ptr + 1) % n;
				cout << pre + 1 << " " << ptr + 1 << "\n";
			}
			ptr = (ptr + 1) % n;
		}
		// 然后只剩下最后一个1.
		// 两个过程：
		// 首先逆向的走，连边直到奇数节点。
		int pre = root;
		for (int nxt = (root + n - 1) % n; s[nxt] != '1'; ) {
			cout << pre + 1 << " " << nxt + 1 << "\n";
			pre = (pre + n - 1) % n;
			nxt = (nxt + n - 1) % n;
		}

		// while (s[ptr] == '0') {
		// 	ptr = (ptr + 1) % n;
		// 	pre = (pre + 1) % n;
		// 	cout << pre + 1 << " " << ptr + 1 << "\n";
		// }
		while (s[pre] == '0') {
			cout << pre + 1 << " " << ptr + 1 << "\n";
			pre = ptr;
			ptr = (ptr + 1) % n;
		}
		// 过程已经找出来了，剩下的只是模拟问题而已：
		/*
		1
		4
		1010
		*/


	}
	else {
		root = 1;
		for (int i = 2; i <= n; i++) {
			cout << root << " " << i << "\n";
		}
	}
}


signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```
