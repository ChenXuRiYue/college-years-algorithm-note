sublime配置环境

前话：曾经几次的配置过程实在痛苦。一款编辑器可以使用各种各样的功能。但是我并不知道有何种功能可以实现以及其原理。

学会使用一款软件，并且是程序员使用的一款软件，都要进一步的接触应用层次。其配置逻辑。

#### 参考

https://www.luogu.com.cn/blog/195331/Sublime-User-Guide



#### 下载编辑器

就是找到了一个。已经把他放在文件夹下了。

网上有一些资源是一件安装的。而另外也有一些资源是，



#### 关于配置c++环境。

- 怎么配置c++17更加先进的标准库？

大多都可以用，没必要，有替代品了。这个不是必选项。

- 关于报错,调试的可有可无。毕竟得习惯这种白板写程序的模式。（放屁，有工具为什么不用。）

##### 初始尝试：

配置环境变量。这个工作早在配置vscode的时候就已经完成了。

然后就是写一些配置文件。

tool -> 构建新的编译系统。、

```json
{
	"cmd": ["g++", "-Wall", "${file}","-std=c++11", "-fexec-charset=gbk", "-o","${file_path}/${file_base_name}"],
	"file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:?(.*)$",
	"working_dir": "${file_path}",
	"selector": "source.c, source.c++",
	"shell": true,
	"encoding":"cp936",
	"variants":
	[
		{
			"name": "Compile Only",
			"cmd": ["cmd","/C","g++", "-Wall", "${file}","-std=c++11", "-fexec-charset=gbk", "-o","${file_path}/${file_base_name}"],
		},
		{
			"name": "Run Only",
			"cmd": ["start","cmd","/c", "${file_base_name} & echo. & pause"],
		},
		{
			"name": "Compile & Run",
			"cmd": ["cmd","/C","g++", "-Wall", "${file}","-std=c++11", "-fexec-charset=gbk", "-o","${file_path}/${file_base_name}", "&&","start","cmd","/c", "${file_base_name} & echo. & pause"],
		}
	]
}

```

然后就来到这一个步骤了。

现在的缺陷是无法逐语句调试，只有编译的时候才报错。然后缩进方面不够方便。

--------

关于上述可以对于默认的c++运行编译环境可以调一下。后面 ， 为了方便， 调成了c++17(运行和编译都调成了c++17)同时注意一点

-------

、

#### 使用优化

逆天，这款软件可以自动下载插件并且进行安装。果然是非常现代化的编译器。

但是这一些插件又如何使用呢？点击插件设计也是有相关的功能设置的。可以通过对这个文件的修改从而完成一个



##### 插件优化。

##### 1. 缩进方式

下载一些相关的插件即可。

通过packeage control-》搜索名字一键安装。

##### 2.方便输入输出的插件。

插件： fastoi

直接下载搜索安装

然后编译的时候使用ctrl alt b即可。

具体使用细节如下：这个插件有什么优势？

##### 3.默认代码模板的使用。

工具开发，新建代码模板即可。

如下所示为单文件的代码模板。

```txt
<snippet>
	<content><![CDATA[
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = (int)2e5 + 10;


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;${1:}

}


]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>single_test</tabTrigger> -->
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<!-- <scope>source.python</scope> -->
</snippet>

```



总的来说和vscode的原理差不多。





##### 4.设置换行首缩进4个字符。

明明在几个文件下设置tap都设置了4个字符。但是这里就是2个空格。

后面还是用重新配置一遍的方法解决了。

这个有空再解决。



#####  5.tap,和enter键问题

有时候tab键不可以选择补全项。而enter也是如此。



##### 6.方便文件管理

side bar 直接安装即可



##### 7.优化图标

a file icon



配置了好几个小时。但是也不算什么大问题了。总归向前走了。

