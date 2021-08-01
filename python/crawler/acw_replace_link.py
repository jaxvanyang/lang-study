from bs4 import BeautifulSoup as BS
import requests
from time import sleep

domain = "https://www.acwing.com"
url = 'https://www.acwing.com/activity/content/punch_the_clock/6/'
headers = {
    'Connection': 'keep-alive',
    'sec-ch-ua': '"Chromium";v="92", " Not A;Brand";v="99", "Microsoft Edge";v="92"',
    'sec-ch-ua-mobile': '?0',
    'Upgrade-Insecure-Requests': '1',
    'DNT': '1',
    'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.107 Safari/537.36 Edg/92.0.902.62',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
    'Sec-Fetch-Site': 'same-origin',
    'Sec-Fetch-Mode': 'navigate',
    'Sec-Fetch-User': '?1',
    'Sec-Fetch-Dest': 'document',
    'Referer': 'https://www.acwing.com/activity/content/punch_the_clock/6/',
    'Accept-Language': 'en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7',
    'Cookie': 'file_2875_readed=""; file_4838_readed=""; csrftoken=EfzcZAwbFzJHjk2ryKSlARMHBW94cT0Q4zmCAj8VZdCfp2hvJMRuyvGMgZ5sPmrN; sessionid=kn3dcvobf1pomjvdo3rpor9sfhkxkme9; file_538183_readed=""; file_777_readed=""'}


session = requests.Session()
main_page = session.get(url, headers=headers)
source = main_page.text
soup = BS(source, 'lxml')

problems = soup.find_all('a', class_='clock-problem-title')
print(len(problems))

i = 1
for each in problems:
    print(f'#{i}: {each.span.text}')
    # print('https://www.acwing.com' + each.attrs['href'])
    href = each.attrs['href']
    page = requests.get(f'{domain}{href}', headers=headers)
    each_soup = BS(page.text, 'lxml')
    target = each_soup.find('a', class_='label label-info')
    # print(target)
    original_link = target.attrs['href']
    print(f'will replace {each.attrs["href"]} with {original_link}')
    # print(source.find(each.attrs['href']))
    source = source.replace(each.attrs['href'], original_link)
    i += 1
    sleep(1)


with open('source.html', 'w') as f:
    f.write(source)
