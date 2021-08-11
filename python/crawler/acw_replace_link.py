# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
from bs4 import BeautifulSoup as BS
import requests
from time import sleep
import time
from getpass import getpass


# %%
domain = "https://www.acwing.com"

# get this from input
activity_url = input('请输入要替换原题链接的 AcWing 活动页面（输入为空则默认为算法竞赛进阶指南》活动）：')
if activity_url == '':
    activity_url = 'https://www.acwing.com/activity/content/punch_the_clock/6/'


# %%
login_url = 'https://www.acwing.com/user/account/signin/'

# access the main page to get csrftoken
session = requests.Session()
session.get(domain)
csrftoken = session.cookies['csrftoken']

# get login username & password
print('请输入 AcWing 的登录信息，输入密码不显示是正常的')
username = input('用户名或邮箱：')
password = getpass('密码（输完后按回车）：')

# set login form
login_headers = {
    'Connection': 'keep-alive',
    'sec-ch-ua': '"Microsoft Edge";v="93", " Not;A Brand";v="99", "Chromium";v="93"',
    'DNT': '1',
    'sec-ch-ua-mobile': '?0',
    'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.25 Safari/537.36 Edg/93.0.961.18',
    'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',
    'Accept': 'application/json, text/javascript, */*; q=0.01',
    'X-Requested-With': 'XMLHttpRequest',
    'X-CSRFToken': 'r2si6L74DMG5QfYhs2lqYsW7TlIVIPCJsj8mTXXUAcNpVUkILw5Hwferk9lpL5Ly',
    'sec-ch-ua-platform': '"Linux"',
    'Origin': 'https://www.acwing.com',
    'Sec-Fetch-Site': 'same-origin',
    'Sec-Fetch-Mode': 'cors',
    'Sec-Fetch-Dest': 'empty',
    'Referer': domain,
    'Accept-Language': 'en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7',
}
login_data = {
  'csrfmiddlewaretoken': csrftoken,
  'username': username,
  'password': password,
  'remember_me': 'on'
}

# login in ACWing
session.post(login_url, headers=login_headers, data=login_data)


# %%
# normal page form data
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
    'Referer': activity_url,
    'Accept-Language': 'en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7',
}

response = session.get(activity_url, headers=headers)
activity_page = session.get(activity_url, headers=headers).text


# %%
activity_soup = BS(activity_page, 'lxml')

problems = activity_soup.find_all('a', class_='clock-problem-title')
cnt = len(problems)
print(f'total problem count: {cnt}')
print(f'it may finish in {cnt // 120} mins')


# %%
start_time = time.time()

for i in range(cnt):
    problem = problems[i]
    print(f'# {i + 1}/{cnt}: {problem.span.text}')

    href = problem.attrs['href']
    page = session.get(f'{domain}{href}', headers=headers)

    problem_soup = BS(page.text, 'lxml')
    target = problem_soup.find('a', class_='label label-info')
    
    original_link = target.attrs['href']
    print(f'will replace {problem.attrs["href"]} with {original_link}')

    activity_page = activity_page.replace(problem.attrs['href'], original_link)

    # optional
    # sleep(1)

end_time = time.time()
print(f'scrape time: {end_time - start_time} s')

with open('source.html', 'w') as f:
    f.write(activity_page)
    print('successed, check source.html in current folder')


