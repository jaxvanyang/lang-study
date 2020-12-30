# 任务

- [ ] 尝试删除 `my_main.cc` 里引入的源文件  

- [ ] 测试完成后删除 `my_main.cc`  

- [ ] 配置 VS Code 的 C/C++ 配置文件，可参考备份文件  

- [ ] 编写测试专用 Makefile，并引入到主 Makefile  

- [ ] 编写按选项编译并自动重命名的脚本  

- [ ] 自定义 VS Code 的 C/C++ 格式化程序  

- [ ] 重写 writeInputToFile()  
    ```cpp
    source/helper.cc:92:29: warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
    92 |     return writeInputToFile("input");
    ```

- [ ] 将对象文件输出到 `c-cpp/`  

- [ ] 遵循注释规范  

## 待考
- [x] 因为对象文件路径不在主目录下，每次 `make` 都会编译所有文件，解决办法待考  
    添加 VPATH 即可解决  

- [ ] gcc 和 g++ 的区别  