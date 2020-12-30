# C/C++ in lang-study

## 简介
用来学习 C/C++ 的仓库

## 规范 & 要求
1. Makefile 的 command 必须以 **TAB** 开头  

2. 编译命令一般将参数写在前面，重命名和操作的文件写在后面  

3. C++ 源文件的扩展名统一命名为 `.cc`  


## File structure
- [dependencies](dependencies)  
	Used to store external dependencies  

- [header](header)  
	Used to store header file  

- [source](source)  
	Used to store source file  

- [tmp](tmp)  
	Used to store temporary file include object file  

- Makefile  
	Used to manage and compile this project

## Make options
A breif introduction of what we can make from this project.  

1. `make linear`  
	You can use this to built a CTI to calculate some linear algebra.  

## 日志
- Makefile 可使用 `VPATH` 添加文件的搜索路径，路径之间用冒号分隔 `:`  

- gcc 不能指定源文件和对象文件的搜索路径  

- gcc 可以使用 `-o` 参数指定路径  

- 自己编写命令后，make 貌似就不能自动推断“.o”文件的依赖文件了  

- Makefile 使用变量名替换时等号左右不能加空格  

- 暂时将输出文件都放在 `c-cpp` 目录下，避免编译命令写得太复杂  

- 修改 Code Runner 配置文件，使之生成带后缀名的输出文件  
	```json
    "cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt.out && $dir$fileNameWithoutExt.out",
	```

- C/C++ 文件名一般是 `my_source_file.cc` 类型,但让 `24_points` 成为例外无伤大雅  

- 不再逐一修改编译输出文件的名字,考虑编写函数完成重命名  

## 计划
- [ ] 尝试删除 `my_main.cc` 里引入的源文件  