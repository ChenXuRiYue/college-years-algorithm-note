**Sticks**

[A-Sticks_0x23 搜索-剪枝 (nowcoder.com)](https://ac.nowcoder.com/acm/contest/1015/A)

将小木棍分成若干组等长的木棍。

#### solve

**最暴力的做法：**
枚举原始产长度然后，确定分组，然后就开始搜索。搜索状态设计：
1. 硬颈瓶好地原始长度，正在拼地原始木棒的当前长度，每个木棍的使用情况。。
2. 边界设计： 木棒数量达标。无法继续拼接而以失败告终。

**优化角度**
1. 优化搜索顺序。优先放大的木棍。
2. 排除等效冗余。
   1. 限制新加入的木棍的长度是递减的。防止搜索过程中出现先拼长度x ， 再拼y。和先拼y再拼x出现的等效构造。（其实在1中已经排好了序。）用一个搜索树的角度来看。
   2. 如果基于某个状态搜索失败了，可以获得一些信息。比如：
      1. 如果当前分支搜索失败，记录最近一次尝试拼接的木棍长度。说明拼接上该长度的木棍最终都不会成功拼接。反证法证明。
      2. 如果当前原始木棒中尝试拼入的第一根木棍的递归分支返回失败。直接判断当前分支失败，立刻回溯。
      3. 如果当前原始木棍中拼入一根木棍后，木棍恰好被拼接完整，并且接下来拼接剩余原始木棒的递归分支返回失败，那么直接判定当前分支失败。反证法证明。


首先是对解空间的宏观挖掘。和dp是类似的能力：
1. 如果当前分支搜索失败了。可以获得什么启发？

#### code

无语，第一次交的代码不懂哪里常数大了。y总的代码10ms内过。

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 70;

int n;
int sum, length;
int sticks[N];
bool st[N];

bool dfs(int u, int cur, int start)
{
    if (u * length == sum) return true;
    if (cur == length) return dfs(u + 1, 0, 0);

    for (int i = start; i < n; i ++ )
    {
        if (st[i]) continue;
        int l = sticks[i];
        if (cur + l <= length)
        {
            st[i] = true;
            if (dfs(u, cur + l, i + 1)) return true;
            st[i] = false;

            // 剪枝3 如果是第一个木棒失败，则一定失败
            if (!cur) return false;

            // 剪枝4 如果是最后一个木棒失败，则一定失败
            if (cur + l == length) return false;

            // 剪枝2 跳过相同木棒
            int j = i;
            while (j < n && sticks[j] == l) j ++ ;
            i = j - 1;
        }
    }


    return false;
}

int main()
{
    while (cin >> n, n)
    {
        sum = 0, length = 0;
        memset(st, false, sizeof st);

        for (int i = 0; i < n; i ++ )
        {
            cin >> sticks[i];
            if (sticks[i] > 50) continue;
            sum += sticks[i];
            length = max(length, sticks[i]);
        }

        // 剪枝：优化搜索顺序
        sort(sticks, sticks + n);
        reverse(sticks, sticks + n);

        for (int i = 0; i < n; i ++ )
            if (sticks[i] > 50)
                st[i] = true;

        while (true)
        {
            if (sum % length == 0 && dfs(0, 0, 0))
            {
                cout << length << endl;
                break;
            }
            length ++ ;
        }
    }

    return 0;
}
```

#### code2

蓝书上的代码：爆T款

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 10000;
int n , a[N] , v[N] , cnt , len;

// 表示当前第几根木棒 ， 当前木棒的长度 ，考察的最后一个位置。
bool dfs(int stick , int cur_len , int last) {
	//终点条件。
	if (stick > cnt)return true;
	//继续搜索
	if (cur_len == len) return dfs(stick + 1 , 0 , 0);
	int fail = 0;
	for (int i = last; i < n; i++)
		if (a[i] != fail && cur_len + a[i] <= len && v[i] != len) {
			v[i] = len;
			if (dfs(stick , cur_len + a[i] , i + 1)) return true;
			fail = a[i];
			v[i] = 0;
			//第三个剪枝
			if (cur_len == 0 ||  cur_len + a[i] == len)return false;
		}
	return false;
}



int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	while (cin >> n && n) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			sum += a[i];
		}
		sort(a , a + n /*, greater<int>()*/);
		reverse(a , a + n);
		// for (int i = 0; i < n; i++) {
		// 	cout << a[i] << " \n"[i == n - 1];
		// }
		for (len = a[0]; len <= sum; len++) {
			if (sum % len)continue;
			cnt = sum / len;
			if (dfs(1 , 0 , 0))break;
		}
		cout << len << '\n';
	}
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

