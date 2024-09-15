https://codeforces.com/problemset/problem/1765/D

1700 cf (俄罗斯的区域赛选题)

- 有若干个视频要看完。
  - 每一个视频的时间位为1分钟。
  - 每一个视频的内存不一样。
- 相关过程。
  - 选择下载一个视频时候，就相当于当前的磁盘空间就直接的占据了一定的位置情况。、
  - 当视频完全下载完毕之后，才可以开始看。
  - 观看视频的同时，就可以下载另外的视频了。
  - 一个时间段之内，只能下载一个电影。 

- 计算看完所有视频的最短时间。

#### 20mins

- 先从暴力开始进行一个优化。
- 无法打开思路，算不下去了。

#### soution

- https://codeforces.com/blog/entry/109642
  - 什么东西？
  - 贪心以及二分搜索。要我狗命。
- 第一点，最差的情况是：$n+\sum a_i$
- 假设有某一种情况使得上述可以优化，就是两者相邻顺序的放进去，一旦成功实现相邻的放进去，就可以节省下一分钟的时间。
- 问题于是转化为了：
  - 寻求某一种顺序，使得两两相邻的元素，可以同时放在同一块磁盘之中，这样就可以省下一定的时间。

##### 突破点1：

按照某一种方式构造出一种选择方式

- 1  ,n  ,2  ,n-1 ,3, n-2.......
  - 定义$f_{j}=a_{j}+a_{j-1}$
  - 令$mmax=max(f_j)$,发现所有方案的$f_j<=mmax$
- 各种情况下，最优情况的构造是：将最大的几个放在一堆。不让他们拉低贡献
- 其它的就按照上述方式进行应给排序。通过这个来判断是否可以达到里面都成立贡献的情况。
- 就是假设有一种最优的状态，其实他们都可以等效转化为上述的状态。，于是就可以满足一个二分搜索的背景了。
- 经典的最大化贡献的问题；

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
int n, k;
bool check(int x)
{
    int l = x - 1, r = n - 1;
    while (l < r)
    {
        if (a[l] + a[r] > k)
            return false;
        l++;
        if (l < r)
        {
            if (a[l] + a[r] > k)
                return false;
        }
        r--;
    }
    return true;
}
void MAIN()
{
    cin >> n >> k;
    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        ans += a[i];
    } //二分的几个要素的设计
    // ans += n;//每一个观看需要一分钟。
    sort(a, a + n, greater<int>());
    //两个下标从什么时候开始？
    //这里check的是，多少个较大值，被留在当前位。
    int low = 1, high = n; //多少个。
    //如果是0该怎么办？
    //怎么设计check函数？
    while (low < high)
    {
        int x = (low + high) >> 1;
        if (check(x))
            high = x;
        else
            low = x + 1;
    }
    cout << ans + high << '\n';
}
```

##### 生长思考：

- 构造与二分相结合：
  - 猜测某一些解，得到相关的优化表达。
  - 然后发现出如上这种的解空间。这些解空间满足着二分的前提。
- 如果二分写懵逼了。
  - 关注：两者相邻时候的情况。然后结合代码中具体的变化情况来看是否符合条件。

