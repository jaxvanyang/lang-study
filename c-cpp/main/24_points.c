#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Macro */
#define maxn 25

/* Const */
const char VERSION[] = "0.1";
const char WELCOME[] =
    "欢迎游玩 24 点！\n版本：0.1\n输入‘Y’开始游戏，输入‘N’结束游戏。\n";
const char ERROR_INPUT[] = "输入错误，请重新输入。\n";
const double TARGET = 24.0;
const double EPS = 1e-6;

/* Global */
char input[maxn];

int solve(double *list, int len);

int main() {
  srand((unsigned int)time(NULL));
  // printf("%d\n", rand());

  // double list[4] = {1, 1, 1, 1};
  // printf("%d\n", solve(list, 4));
  // return 0;

  printf("%s", WELCOME);
  while (1) {
    scanf("%s", input);
    if (strcmp(input, "N") == 0 || strcmp(input, "n") == 0)
      break;
    else if (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0) {
      // printf("Hello!\n");
      int nums[4];
      for (int i = 0; i < 4; i++) nums[i] = rand() % 9 + 1;

      printf(
          "你需要计算的数字分别是：%d，%d，%d，%d。\n请输入是否能计算出 24 "
          "点（Y/N）。\n",
          nums[0], nums[1], nums[2], nums[3]);
      scanf("%s", input);
      double list[4];
      int len = 4;
      for (int i = 0; i < 4; i++) {
        list[i] = nums[i];
      }
      int flag = solve(list, len);
      if (flag && (input[0] == 'Y' || input[0] == 'y')) {
        printf("恭喜你，答对了！\n");
      } else {
        printf("很遗憾，你答错了。\n");
      }
      printf("正确答案是：");
      if (flag)
        printf("可以。\n");
      else
        printf("不可以。\n");

      printf("是否继续游戏？输入‘Y’继续，输入‘N’结束游戏。\n");
    } else {
      printf("%s", ERROR_INPUT);
    }
  }
}

int solve(double *list, int len) {
  if (len == 0) return 0;
  if (len == 1) return fabs(list[0] - TARGET) < EPS;

  for (int i = 0; i < len; i++)
    for (int j = 0; j < len; j++) {
      if (i == j) continue;

      double list_2[4];
      int len_2 = 0;
      for (int k = 0; k < len; k++) {
        if (k != i && k != j) list_2[len_2++] = list[k];
      }

      for (int k = 0; k < 4; k++) {
        if (k < 2 && i < j) continue;
        if (k == 0) {
          list_2[len_2++] = list[i] + list[j];
        } else if (k == 1)
          list_2[len_2++] = list[i] * list[j];
        else if (k == 2)
          list_2[len_2++] = list[i] - list[j];
        else if (k == 3) {
          if (fabs(list[j]) < EPS) continue;
          list_2[len_2++] = list[i] / list[j];
        }
        if (solve(list_2, len_2)) return 1;
        len_2--;
      }
    }

  return 0;
}