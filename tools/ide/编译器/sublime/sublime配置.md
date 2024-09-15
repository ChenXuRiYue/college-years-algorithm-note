1. 下载好c++的编译器之后， mingw64配置环境变量
2. 新建一个c++的编译系统内容如下：

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
			"cmd": ["cmd","/C","g++", "-Wall", "${file}","-std=c++17", "-fexec-charset=gbk", "-o","${file_path}/${file_base_name}"],
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

ctr + b就能运行了
