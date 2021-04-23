## Structure
- [algorithm](algorithm)  
    My algotithm package  

- [crawler](crawler)  
    Some crawler  

- [file](file)  
    File operation package  

## 日志
- 2020/12/28 将 `/python/file/` 设置为包  
    但是 `VS Code` 无法识别  
    修复：需要相对于 `VS Code` 打开的工作目录进行导入，也可以通过 `settings.json` 来设置 `python.analysis.extraPaths` 解决