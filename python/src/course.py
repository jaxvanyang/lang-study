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


def translate_course(course: dict):
    ret = {}
    for key in course.keys():
        ret[translation[key]] = course[key]
    return ret


def main():
    course = new_course('2019-2020-1', '高等数学', 6, '必修', '公共课', 2.7)
    print(course)
    translated_course = translate_course(course)
    print(translated_course)


if __name__ == '__main__':
    main()
