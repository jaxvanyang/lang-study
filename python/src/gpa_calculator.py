from course import *
import os
import sys
import json
import time
from selenium import webdriver
from selenium.webdriver.chrome.webdriver import WebDriver


def get_courses(account: str, password: str):
    """ 
    从网络上爬取课程成绩信息
    :return: <dict> 记录了课程成绩信息的字典
    """
    div = '/html/body/div'  # 课程成绩信息分区的 xpath
    table = '//*[@id="dataList"]/tbody'  # 课程成绩信息表格的 xpath
    url = 'http://xk.csust.edu.cn/'  # 教学一体化服务平台网址

    """ 
    获取一个到达课程成绩信息位置的 driver
    """
    # 根据本地安装的浏览器选择 driver
    driver = webdriver.Chrome()

    # 使用 driver 访问网址并登录
    driver.get(url)
    driver.find_element_by_id('userAccount').send_keys(account)
    driver.find_element_by_id('userPassword').send_keys(password)
    driver.find_element_by_xpath('//*[@id="ul1"]/li[5]/button').click()
    time.sleep(1)

    # 切换到课程成绩信息页面
    driver.switch_to.frame('Frame0')
    driver.find_element_by_xpath(
        '/html/body/div[2]/div[2]/div[1]/div[2]/div/div/div[2]').click()
    time.sleep(1)

    # 查询课程成绩
    driver.switch_to.default_content()
    driver.switch_to.frame('Frame1')
    driver.switch_to.frame('cjcx_query_frm')
    driver.find_element_by_xpath('//*[@id="btn_query"]').click()
    time.sleep(1)

    # 导航到数据页面
    driver.switch_to.parent_frame()
    driver.switch_to.frame('cjcx_list_frm')

    def get_item(row: int, col: int):
        return driver.find_element_by_xpath(f'{table}/tr[{row}]/td[{col}]').text

    # TODO：使用课程成绩分区的信息判断计算是否正确
    div_text = driver.find_element_by_xpath(div).text
    div_list = div_text.splitlines()
    div_size = len(div_list)

    # 提取课程成绩信息
    print('请稍等片刻，爬取信息需要时间')
    courses = []
    for row in range(2, div_size):
        course = new_course(
            [get_item(row, col) for col in range(1, 18)]
        )
        courses.append(course)
    driver.quit()

    return courses


def parse_courses_txt(file: str = 'courses-info.txt'):
    '''
    解析 txt 形式的课程信息
    '''
    raw_courses = []
    f = open(file, 'r', encoding='utf-8')
    line = f.readline()
    while line:
        raw_courses.append(line.split())
        line = f.readline()
    f.close()

    # delete group_name for simplify following opration
    for course in raw_courses:
        if not course[4].isdigit():
            course.remove(course[4])

    courses = []
    for course in raw_courses:
        courses.append(new_course(
            no=int(course[0]),
            term=course[1],
            id=course[2],
            name=course[3],
            score=float(course[4]),
            study_type=course[5],
            credit=float(course[6]),
            total_class_hour=int(course[7]),
            grade=float(course[8]),
            exam_type=course[9],
            exam_property=course[10],
            course_attr=course[11],
            course_property=course[12]
        ))

    return courses


def calculate_gpa(courses: list, contains_elective: bool = True):
    total_credits = 0
    total_grades = 0
    total_scores = 0
    course_amount = len(courses)
    for course in courses:
        total_credits += course['credit']
        total_grades += course['credit'] * course['grade']

        # 注意平均成绩不用加权学分计算
        total_scores += course['score']
    return {
        'course_amount': course_amount,
        'total_credits': total_credits,
        'gpa': total_grades / total_credits,
        'score_average': total_scores / course_amount,
        'contains_elective': contains_elective,
    }


def analysis_courses(courses: list, contains_elective: bool = True):
    courses_statistics = {'all': calculate_gpa(courses, contains_elective)}

    term_set = set()
    for course in courses:
        term_set.add(course['term'])
    # 推导为字典需要使用大括号
    term_dict = {term: [] for term in term_set}
    for course in courses:
        term_dict[course['term']].append(course)

    # 注意此处的 year 表示学年
    year_set = set()
    for term in term_dict:
        begin, end, _ = term.split('-')
        year_set.add(f'{begin}-{end}')
    year_dict = {year: [] for year in year_set}
    for course in courses:
        begin, end, _ = course['term'].split('-')
        year_dict[f'{begin}-{end}'].append(course)

    for term in term_dict:
        courses_statistics[term] = calculate_gpa(
            term_dict[term], contains_elective)
    for year in year_dict:
        courses_statistics[year] = calculate_gpa(
            year_dict[year], contains_elective)

    return courses_statistics


def print_courses_statistics(courses_statistics: dict):
    sorted_key = sorted(courses_statistics.keys())
    for condition in sorted_key:
        print(f'查询学期或学年：{condition}')
        for key in courses_statistics[condition]:
            val = courses_statistics[condition][key]
            print(f'{translation[key]}：{val}；')
        print('\n')


def save_courses(courses: dict, file: str = 'courses.json'):
    # 注意编码问题
    f = open(file, 'w', encoding='utf-8')
    json.dump(courses, f, ensure_ascii=False)


def main(courses: list):
    # courses = parse_courses_txt()
    # courses = get_courses()
    # f = open('courses.json', 'r', encoding='utf-8')
    # courses = json.load(f)
    courses_statistics = analysis_courses(courses)
    courses_statistics_no_elective = analysis_courses(
        [course for course in courses if course['course_attr'] != '公选'],
        False
    )
    print_courses_statistics(courses_statistics)
    print_courses_statistics(courses_statistics_no_elective)
    save_courses(courses)


if __name__ == '__main__':
    account = input('请输入帐号：')
    password = input('请输入密码：')
    if sys.platform == 'linux':
        os.system('clear')
    else:
        os.system('cls')

    try:
        main(get_courses(account, password))
    except:
        print('获取网页信息异常！可能是账密有误，或者网络连接异常，请稍后再试。')
