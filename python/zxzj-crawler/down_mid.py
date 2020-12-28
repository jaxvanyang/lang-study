from requests import get
from bs4 import BeautifulSoup as BS
from json import dumps, loads

url = 'https://www.zxzj.me/video/485-1-1.html'

headers = {'user-agent': 'my-app/0.0.1'}

res = get(url, headers=headers)
text = res.text
link = 'https://bnj189cloud.oos-js.ctyunapi.cn/1b61515c-3253-4c80-afe0-08d7520d57cd?response-content-disposition=attachment%3Bfilename%3D%22%C3%A6%C2%B7%C2%B1%C3%A5%C2%A4%C2%9C%C3%A9%C2%A3%C2%9F%C3%A5%C2%A0%C2%82S01E01.mp4%22&x-amz-CLIENTNETWORK=UNKNOWN&x-amz-CLOUDTYPEIN=CORP&x-amz-CLIENTTYPEIN=UNKNOWN&Signature=K94qXgwdDm3VY90BDYcncetns0c%3D&AWSAccessKeyId=ad2d051c334eb8bbf4c1&Expires=1609052629&x-amz-limitrate=102400&response-content-type=video/mp4&x-amz-FSIZE=498940465&x-amz-UID=183558589591430&x-amz-UFID=41443311230305200'

soup = BS(text, 'html.parser')
target = soup.find('div', class_='stui-player__video clearfix')
target_text = str(target)
begin = target_text.index('{')
end = target_text.index('}')
target_json = target_text[begin:end+1]
target_dict = loads(target_json)
print(target_dict['url'])

file_loc = 'res.html'
file = open(file_loc, 'w')
file.write(text)
