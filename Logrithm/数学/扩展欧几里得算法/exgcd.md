# 扩展欧几里得算法

[最大公约数 - OI Wiki (oi-wiki.org)](https://oi-wiki.org/math/number-theory/gcd/)

[P5656 【模板】二元一次不定方程 (exgcd) - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P5656)

扩展欧几里得算法：常用于求$ax + by = gcd(a , b)$的一组可行解：

求解过程：
$$
ax_1 + by_1 = gcd(a , b)\\
bx_2 + (a\%b)y_2 = gcd(b , a \% b)\\
由于:gcd(a , b) = gcd(b , a\%b)\\
ax_1 + by_1 = bx_2 + (a \%b)y_2\\
又因为：a\%b = a - \left \lfloor  \frac{a}{b} \right \rfloor b\\
所以ax_1 + by_1 = bx_2 + (a - (\left \lfloor \frac {a}{b} \right \rfloor \times b )) y_2\\
所以x_1 = y_2 , y1 = x_2 - \left \lfloor  \frac{a}{b} \right \rfloor y_2
$$

---

将$x_2 , y_2$不断代入递归求解。直到gcd为0，递归x = 1 , y = 0.回去求解。



### 性质，以及基本问题：

**1. 求出方程的一组整数解：**



**2. 求出方程的整数解个数：**



**3. **





给定不定方程

$$ax+by=c$$

若该方程无整数解，输出 $-1$。  
若该方程有整数解，且有正整数解，则输出其**正整数**解的数量，所有**正整数**解中 $x$ 的最小值，所有**正整数**解中 $y$ 的最小值，所有**正整数**解中 $x$ 的最大值，以及所有**正整数**解中 $y$ 的最大值。  
若方程有整数解，但没有正整数解，你需要输出所有**整数解**中 $x$ 的最小正整数值， $y$ 的最小正整数值。

正整数解即为 $x, y$ 均为正整数的解，$\boldsymbol{0}$ **不是正整数**。  
整数解即为 $x,y$ 均为整数的解。  
$x$ 的最小正整数值即所有 $x$ 为正整数的整数解中 $x$ 的最小值，$y$ 同理。

对于 $100\%$ 的数据，$1 \le T \le 2 \times {10}^5$，$1 \le a, b, c \le {10}^9$。



### 板子

```cpp
int Exgcd(int a, int b, int &x, int &y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  int d = Exgcd(b, a % b, x, y);
  int t = x;
  x = y;
  y = t - (a / b) * y;
  return d;
}
```

