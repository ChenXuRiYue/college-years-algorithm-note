**XYYYX**

[My Submissions - AtCoder Regular Contest 157](https://atcoder.jp/contests/arc157/submissions/me)

#### solve

定义一些概念：
x表示X符的个数。n表示字符长度。$pos_{i}$表示字符串中第（i + 1）个‘Y’的位置：

先分类讨论几种情况：

1. $x\ge k$，正常贪心。尽量使得YXXXY 之间的X被填满。设这种子串处理了 ， a个。那么相比于其它一些非同类操作，其贡献至少增加a个。
2. $x<k$，该情况下处理完‘X’字符后 ， 还有一些剩余的修改机会。
   1. ==证明==关于先处理完‘X’字符，显然，如果没有处理完，就说明有两次得到‘Y’的机会被白白浪费了。可以拿出处理Y的操作来处理x。无论何种情形，处理完‘X’总是最优的。
   2. 处理完x之后，那么剩下的操作次数在处理Y中如何分配？
      1. 使用等效转换的逆向思维。将问题转换成：土著‘Y’全部变成了‘X’，然后一定量操作机会下，它他们变成‘Y’。求最优解。于是转换成了第一种情况下同样的问题。

实现方式，先分类讨论，进行预处理，然后使用优先队列进行维护。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;
int sum[N] , pre[N];
int  n , k , ans;;
string s;

void solve() {
	vector<int>pos;
	for (int i = 1; i <= n; i++)
		if (s[i] == 'Y')pos.push_back(i);
	if (pos.size() == 0) {
		cout << max( k - 1 , 0) << '\n';
		return;
	}
	priority_queue<int , vector<int> , greater<int>> que;
	//对于连续段应该怎么吃处理？
	for (int i = 1; i < (int)pos.size(); i++) {
		if (pos[i] == pos[i - 1] + 1)ans++;
		else que.push(pos[i] - pos[i - 1] - 1);
	}
	while (que.empty() == false && k) {
		int top = que.top(); que.pop();
		if (top <= k) {
			ans += top + 1;
			k -= top;
		} else {
			ans += k;
			k = 0;
		}
	}
    /*处理两端的情况*/
	ans += k;
	cout << ans << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	cin >> s;
	s = ' ' + s;
	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i - 1] + (s[i] == 'X');
	}
	if (k > sum[n]) {
		for (int i = 1; i <= n; i++) {
			if (s[i] == 'X')s[i] = 'Y';
			else s[i] = 'X';
		}
		k = n - k;
	}
	solve();

}
/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*2023/3/5 陈九日
*/
```

