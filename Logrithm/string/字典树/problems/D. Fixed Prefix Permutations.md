复习次数：

1. 2023.3.10



https://codeforces.com/contest/1792/problem/D

给定两个若干个排列：（1....n）

对于两个排列

$p,q$

定义一种运算：
$$
t = p\times q\\
t_i= q_{p_i}
$$
定义排列的美丽值为从1开始的连续最大前缀。

对于每一个排列，作为前值和集合中的任意排列（包括自己），运算后的排列集合中。求出其中的最大美丽值。

#### solve

研究这种运算的性质。

如果想要得到美丽值尽可能大的$p\times q$。对于q。记录$s_i$表示其中i的位置。那么这个序列和q的公共前缀越大,结果

美丽度越大。

因此我们对每一个排列都求出$s_i$。当我们基于问题查询$p$排列时，就是找出其与$s$集合的最大公共前缀。

##### first

可以直接维护一个set。记录下所有的前缀。对于$p$从大到小枚举前缀。查询是否出现。

复杂度为$m*n*log(m*n)$

##### second

由于数字只有1....0；可以投射到0....9;或者就数组下标1 ....10;

维护一个字典树。

复杂度为$O(m*n)$



#### code

##### first

```cpp
#include<bits/stdc++.h>
using  namespace std;
using ll = long long;
const int N = 5E4 + 10;

int n , m;
string s[N];
int pos[N][10];

void solve()
{
    cin >> n >> m;
    //先输入数据。
    //然后进行处理找到理想匹配的情况。如果作为前值。其最优对应数组。
    //如果作为后值，其最优数组如何，
    set<string>rec;
    for (int i = 1; i <= n; i++)
    {
        s[i].clear();
        for (int j = 0; j < m; j++)
        {
            int x;
            cin >> x;
            s[i] += x - 1 + '0';
            pos[i][x - 1] = j;
        }
        string t;
        for (int j = 0; j < m; j++)
        {
            t += pos[i][j] + '0';
            rec.insert(t);
        }
    }
    //作为前值。
    for (int i = 1; i <= n; i++)
    {
        string t;
        int ans = 0;
        for (int j = 0; j < m; j++)
        {
            t += s[i][j];
            if (rec.count(t))
                ans++;
            else break;
        }
        cout << ans << ' ';
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)solve();
}
```

##### second

忘记初始化。wa了几发。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;


int a[N][11];
int pos[N][11];
int n , m;


struct node {
	int ch[11];//一般是26个字母小心出错。
	int cnt;    //当前节点以上前缀总和
} tree[N];
int tot;//管理记录节点。

void init()
{
	tot = 0;
	for (int i = 0; i <= n * m; i++)
	{
		tree[i] = {};
	}
}

void insert(int* s)
{
	//当前及检索的节点。
	int cur = 0;
	int len = m;
	for (int i = 1; i <= len; i++)
	{
		int now = s[i];
		if (tree[cur].ch[now] == 0)
		{
			tree[cur].ch[now] = ++tot;
		}
		cur = tree[cur].ch[now];
		tree[cur].cnt++;
	}
}

int query(int* s)
{
	int cur = 0;
	int len = m;
	int res = 0;
	for (int i = 1; i <= len; i++)
	{
		int now = s[i];
		if (tree[cur].ch[now] == 0)return res;
		cur = tree[cur].ch[now];
		++res;
	}
	return res;
}
/*
*1.注意维护什么信息。
*2.注意数组的大小。
*/

void work(int testNo)
{
	cin >> n >> m;
	init();
	for (int i = 1; i <= n ; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> a[i][j];
			pos[i][a[i][j]] = j;
		}
		insert(pos[i]);
	}

	for (int i = 1; i <= n; i++)
	{
		cout << query(a[i]) << " \n"[i == n];
	}
}


int main()
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

