**D. Walk on Matrix**
https://codeforces.com/problemset/problem/1332/D

给定举证： 规定从(1 , 1)开始， 只能够向下， 向右走。求矩阵上行动的最大and和。给出以下算法，发现该算法是不正确的。

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1332D/f77be4abbc0e4a1768015d201a26d68f6c552a32.png)

构造出一个矩阵， 使得该正确答案和上述算法得出的答案相差k。

## solve

首先特殊的 ：

1. 考虑：由算法得到的答案为0.
2. 考虑：矩阵尽量小： 
   1. $2\times2$  
   2. $2\times 3$
3. 构造思路： 骗一个人先得到，然后全部失去。 
4. 位运算中一种常见的构造思路， 构造一个高位权。可以达到区分，调整数大小等等功能.

因此可以是：

```txt
1 << 17  + k	 (1 << 17)	   	 0
k		        (1 << 17) + k    k
```

## code

```cpp
signed main()
{
	int k;
	scanf("%d" , &k);
	printf("2 3\n");
	printf("%d %d %d\n" , (1 << 17) + k , (1 << 17) , 0);
	printf("%d %d %d\n" , k , (1 << 17) + k , k);
}
```

