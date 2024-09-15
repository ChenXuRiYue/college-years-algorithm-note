[addressing](https://www.luogu.com.cn/problem/CF510D)

##### 题目简介

```txt
一个靓仔，玩一个游戏：
一个带子上，有很多个点。位置被一维坐标描述。
同时他有n张卡片。每张卡片上有两个属性。
l和c.每次他花费c的钱，就可以从当前位置，移动到x+l或x-l；
他从0靠开始，他打算经过每一个格子。问是否有可能实现？如果是实现，最小花费应该为多少？
```

##### 20min

```txt
qaq
```

##### 题解

```txt
翡蜀定理：
gcd(a,b)=c;
ax+by=kc;(其中x，y为整数，且k为整数)。

要想遍历到所有的解，购买的卡片中必须存在一个子集。使得它们的公约数为1。
而仅仅通过这一个子集我们就已经可以，达到目标了。


因此问题就可以转化为，寻找一个最小的集合，满足
它们这整体的gcd=1.并且它们的总花费最小。


fij。表示从前j个数，gcd为j的最小花费。由于gcd这一个数非常的大。
空间时间花费都有点难以承受。

解决思路：
直接用一个map容器来作为滚动数组。
由于鸽笼原理，当数字比较多时，必然会有重复公约数出现。这样就就减少了重复计算。

启发性思考：
一般的二维数组，map方式，深度搜索多种方式之间的差别。
相关数论定理的总结
```



##### code 

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e2 + 10;

map<int, int> f;
int aa[maxn], bb[maxn];

int gcd(int x, int y){
    return y == 0 ? x : gcd(y, x % y);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    f[0] = 0;//初始化。
    //数据录入；
    for (int i = 1; i <= n; i++)
        cin >> aa[i];
    for (int i = 1; i <= n; i++)
        cin >> bb[i];
    //
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        a = aa[i], b = bb[i]; //分别表示长度，花费。
        map<int, int>::iterator it = f.begin();
        while (it != f.end())
        {
            int c = gcd(it->first, a);
            if (f.count(c))
                f[c] = min(it->second + b, f[c]);
            else
                f[c] = it->second + b;
            it++;
        }
    }
    //
    if (f[1])
        cout << f[1] << '\n';
    else
        cout << -1 << '\n';
}
```

###### 生长思考

```txt
总体上看，理想上（忽略空间的局限性）比较三种方式
第一种，记忆化搜索；

第二种，抽象出二重循环。

第三种，如上进行map存储转移。
```

