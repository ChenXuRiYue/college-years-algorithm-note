**F. Interesting Function**

[Problem - 1538F - Codeforces](https://codeforces.com/problemset/problem/1538/F)

#### 简介

将0变化到l关注每一个变化出现的次数。每一个进制位上的变化独立统计。

#### solve

##### solve1**感受一个规律：**

1. 关注每一个进位上的变化次数独立统计（就是贡献分离统计的思想：）

$a_1a_2a_3....a_n$

第1位的变化次数为$a_1$

第2位的变化次数为$a_1a_2$

第i位的变化次数为$a_1...a_i$

直接统计即可。

**code1**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;

int ans = 0;

inline int read() {
	int x = 0 ; char c = getchar() ;
	while (c >= '0' && c <= '9' ) { x = x * 10 + c - '0' ; ans += x; c = getchar() ;}
	return ans;
}
void work(int testNo) {
	ans = 0;
	read(); ans = - ans;
	read();
	printf("%d\n" , ans);
}


int main()
{
	int t;
	scanf("%d\n" , &t);
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



##### solve2

考虑数位dp。