echo `date '+%Y-%m-%d %T'` >> /tmp/clean.log

# 用 * 作为搜索路径可以忽略隐藏文件
# 需要为 find 指定 -regextype 为 gnu-awk 才支持括号匹配
# find 的正则匹配的是文件的相对路径，所以要在最前面加 .*
find * -type d -name '__pycache__' -exec echo {}/ >> /tmp/clean.log \; -exec rm -rf {} \;
find * -regextype gnu-awk -regex '.*\.(tmp|exe|out|txt|class|in)' -exec echo {} >> /tmp/clean.log \; -delete
echo >> /tmp/clean.log
cat /tmp/clean.log && rm /tmp/clean.log
