#### [线段树2](https://www.luogu.com.cn/problem/P3373)

#### 生长

- 维护的操作变多
- 寻求方案，进行维护上的简化，统一。

##### 20min

```txt
分析：
现在维护两种修改方式
区间乘法，区间加法。
如果是简单的一段区间乘法。那么和之前的处理一般即可。

现在两种运算：
注意运算的先后。对于一个节点 ，不能同时有信息。如果出现该情况就将该节点的懒惰标记下放。
或者对该节点新建一个vectorb标记一个先后处理的关系。 
两者不能相同，就是必须有一个先走。

主要解决的问题：维护两种区间修改。而修改之间的顺序影响最终的结果怎么处理这一种结果的方法。

思路一：
   当处理一个节点时，发现它的另一种lazy标记有内容。直接将lazy标记下放到他们的子节点。
   
   特殊例子
   当[1,n]交替进行两种运算若非常多次。到一定程度之后一层又一层的标记，一次更新的复杂度达到n的级别。似乎不太可行：但是做出尝试：
   
   建树 getsum都和之前一模一样。基本和之前一样。
   懒惰标记。
   向下寻找时，当找到一个一个区间区间时。
   懒惰标记：打懒惰标记时，将子节点的懒惰标记先处理。就是写样一个函数出来处理一颗子树的懒惰标记。
   找到不完全包含，同样将懒惰标记下放。
```

#### 方法一的实现

- 定义数据：
  - time:维护相关乘法的操作标记。
  - b维护加法运算的标记。
- 相关函数
  - $one$，更新$b$标记。
  - $two$，更新$time$标记。

- 使得=代码更简洁。



#### $code\quad first$ 

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int a[maxn];
int n;
ll mod;

template <class T>
class segement_tree
{
private:
    //写一个线段树板子并且用类语法做好封装
    struct inter //表示区间信息。每个节点管理的区间对象也是其中的一种属性。
    {
        int l;
        int r;
    };
    vector<ll> d;      //乘4；表示每个节点管理的区间的题目要求的信息。
    vector<ll> b;      //这b里选择标记。
    T l, r, c, ans;    //分别表示区间，以及查询结果。
    vector<inter> _lr; //每一个对应节点管理对应的区间。
    vector<ll> time;   //关于乘法的懒惰标记。
    bool choice;       //表示选择哪一种方式。false表示乘法，true表示加法。
                       //表示现在的选择。
    void _up(int p)    //函数的功能：标该节点标记下放。
    {
        if (_lr[p].l == _lr[p].r) //说明当前遍历的节点并不是子节点。
        {
            b[p] = 0;
            time[p] = 1;
            return;
        }
        if (b[p] == 0 && time[p] == 1) //没有标记。
            return;
        //更新向下更新。
        if (b[p] != 0 && b[2 * p] != 0) //当前两个子节点都都是区间加的状态。
        {
            //直接更新不再递归。
            d[2 * p] += (_lr[2 * p].r - _lr[2 * p].l + 1) * b[p];
            d[2 * p + 1] += (_lr[2 * p + 1].r - _lr[2 * p + 1].l + 1) * b[p];
            d[2 * p] %= mod;
            d[2 * p + 1] %= mod;
            b[p * 2] += b[p];
            b[p * 2 + 1] += b[p];
            b[p * 2] %= mod;
            b[p * 2 + 1] %= mod;
            b[p] = 0;
            return;
        }
        if (time[p] != 1 && time[p * 2] != 1) //两个都是time类型的标记。//当time=1时
        {
            d[p * 2] *= time[p];
            d[p * 2 + 1] *= time[p];
            d[2 * p + 1] %= mod;
            b[p * 2] = b[p * 2 + 1] = b[p];
            time[p * 2] *= time[p], time[p * 2 + 1] *= time[p];
            time[p * 2] %= mod;
            time[p * 2 + 1] %= mod;
            time[p] = 1;
            return;
        }
        if (time[p] != 1) //第一，下一个节点存在，下一个状态与当前懒惰标记的优先状态不同。下一个状态的标记为加法
        {
            _up(p * 2);
            _up(2 * p + 1);
            time[2 * p] = time[p * 2 + 1] = time[p];
            d[p * 2] *= time[p];
            d[p * 2 + 1] *= time[p];
            d[2 * p + 1] %= mod;
            d[2 * p] %= mod;
            time[p * 2] %= mod;
            time[p * 2 + 1] %= mod;
            //b[p * 2] = b[p * 2 + 1] = 0;
            time[p] = 1;
            return;
        }
        else //下一个标记的状态为乘法
        {
            _up(p * 2), _up(p * 2 + 1);
            d[p * 2] += (_lr[p * 2].r - _lr[p * 2].l + 1) * b[p];
            d[p * 2 + 1] += (_lr[p * 2 + 1].r - _lr[p * 2 + 1].l + 1) * b[p];
            d[2 * p + 1] %= mod;
            b[p * 2] = b[p * 2 + 1] = b[p];
            b[p << 1] = b[p * 2 + 1] = b[p];
            b[p] = 0;
            b[p * 2] %= mod;
            b[p * 2 + 1] %= mod;
        }
    }
    void _build(int s, int t, int p) //建树函数
    {
        _lr[p].l = s;
        _lr[p].r = t;
        time[p] = 1;
        if (s == t)
        {
            d[p] = a[s];
            return;
        }
        int m = s + ((t - s) >> 1); //计算中点。
        _build(s, m, p * 2);
        _build(m + 1, t, p * 2 + 1);
        d[p] = d[p * 2] + d[p * 2 + 1];
        d[p] %= mod;
    }
    void _update(int p)
    {
        //[l,r]为修改区间，c为被修改的元素的变化量，[s,t]为当前节点
        if (l <= _lr[p].l && _lr[p].r <= r)
        {
            if (choice) //=现在是加法
            {
                if (time[p] != 1) //小心覆盖先先后性。
                    _up(p);
                b[p] += c;
                b[p] %= mod;
                d[p] += (_lr[p].r - _lr[p].l + 1) * c;
                d[p] %= mod;
            }
            else //乘法。
            {
                if (b[p] != 0)
                    _up(p);
                d[p] *= c;
                time[p] *= c;
                time[p] %= mod;
                d[p] %= mod;
            }
            return;
        }
        int m = _lr[p].l + ((_lr[p].r - _lr[p].l) >> 1);
        if (b[p] && _lr[p].l != _lr[p].r) //关于加法的更新。
            _up(p);
        if (time[p] != 1 && _lr[p].l != _lr[p].r) //关于乘法的更新。
            _up(p);
        if (l <= m)
            _update(p * 2);
        if (r > m)
            _update(p * 2 + 1);
        d[p] = d[p * 2] + d[p * 2 + 1]; //再次进行更新。
        d[p] %= mod;
    }
    void _getsum(int p)
    {
        if (l <= _lr[p].l && _lr[p].r <= r)
        {
            ans += d[p];
            return;
        }
        int m = _lr[p].l + ((_lr[p].r - _lr[p].l) >> 1);
        if (b[p])
            _up(p);
        if (time[p] != 1)
            _up(p);
        if (l <= m)
            _getsum(p * 2);
        if (r > m)
            _getsum(p * 2 + 1);
        d[p] %= mod;
    }

public:
    void build() //建树函数的中间层。
    {
        _lr.resize(n * 4 + 1);
        d.resize(n * 4 + 1);
        b.resize(n * 4 + 1);
        time.resize(n * 4 + 1);
        _build(1, n, 1);
    }
    void update(int s, int t, int k, int cc)
    {
        l = s, r = t, c = k, choice = cc;
        _update(1);
    }
    T getsum(int s, int t)
    {
        l = s, r = t;
        ans = 0;
        _getsum(1);
        return ans;
    }
};
//定义一棵树。
segement_tree<ll> tree1;
int main()
{
    int q;
    cin >> n >> q >> mod;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    tree1.build();
    for (int i = 1; i <= q; i++)
    {
        int choice;
        cin >> choice;
        if (choice != 3)
        {
            int l, r, k;
            cin >> l >> r >> k;
            tree1.update(l, r, k, choice - 1);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << tree1.getsum(l, r) % mod << '\n';
        }
    }
}
```

- 没有过，样例倒是过了；写了一个稀巴烂

```txt
检查点：
1.实现是否符合算法：
样例中，有几个点缺失，更大一点的点，答案错误，或者tle;
关键是答案错误问题。如果正常发展，不应该出现wa,而是出现tle的问题。

猜测：
wa是因为溢出方面的问题。当数据达到一定的规模时候，就发生了错误，而小规模的问题并没有wa。
彻底排除，实现方面溢出的细节处理问题之后，就去回头检查算法方面的问题。

实际上，检查了一遍又一遍， 把每一个细分的点都拆出来看后。
原来是一个算法细节出现错误。
当讲一个标记往下移时。两个子节点的类型不一定一样。出错点就在这一个结论上。
```

###### $\_up$函数改动后如下：

```cpp
void _up(int p)    //函数的功能：标该节点标记下放。
    {
        if (_lr[p].l == _lr[p].r) //说明当前遍历的节点并不是子节点。
        {
            b[p] = 0;
            time[p] = 1;
            return;
        }
        if (b[p] == 0 && time[p] == 1) //没有标记。不需要下放
            return;

        _up(p * 2), _up(p * 2 + 1);
        // add
        d[2 * p] = ((_lr[2 * p].r - _lr[2 * p].l + 1) * b[p] + d[2 * p]) % mod;
        d[2 * p + 1] = ((_lr[2 * p + 1].r - _lr[2 * p + 1].l + 1) * b[p] + d[2 * p + 1]) % mod;
        b[p * 2] = b[p];
        b[p * 2 + 1] = b[p];
        b[p] = 0;

        //乘法
        d[p * 2] *= time[p];
        d[p * 2 + 1] *= time[p];
        d[2 * p + 1] %= mod;
        d[p * 2] %= mod;
        // b[p * 2] = b[p * 2 + 1] = b[p];
        time[p * 2] *= time[p], time[p * 2 + 1] *= time[p];
        time[p * 2] %= mod;
        time[p * 2 + 1] %= mod;
        time[p] = 1;
}
```



### 思路优化

- 一定要让把标记push_down吗。
  - 方式一：用另外的一些结构来存储标记。链表，作为一个区间运算的标记。在访问的时候整理一遍变成加一个数即可。
    - 估算，虽然减少了下放的次数。但直观上看，常数也比较大。
  - 方式2：一系列对额区间加法，区间乘法，可以等效为一个区间乘法，加上一个区间加法。通过等效的原理。复杂度和简单的模板一一摸一样。
- $正解代码如下：code$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100007;
ll mod;
int n;
int a[maxn];

template <class T>
class segement_tree
{
private:               //相关的数据；
    T st[maxn << 2];   //区间和
    int _l[maxn << 2]; //某个点的左边界
    int _r[maxn << 2]; //某个点的右边界。
    T add[maxn << 2];  // lazey
    T mul[maxn << 2];  // lazy
    T ans, l, r, k;    //操作相关的数据等等。
    int choice;

    void _bu(int s, int t, int p) //建树
    {
        _l[p] = s, _r[p] = t;
        add[p] = 0, mul[p] = 1;
        if (s == t)
        {
            st[p] = a[s];
            return;
        }
        int m = (s + t) >> 1;
        _bu(s, m, p << 1), _bu(m + 1, t, p << 1 | 1);
        st[p] = (st[p << 1] + st[p << 1 | 1]) % mod;
    }
    void lazy_down(int p) //标记下放的函数。
    {
        if (_l[p] == _r[p]) //终点点不可下放。不可能会对终点进行下放；。
            return;
        //区间先乘，再加。
        st[p << 1] = (st[p << 1] * mul[p] + (_r[p << 1] - _l[p << 1] + 1) * add[p]) % mod;
        st[p << 1 | 1] = (st[p << 1 | 1] * mul[p] + (_r[p << 1 | 1] - _l[p << 1 | 1] + 1) * add[p]) % mod;
        mul[p << 1] = (mul[p << 1] * mul[p]) % mod;
        mul[p << 1 | 1] = (mul[p << 1 | 1] * mul[p]) % mod;
        add[p << 1] = (add[p << 1] * mul[p] + add[p]) % mod;
        add[p << 1 | 1] = (add[p << 1 | 1] * mul[p] + add[p]) % mod;
        add[p] = 0, mul[p] = 1; //重置懒惰标记。
    }
    void lazy_up(int p) //当前节点上更新标记的函数。
    {
        if (choice == 1) //乘法
        {
            mul[p] = (k * mul[p]) % mod;
            add[p] = (k * add[p]) % mod;
            st[p] = (st[p] * k) % mod;
        }
        else //加法。
        {
            add[p] = (add[p] + k) % mod;
            st[p] = (st[p] + (_r[p] - _l[p] + 1) * k) % mod;
        }
    }
    void _up(int p) //更新函数。
    {
        if (l <= _l[p] && _r[p] <= r)
        {
            lazy_up(p);
            return;
        }
        if (mul[p] != 1 || add[p])
            lazy_down(p);
        int m = (_l[p] + _r[p]) >> 1;
        if (l <= m)
            _up(p << 1);
        if (r > m)
            _up(p << 1 | 1);
        st[p] = (st[p << 1] + st[p << 1 | 1]) % mod;
    }
    void _getsum(int p)
    {
        if (l <= _l[p] && _r[p] <= r)
        {
            ans = (ans + st[p]) % mod;
            return;
        }
        if (mul[p] != 1 || add[p])
            lazy_down(p);
        int m = (_l[p] + _r[p]) >> 1;
        if (l <= m)
            _getsum(p << 1);
        if (r > m)
            _getsum(p << 1 | 1);
    }

public:
    void build()
    {
        _bu(1, n, 1);
    }
    void update(int s, int t, int c, int choice_)
    {
        l = s, r = t, k = c, choice = choice_;
        _up(1);
    }
    T getsum(int s, int t)
    {
        ans = 0, l = s, r = t;
        _getsum(1);
        return ans % mod;
    }
};
segement_tree<ll> tree;

int main()
{

    // cout << (1 << 1 | 1) << '\n';
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int q;
    cin >> n >> q >> mod;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    tree.build();
    for (int i = 1; i <= q; i++)
    {
        int c;
        cin >> c;
        if (c != 3)
        {
            int a, b, k;
            cin >> a >> b >> k;
            tree.update(a, b, k, c);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            cout << tree.getsum(a, b) << '\n';
        }
    }
}
```

- 回顾$tips$

  - 认识各种结构：类的认识。

  - 最精妙的想法是，将多次不一样的区间操作统一。
    $$
    对一个区间进行多次的操作：\\
    a表示加法，b表示乘法\\
    操作序列具体如下：\\
    a_1,b_1.a_2,b_2;\\
    区间和为：\\
    ((st[d]+a_1)\times b_1+a_2)\times b_2\\
    整理得\\
    b_1b_2d[i]+b_1a_1+b_1b_2a_2\\
    找出一个结论：\\
    再原有得基础上,分别做两种操作。\\
    前，区间和为，对一个区间中元素操作为 mul[i],add[i];\\
    做加法操作，区间和等效为对一个区间分别做两个操作，mul[i],add[i]+k。\\
    做一个乘法操作等效为，对区间做mul[i]*k,add[i]*k这两种操作。可以通过运算律\\
    来完成证明。
    按照这样的规则来更新lazy的标记即可。
  $$
