https://codeforces.com/problemset/problem/1747/D

- 简介
  - 给定一个数组：
  - 进行若干次查询：{l,r}问最少可以进行多少种操作使得，这个区间上的所有数字变化为0；
  - 操作的细节为：
    - 1 . 选定一个奇数的子区间。
    - 2，使得区间每一个数变为整一个区间区间的异或和。

#### solve

- 观察角度，操作后，整体的某一些属性没有变化。
  - 这里发现，一次操作后，对区间的亦或和大小没有变化。
    - 本质上，就是每一个位置上，不改变每一个位置上的1的个数奇偶性。
  - 根据该结论，可以进行一个发散。
    - 第一个，最终可以使得它变为0的操作为，整体区间的区间和必定为0；
- 显然如果当前已经全为0了，对应0次操作。
  - 这里是一个特判点。
- 如果当前是奇数
  - 如果当异或和为0. ans=1;
  - 否则为-1；
- 如果当前为偶数。
  - [l , mid]=0   ,   [mid+1 ,  r]=0,情况之下，最小答案为2；
  - 否则答案不存在。
    - 证明如下：
      - 有没有可能经过3次使得其为0？
      - 中间一块搞一下，然后两边再搞一下。
      - 记作曲为 sumll  ,中间区间为 summm,  右区间的异或和为 sumrr.
      - 中间区间的前一块的异或和为  sumlm ,右边一块为  summr.
      - 当中间进行一次操作之后，整个区间的数都变成该区间的异或和。
        - 如果和sumlm区间长度为偶数。那么sumlm为0。如果sumlm^sumll=0说明sumll=0.矛盾。
        - 如果为奇数。sumlm=summm.所以sumll^summm=0;矛盾。
    - 如果是若干次操作呢？
      - 呕，下次再想。
- 最后一个问题，关于怎么快速得到一段长度为奇数的亦或和为0的区间？
  - 方法一：
    - 对于记录两种异或和。第一个是奇数上。第二种是偶数上的。这样对于一个位置，我们保存了两种代表可行选择的情况。可以求出一个位置的最短奇数，异或和为0的区间。
    - 利用这个来处理偶数区间情况，是否存在。
  - 方法二：
    - 如果每一个记录最近。如果当前最近刚好是奇数就刚刚好。
    - 如果不是是偶数，那么就寻找上一个fa[res],必然是最近的满足相聚奇数距离，区间xor为的对象。由递推可得，以及反证法可得。

#### code

```cpp
#include <bits/stdc++.h>
using namespace std;

void MAIN();
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    MAIN();
}
typedef long long ll;
const int maxn = 2e5 + 10;
//------code-----٩(ˊωˋ*)و ------靓仔代码-----٩(ˊωˋ*)و ----talk is cheap , show me the code--------

int a[maxn];
ll s[maxn];
int x[maxn];
int pre[maxn];

void MAIN()
{
    int n, q;
    cin >> n >> q;
    map<int, int> rec;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
        x[i] = x[i - 1] ^ a[i]; //区间异或和相关性质。
        int res = rec[x[i]];    //记录最近的情况。
        if ((i - res + 1) % 2)  //当前为偶数
            res = pre[res];     //记录上一个区间的
        pre[i] = res;           //不是奇数就是0.0肯定部分和条件
        rec[x[i]] = i;
    }
    while (q--)
    {
        int L, R;
        cin >> L >> R;
        //第一种情况。
        if (x[R] ^ x[L - 1])
        {
            cout << -1 << '\n';
            continue;
        }
        if (s[R] - s[L - 1] == 0)
        {
            cout << 0 << '\n';
            continue;
        }

        int ans = -1;
        if ((R - L + 1) % 2)
            ans = 1;
        else if (a[L] == 0 || a[R] == 0)
            ans = 1;
        else if (pre[R] >= L)
            ans = 2;
        cout << ans << '\n';
    }
}
```

