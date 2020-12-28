from requests import get
from bs4 import BeautifulSoup as BS

cnt = 1
def printInfo(names, scores, k):
    cnt = k * 25 + 1
    size = len(names)
    for i in range(size):
        print(cnt, end=': ')
        cnt += 1
        print(names[i].a.span.text, scores[i].text, end='分\n')
        

host = 'https://movie.douban.com/top250'
start = '?start='
end = '&filter='
headers = {'user-agent': 'my-app/0.0.1'}
res = get(host, headers=headers)
soup = BS(res.text, 'html.parser')
targets = soup.find_all('div', class_='hd')
scores = soup.find_all('span', class_='rating_num')
size = len(targets)
for i in range(size):
    print(cnt, end=': ')
    cnt += 1
    print(targets[i].a.span.text, scores[i].text, end='分\n')

for i in range(1, 10):
    res = get(host + start + str(i * 25) + end, headers=headers)
    soup = BS(res.text, 'html.parser')
    targets = soup.find_all('div', class_='hd')
    scores = soup.find_all('span', class_='rating_num')
    printInfo(targets, scores, i)
