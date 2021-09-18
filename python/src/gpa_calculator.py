# 使用须知：

# 本脚本使用 Chrome 的测试驱动与 Chrome 进行交互以模拟手动访问教务平台

# 所以需要安装 Chrome 和 Chrome 的测试驱动：https://sites.google.com/chromium.org/driver/home
# 还需要将驱动的可执行文件加入环境变量 PATH

# 由于本脚本使用 selenium 控制 Chrome，所以也需要使用 pip 安装依赖包 selenium

# 如果你使用的是其他浏览器也可以安装相应的驱动，再更改本代码文件的第 25 和 165 行指定的浏览器即可

# 脚本会自动打开浏览器查询，完成后会自动关闭
# 计算过程也会花费一点时间，请耐心等待


from io import TextIOWrapper
# import traceback
from datetime import datetime
from getpass import getpass
import json
from time import sleep
from threading import Thread

# 非标准库依赖包
from selenium.webdriver import Chrome
# 可选的浏览器驱动
# from selenium.webdriver import Edge

translation = {
    'no': '序号',
    'term': '开课学期',
    'id': '课程编号',
    'name': '课程名称',
    'group_name': '分组名',
    'score': '成绩',
    'study_type': '修读方式',
    'score_id': '成绩标识',
    'credit': '学分',
    'total_study_hour': '总学时',
    'grade': '绩点',
    'restudy_term': '补重学期',
    'exam_type': '考核方式',
    'exam_property': '考试性质',
    'course_attr': '课程属性',
    'course_property': '课程性质',
    'course_type': '课程类别',
    'course_amount': '所修门数',
    'total_credits': '所修总学分',
    'gpa': '平均学分绩点',
    'score_average': '平均成绩',
    'contains_elective': '是否包括公选课',
}

col_to_key = (
    'no',
    'term',
    'id',
    'name',
    'group_name',
    'score',
    'study_type',
    'score_id',
    'credit',
    'total_study_hour',
    'grade',
    'restudy_term',
    'exam_type',
    'exam_property',
    'course_attr',
    'course_property',
    'course_type',
)


def new_course(
        term: str,
        name: str,
        credit: float,
        course_attr: str,   # 公选是不用计算的选修课
        course_property: str,
        grade: float,
        no: int = None,
        id: str = None,
        score: float = None,
        group_name: str = None,
        study_type: str = None,
        score_id: str = None,
        total_class_hour: int = None,
        restudy_term: str = None,
        exam_type: str = None,
        exam_property: str = None,
        course_type: str = None):
    """ 
    创建一个表示课程信息的字典
    """
    return {
        'no': no,
        'term': term,
        'id': id,
        'name': name,
        'group_name': group_name,
        'score': score,
        'study_type': study_type,
        'score_id': score_id,
        'credit': credit,
        'total_study_hour': total_class_hour,
        'grade': grade,
        'restudy_term': restudy_term,
        'exam_type': exam_type,
        'exam_property': exam_property,
        'course_attr': course_attr,
        'course_property': course_property,
        'course_type': course_type,
    }

def new_course(li: list):
    """ 
    创建一个表示课程信息的字典
    """
    return {
        'no': int(li[0]),
        'term': li[1],
        'id': li[2],
        'name': li[3],
        'group_name': li[4],
        'score': float(li[5]),
        'study_type': li[6],
        'score_id': li[7],
        'credit': float(li[8]),
        'total_study_hour': int(li[9]),
        'grade': float(li[10]),
        'restudy_term': li[11],
        'exam_type': li[12],
        'exam_property': li[13],
        'course_attr': li[14],
        'course_property': li[15],
        'course_type': li[16],
    }


def translate_course(course: dict):
    ret = {}
    for key in course.keys():
        ret[translation[key]] = course[key]
    return ret


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
    # 指定可执行文件的路径就不用假如环境变量 PATH 了
    # driver = Edge(executable_path='./drivers/msedgedriver.exe')
    driver = Chrome()


    # 使用 driver 访问网址并登录
    driver.get(url)
    driver.find_element_by_id('userAccount').send_keys(account)
    driver.find_element_by_id('userPassword').send_keys(password)
    driver.find_element_by_xpath('//*[@id="ul1"]/li[5]/button').click()
    sleep(3)

    # 切换到课程成绩信息页面
    driver.switch_to.frame('Frame0')
    driver.find_element_by_xpath(
        '/html/body/div[2]/div[2]/div[1]/div[2]/div/div/div[2]').click()
    sleep(3)

    # 查询课程成绩
    driver.switch_to.default_content()
    driver.switch_to.frame('Frame1')
    driver.switch_to.frame('cjcx_query_frm')
    driver.find_element_by_xpath('//*[@id="btn_query"]').click()
    sleep(3)

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

    def get_course(row: int):
        """ 
        爬取指定行的课程信息
        :return: <list> 一门课程得到信息
        """
        return new_course(
            [get_item(row, col) for col in range(1, 18)]
        )

    courses = []

    def update_courses(row: int):
        """ 
        作为线程类 Thread 的目标执行更新课程信息的任务
        """
        # print(f'开始爬取第 {row - 1} 门课程信息')
        course = get_course(row)
        if course['grade'] == 0:
            global flag
            flag = True
            return

        # TODO: 为 courses 加锁
        courses.append(course)
        # print(f'第 {row - 1} 门课程爬取已完成')

    threads = []
    print(f'Begin time:{datetime.now()}')
    for row in range(2, div_size):
        # course = new_course(
        #     [get_item(row, col) for col in range(1, 18)]
        # )
        # if course['grade'] == 0:
        #     global flag
        #     flag = True
        #     continue
        # courses.append(course)
        thread = Thread(target=update_courses, args=(row,))
        thread.start()
        threads.append(thread)

    for thread in threads:
        thread.join()

    print(f'End time:{datetime.now()}')

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
    print(
        """
        使用须知：

        本脚本使用 Chrome 的测试驱动与 Chrome 进行交互以模拟手动访问教务平台

        所以需要安装 Chrome 和 Chrome 的测试驱动：https://sites.google.com/chromium.org/driver/home
        还需要将驱动的可执行文件加入环境变量 PATH
        
        由于本脚本使用 selenium 控制 Chrome，所以也需要使用 pip 安装依赖包 selenium

        如果你使用的是其他浏览器也可以安装相应的驱动，再更改本代码文件的第 25 和 165 行指定的浏览器即可

        脚本会自动打开浏览器查询，完成后会自动关闭
        计算过程也会花费一点时间，请耐心等待
        """)


if __name__ == '__main__':
    msg()
    print('（输入一行后按“Enter”确认）')
    account = input('请输入帐号：')
    print('（为了防止密码泄露，输入的密码是隐藏的，输完后按“Enter”确认即可）')
    password = getpass('请输入密码：')

    try:
        main(get_courses(account, password))
    except:
        print('获取网页信息异常！可能是账密有误，或者网络连接异常，请稍后再试。')
        # traceback.print_exc()
        exit(1)
    

    if flag:
        print('已去除挂科课程')


    print('你也可以通过生成在当前目录下的“data.txt”查看计算结果')
    print("计算的 GPA 分为两部分，第一部分是包括公共选修课的计算结果，第二部分是去除公选课的计算结果，可以通过所修門数验证")
    print("一般来说综测是按照去除公选课的成绩计算")