# C/C++ in lang-study

## 简介
用来学习 C/C++ 的仓库

## 规范 & 要求
1. Makefile 的 command 必须以 **TAB** 开头  

2. 编译命令一般将参数写在前面，重命名和操作的文件写在后面  

3. C++ 源文件的扩展名统一命名为 `.cc`  


## File structure
- [dependencies](dependencies)  
	存放额外的依赖文件  

- [header](header)  
	存放头文件  

- [~~out~~](out)  
	存放输出文件，被 Git 忽略  

- [resource](resource)  
	存放资源文件以及文档和备份  
	- [backups](resource/backups)  
	- [docs](resource/docs)  
		存放文档，包括日志和任务  

- [source](source)  
	存放源文件  

- [~~tmp~~](tmp)  
	存放临时文件,包括对象文件，被 Git 忽略  

- [_clang-format](_clang-format)  
	用于 VS Code 的 C/C++ 代码格式文件  

- [.gitignore](.gitignore)  
	作为主忽略文件的补充  

- Makefile  
	Used to manage and compile this project