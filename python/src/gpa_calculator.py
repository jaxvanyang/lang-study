from io import TextIOWrapper
from course import *
from getpass import getpass
import json
from time import sleep
from selenium.webdriver import Edge

# 可选的浏览器驱动
# from selenium.webdriver import Chrome

flag = False


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
    # 根据本地安装的浏览器选择驱动
    driver = Edge(executable_path='./drivers/msedgedriver.exe')
    # driver = Chrome()


    # 使用 driver 访问网址并登录
    driver.get(url)
    driver.find_element_by_id('userAccount').send_keys(account)
    driver.find_element_by_id('userPassword').send_keys(password)
    driver.find_element_by_xpath('//*[@id="ul1"]/li[5]/button').click()
    sleep(1)

    # 切换到课程成绩信息页面
    driver.switch_to.frame('Frame0')
    driver.find_element_by_xpath(
        '/html/body/div[2]/div[2]/div[1]/div[2]/div/div/div[2]').click()
    sleep(1)

    # 查询课程成绩
    driver.switch_to.default_content()
    driver.switch_to.frame('Frame1')
    driver.switch_to.frame('cjcx_query_frm')
    driver.find_element_by_xpath('//*[@id="btn_query"]').click()
    sleep(1)

    # 导航到数据页面
    driver.switch_to.parent_frame()
    driver.switch_to.frame('cjcx_list_frm')

    def get_item(row: int, col: int):
        return driver.find_element_by_xpath(f'{table}/tr[{row}]/td[{col}]').text

    driver.minimize_window()
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
        if course['grade'] == '0':
            flag = True
            continue
        courses.append(course)

    # 使用 Edge时，退出会产生编码错误，尚不清楚原因
    try:
        driver.quit()
    except:
        pass

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
        if (not contains_elective) and course['course_attr'] == '公选':
            course_amount -= 1
            continue
        total_credits += course['credit']
        total_grades += course['credit'] * course['grade']

        # 注意平均成绩不用加权学分计算
        total_scores += course['score']
    return {
        'course_amount': course_amount,
        'total_credits': total_credits,
        'gpa': total_grades / total_credits,
        'score_average': total_scores / course_amount,
        # 'contains_elective': contains_elective,
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


def print_courses_statistics(courses_statistics: dict, sorted_key: list):
    """ 
    输出统计数据
    """
    # for condition in sorted_key:
    #     print(f'查询学期或学年：{condition}')
    #     for key in courses_statistics[condition]:
    #         val = courses_statistics[condition][key]
    #         print(f'{translation[key]}：{val}；')
    #     print('\n')
    print('查询学期或学年  所修门数        所修总学分      平均学分绩点    平均成绩')
    for condition in sorted_key:
        data = courses_statistics[condition]
        print('%-16s%-16d%-16.1f%-16f%-16f' % (
            condition,
            data['course_amount'],
            data['total_credits'],
            data['gpa'],
            data['score_average']
        ))
        print()


def save_courses_statistics(courses_statistics: dict, sorted_key: list, f: TextIOWrapper):
    f.write('查询学期或学年  所修门数        所修总学分      平均学分绩点    平均成绩\n')
    for condition in sorted_key:
        data = courses_statistics[condition]
        f.write('%-16s%-16d%-16.1f%-16f%-16f\n' % (
            condition,
            data['course_amount'],
            data['total_credits'],
            data['gpa'],
            data['score_average']
        ))
        f.write('\n')


def save_courses(courses: dict, file: str = 'courses.json'):
    # 注意编码问题
    f = open(file, 'w', encoding='utf-8')
    json.dump(courses, f, ensure_ascii=False)


def main(courses: list):
    courses_statistics = analysis_courses(courses)
    courses_statistics_no_elective = analysis_courses(courses, False)
    sorted_key = sorted(courses_statistics.keys())

    print('包括公共选修课的计算结果：')
    print_courses_statistics(courses_statistics, sorted_key)
    print()

    print('不包括公共选修课的计算结果')
    print_courses_statistics(courses_statistics_no_elective, sorted_key)

    # 保存序列化的课程成绩信息
    save_courses(courses)

    # 保存成绩统计结果
    f = open('data.txt', 'w', encoding='utf-8')
    save_courses_statistics(courses_statistics, sorted_key, f)
    save_courses_statistics(courses_statistics_no_elective, sorted_key, f)
    if flag:
        f.write('已去除挂科课程')
    f.close()


def msg():
    print('\033[1;41;0m！！！！！！！！！！！使用须知：\033[0m')
    print()
    print('使用前请确认安装了最新版本的 Edge')
    print('不清楚自己 Edge 浏览器版本号的同学可以在 Edge 地址栏输入以下地址查看：\nedge://settings/help')
    print()
    print('脚本会自动打开浏览器查询，完成后自动关闭浏览器')
    print('查询会花费一定时间，请不要提前关闭浏览器')
    print()


if __name__ == '__main__':
    msg()
    account = input('请输入帐号（输入一行后按“Enter”确认）：')
    password = getpass('请输入密码（为了防止密码泄露，输入的密码是隐藏的，输完后按“Enter”确认即可）：')

    try:
        main(get_courses(account, password))
    except:
        print('获取网页信息异常！可能是账密有误，或者网络连接异常，请稍后再试。')

    if flag:
        print('已去除挂科课程')


    print('你也可以通过生成在当前目录下的“data.txt”查看计算结果')
    input('按“Enter”关闭窗口：')
