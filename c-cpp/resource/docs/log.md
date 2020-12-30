# 日志

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