# use * to ignore hidden files
find * -type d -name '__pycache__' -exec rm -rf {} \;
find * -type f -name '*.tmp' -exec rm {} \;
find * -type f -name '*.exe' -exec rm {} \;
find * -type f -name '*.txt' -exec rm {} \;
find * -type f -name '*.out' -exec rm {} \;
