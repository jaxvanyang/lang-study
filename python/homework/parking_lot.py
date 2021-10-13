# 201908130416 杨凯

import random
import time

def print_msg(s: str) -> None:
    k = 50
    t = '=' * k

    print(t)
    print(s.center(50))
    print(t)

SECONDS_PER_HOUR = 3600
def calc_hour(x: float) -> float:
    return round(x / SECONDS_PER_HOUR, 1)

print_msg('欢迎来到停车场')



MAX_CAR = 5
pos_list = [f'{i}#' for i in range(1, MAX_CAR + 1)]
car_list = []
cur_car = 0

while True:
    choice = input('''
    请选择功能：
    1. 停车
    2. 出停车场
    3. 查询车辆
    4. 查询所有车辆
    5. 退出系统
    ''')

    if choice == '1':

        if cur_car < MAX_CAR:
            print_msg('停车')

            car_no = input('输入车牌号：')
            start = time.time()
            pos = random.choice(pos_list)
            car_msg = (car_no, start, pos)

            car_list.append(car_msg)
            pos_list.remove(pos)
            cur_car += 1

            print_msg(f'{car_no} 停在 {pos} 位置上，进场时间为：{time.ctime(start)}')

        else:
            print_msg('车位已停满')

    elif choice == '2':
        print_msg('出停车场')

        car_no = input('输入车牌号：')
        end = time.time()
        
        for car_msg in car_list:
            if car_no in car_msg:
                t = calc_hour(end - car_msg[1])
                fee = int(t) * 5

                print_msg(f'停车时间是 {t} 小时，费用是 {fee} 元')
                time.sleep(2)
                print_msg('支付成功')

                pos_list.append(car_msg[2])
                cur_car -= 1
                car_list.remove(car_msg)
                break

        else:
            print_msg('停车场没有该车牌的信息，请联系管理员')

    elif choice == '3':
        print_msg('查询车辆')

        car_no = input('输入车牌号：')

        for car_msg in car_list:
            if car_no == car_msg[0]:
                print_msg(f'查询到车辆 {car_no} 停在车位 {car_msg[2]}')
                break
        
        else:
            print_msg(f'未在停车场内找到车牌号为 {car_no} 的车辆')

    elif choice == '4':
        print_msg('查询所有车辆')
        end = time.time()

        for car_no, start, pos in car_list:
            print(f'{car_no:<10}  已经停在 {pos:<5} {calc_hour(end - start):<5} 小时了')

    elif choice == '5':
        print_msg('退出系统')

        confirm = input('你确定要退出系统吗（y/n）？')

        if confirm.lower() == 'y':
            print_msg('系统关闭中……')
            time.sleep(1)
            break

    else:
        print_msg('输入错误，请重新输入')

print_msg('已退出系统')