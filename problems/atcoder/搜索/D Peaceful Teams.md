# **D - Peaceful Teams**
https://atcoder.jp/contests/abc310/tasks/abc310_d

现在有N个人，组成T个队伍。但是一些人之间会互相讨厌。问一个有多少队伍的划分方式？

特殊的数据范围是;
$$
1\le T \le N \le 10\\
0 \le M \le \frac{N(N-1)} {2}\\
1 \le A_i \lt B_i \le N (1\le i \le M)
$$


##  solve

由于N大小只有10，只要搜出来的都是答案，那么就复杂度是够的；

**关于搜索的一些技巧：**

1. 保证顺序无关的方法；枚举某个人时，尽量只将其与前已经构成的队伍一组，或者自己新作为一个队伍。发现构造出来的方案都是不同的，并且考虑了所有可能，因此该方式的搜索出来的解空间，就是目标解空间。
2. 利用位运算等方法，对常数做一个优化。



**奇怪的问题：**

为什么将teams.reserve()这个语句删除之后 ， 程序的运行结果就会出错？发现跑几遍代码之后，连程序运行的结果都不同：



```cpp
unsigned dfs(int cur , vector<unsigned>& teams) {
	if (cur == n)
		return (int)teams.size() == t;
	unsigned ans = 0;

	for (auto & team : teams) {
		//先检查是否符合条件：
		if ((team & limit[cur]) == 0) {
			team |= 1U << cur;
			ans += dfs(cur + 1, teams);
			team ^= 1U << cur;
		}
	}
	if (teams.size() < t) {
		unsigned team = 1U << cur;
		teams.push_back(team);
		ans += dfs(cur + 1 , teams);
		teams.pop_back();
	}
	return ans;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> t >> m;
	for (int i = 0; i < m; i++) {
		int u , v;
		cin >> u >> v;
		u-- , v--;
		limit[v] |= 1U << u;
	}
	vector<unsigned> teams;
	teams.reserve(t);
	cout << dfs(0 , teams) << "\n";
}
```



```cpp
#include <iostream>
#include <vector>

int main() {
    using namespace std;
    unsigned N, T, M;
    cin >> N >> T >> M;

    // j-th bit of hate[i] is 1 ⟹ i-th and j-th players are incompatible (0-indexed)
    vector<unsigned> hate(N);
    for (unsigned i{}, a, b; i < M; ++i) {
        cin >> a >> b;
        hate[--b] |= 1U << --a;
    }

    // Print the result of the recursive function
    cout << [dfs{ [N, T, &hate](auto&& f, vector<unsigned>& teams, unsigned now) -> unsigned {
        // OK if there are T teams so far when all the N players are inspected
        if (now == N)
        return size(teams) == T;

        unsigned ans{};

        // Add the now-th player to an existing team
        for (auto&& team : teams)
            // If nobody in the team is incompatible with the now-th
            if (!(team & hate[now])) {
                team ^= 1U << now;
                ans += f(f, teams, now + 1);
                team ^= 1U << now;
            }

        // If new team can be made, make a new one
        if (size(teams) < T) {
            teams.emplace_back(1U << now);
            ans += f(f, teams, now + 1);
            teams.pop_back();
        }

        return ans;
    } }, T] {
        vector<unsigned> team;
        team.reserve(T);
        return dfs(dfs, team, 0);
    }() << endl;

    return 0;
}
```





