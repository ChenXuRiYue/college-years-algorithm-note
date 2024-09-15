# DSU on tree

## 基础问题

给定一颗树，维护一些子树的信息：

1. 例如，给定一颗树，检查子树有多少种颜色。

   ps:这个问题，可以通过莫队，dfn 序， 扫描线处理。

## 基本思想

将子树信息进行合并： 本质上就是启发式合并。
DSU on tree 是和树结构相关的合并问题中，时间，空间复杂度更加优秀的方法。

==**其一般操作为**==

1. 对每一个点找到最大的儿子（重儿子：节点数最多）。将轻儿子并入重儿子中。
2. 启发想法递进：
   1. u节点集合，直接从重儿子中继承过来。再将轻儿子并入：
   2. 合并轻儿子时，对轻儿子的每一个元素进行访问。不需要维护轻儿子集合中的信息。
      1. 使用dfs序来优化常数。
   3. 整个过程中，只维护一个集合：

### 算法效率分析：

1. 时间复杂度： $O(log(n))$
2. 空间复杂度： $O(log(n))$

## 封装成板：（算法步骤）

1. dfs1（） 

   1. 将重儿子亲儿子等子树信息求出。
   2. 给树求dfs序，优化常数。

2. dfs2 ， 就是进行dsu on tree

   void dfs(int u , int fa, bool keep)

   **主要过程：**

   1. 将（轻儿子）v子树中的所有节点加到重儿子的集合里。 
      1. 这里的可以通过深搜实现，也可以通过dfs序实现。
   2. 然后将u本身加入重儿子的集合中。
   3. keep的意义： 需不需要保留当前信息。对于重儿子需要保留信息，轻儿子不需要保留信息。也就是将轻儿子合并之后，需要对轻儿子的信息进行一些合并操作。



```cpp
const int N = (int)1E6 + 10;

int l[N] , r[N] , id[N] , sz[N] , hs[N] , tot;
// int cnt[N]; //每个颜色出现的次数。
// int mxcnt; // 众数出现的次数。
// ll sumcnt , ans[N];;// 总数颜色编号的和。
/*维护信息集合*/
vector<int> e[N];
void dfs_init(int u , int fa) {
	l[u] = ++ tot;
	id[tot] = u;
	sz[u] = 1;
	hs[u] = -1;
	for (auto v : e[u]) {
		if (v == fa) continue;
		dfs_init(v , u);
		sz[u] += sz[v];
		if (hs[u] == -1 || sz[v] > sz[hs[u]])
			hs[u] = v;
	}
	r[u] = tot;
}
void dfs_solve(int u , int fa , bool keep) {
	for (auto v : e[u]) {
		if (v != fa && v != hs[u]) {
			dfs_solve(v , u , false);
		}
	}
	if (hs[u] != - 1) {
		dfs_solve(hs[u] , u , true);
		// 重儿子集合
	}
	/*主要需要修改的东西： 就是以下这两个函数add() 和 del()*/
	auto add = [&](int x) {
	};
	auto del = [&](int x) {

	};
	for (auto v : e[u]) {
		if (v != fa && v != hs[u]) {
			for (int x = l[v]; x <= r[v]; x++)
				add(id[x]);
		}
	}
	// u本身加入。
	add(u);
	ans[u] = sumcnt;
	if (!keep) {
		mxcnt = 0;
		sumcnt = 0;
		for (int x = l[u]; x <= r[u]; x++) {
			del(id[x]);
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	dfs_init(1 , 0);
	dfs_solve(1 , 0 , false);
}
```

