echo `date '+%Y-%m-%d %T'` >> clean.log

# 用 * 作为搜索路径可以忽略隐藏文件
# 需要为 find 指定 -regextype 为 gnu-awk 才支持括号匹配
# find 的正则匹配的是文件的相对路径，所以要在最前面加 .*
find * -type d -name '__pycache__' -exec echo {}/ >> clean.log \; -exec rm -rf {} \; 
find * -regextype gnu-awk -regex '.*\.(tmp|exe|txt|class)' -exec echo {} >> clean.log \; -delete
echo >> clean.log
cat clean.log && rm clean.log