---
离散化：把无限空间中有限的个体映射到有限的空间中去，以此提高算法的时空效率。通俗的说，离散化是在不改变数据相对大小的条件下，对数据进行相应的缩小。
---





#### 定义

离散化，把无限空间中有限的个体映射到有限的空间中去，以此提高算法的时空效率。

通俗的说，离散化是在不改变数据相对大小的条件下，对数据进行相应的缩小。

同时总是尽量保证它们之间的偏序关系不变。



#### 使用场景模型总结。

- 给数字分配标记。保持相对大小不变将他们投到小值域中。
- 方便建立图。给每一节点分配关键字，节点序号。

- 求逆序对问题。利用树状数组或者线段树求逆序对。

#### 类型

##### 相同的值映射的字不同。

比较简单。直接搞就行。

```cpp
const int N = 1E6+10;
int a[N];//元空间。
pair<int,int> dct[N];//discretize.离散

void discretize(){
    for(int i=1; i <= n; i++){
        dct[i] = {a[i] , i};
    }
    sort(dct + 1 , dct + 1 + n);
    for (int i = 1; i <= n; i++) {
        a[dct[i].second] = i;
	} 
}
```



##### 相同值映射的字相同。

在上面的基础上搞一搞特判。

```cpp
const int N = 1E6+10;
int a[N];//元空间。
pair<int,int> dct[N];//discretize.离散

void discretize(){
    for(int i=1; i <= n; i++){
        dct[i] = {a[i] , i};
    }
    sort(dct + 1 , dct + 1 + n);
   for (int i = 1; i <= n; i++) {
		//要追求稳定排序吗？不需要。因为最终都上了一样的标记。
		if (dct[i].first != dct[i - 1].first)
			a[dct[i].second] = i;
		else a[dct[i].second] = a[dct[i - 1].second];
		//注意特判，这里容易出错。导致有一些位置没有修改。然后造成越界的问题。
	}
}
```





