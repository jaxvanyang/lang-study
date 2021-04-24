from course import *


def parse_courses_txt(file: str = 'courses-info.txt'):
    '''
    解析 txt 形式的课程信息
    '''
    raw_courses = []
    f = open(file, 'r')
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
    for condition in courses_statistics:
        print(f'条件：{condition}')
        for key in courses_statistics[condition]:
            val = courses_statistics[condition][key]
            print(f'{translation[key]}：{val}； ', end='')
        print('\n')


def main():
    courses = parse_courses_txt()
    courses_statistics = analysis_courses(courses)
    courses_statistics_no_elective = analysis_courses(
        [course for course in courses if course['course_attr'] != '公选'],
        False
    )
    print_courses_statistics(courses_statistics)
    print_courses_statistics(courses_statistics_no_elective)


if __name__ == '__main__':
    main()
