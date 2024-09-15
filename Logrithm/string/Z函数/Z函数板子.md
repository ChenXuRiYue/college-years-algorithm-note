# Z函数

[题解 P5410 【【模板】扩展 KMP（Z 函数）】 - George1123 - 洛谷博客 (luogu.com.cn)](https://www.luogu.com.cn/blog/George1123/solution-p5410)

[Z 函数（扩展 KMP） - OI Wiki (oi-wiki.org)](https://oi-wiki.org/string/z-func/)

关键的思想和manacher相似， 使用已经计算出的成果，关注对称，交等特征。

会板就行：

****

$\Large moban$

```cpp
vector<int> Z(string s) {
	int n = (int)s.size();
	vector<int> z(n);
	for (int i = 1, l = 0 , r = 0; i < n; ++i) {
		if (i <= r && z[i - l] < r - i + 1) {
			z[i] = z[i - l];
		} else {
			z[i] = max(0 , r - i + 1);
			while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
		}
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	z[0] = n;
	return z;
}

vector<int> Z(string s , string parten) {
	int n = (int)s.size();
	auto zz = Z(parten + '$' + s);
	vector<int> z(n);
	for (int i = 0 , id = (int)zz.size() - n; i < n; i++ , id++) {
		z[i] = zz[id];
	}
	return z;
}
//返回，s各个位置和parten的最小前缀匹配长度  
```

