[入口](https://vjudge.net/contest/515358#problem/C)

#### 问题简介：

```txt
给出n个数，求出满足一定条件的一组数：（n个数中两两不同。）给出k,素数p.
条件为
1，a!=b,
2. (a+b)*(a^2+b^3)%p=k%p;

```

#### 思路分析

$$
这种找对的，很容易想到，哈希的方法，查询一个元素的情况是，尝试去查找前面的匹\\配项。
于是问题出在，判定条件的优化是什么？可以将数抽离出一些属性，将它们归类\\，保证，后面的
数，匹配项指向这一类时。可以直接查询前面这类数出现过的总数\\
最简单的问题是，寻找相同数的对数。哈希表记录某值的数的个数。它们的关键字就是它们自身的值\\
在这里，关键字应该是某一个函数值，例如G(a)=c;\\
\\
推导如下：\\
(a_i+a_j)(a_i^2+a_j^2)\equiv k\quad mod\quad p\\
(a_i+a_j)(a_i-a_j)(a_i^2+a_j^2)\equiv (a_i-a_j)\times k\quad mod\quad p\\
(a_i^2-a_j^2)(a_i^2+a_j^2)\equiv (a_i-a_j)\times k\quad mod\quad p\\
a_j*k-a_j^4\equiv ai*k-a_i^4(mod\quad p)
$$

#### 引出一些问题：

- #### $first$

```txt
关于负数取模的问题：
first： 负数取mod的规则。
测试程序如下：
```

```cpp
for(int i=-1;i>=-8;i--)
    cout<<i%2<<' ';
```

![](F:\本地照片库\每日一练\2022\屏幕截图 2022-09-16 232535.png)

```txt
容易总结：计算机中关于取模运算涉及原理为
k=p%n=p-n*(p/n);
舍弃小数部分。当p为一个负数的时候。就是向上取整。反之，就是向下取整。
```

- #### 第二个证明的问题：

  $$
  欲证：\\
  a\equiv b(\quad \%\quad p\quad )\\
  <=>\\
  -a\equiv -b(\quad \%\quad p\quad )\\
  不妨设a为正数：\\
  若b为负数,取模的拿结果是0，或负数\\
  只有0的情况有意义。\\
  显然符合情况\\
  若b为正数\\
  t=a-【a\k】\times k;\\
  t=b-【a\k】\times k;\\
  
  p=-a-[-a\k]\times k;\\
  pp=-b-[-b\k]\times k;\\
  p=-a-[(-【a\k】*k-t)\k]\times k\\=-a-[(-【a\k】*k)\k]\times k\\=-a+【a\k】\times k\\=-t\\
  \\
  pp=-b-[(-【b\k】*k-t)\k]\times k\\=-b-[(-【b\k】*k)\k]\times k;\\=-b+【b\k】\times k\\=-t\\
  得证\\
  当a为负数时同理：
  $$

  



