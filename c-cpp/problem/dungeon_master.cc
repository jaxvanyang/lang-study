#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int nex[6][3] = {{0, 0, 1},  {0, 1, 0},  {1, 0, 0},
                 {-1, 0, 0}, {0, -1, 0}, {0, 0, -1}};

vector<int> from(int x, int y, int z) {
  vector<int> tmp;
  tmp.push_back(x);
  tmp.push_back(y);
  tmp.push_back(z);
  return tmp;
}

int bfs(vector<vector<vector<char>>> &mp, queue<vector<int>> &curs,
        vector<int> &e) {
  int n = curs.size();
  if (n == 0) {
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    vector<int> cur = curs.front();
    curs.pop();
    if (cur[0] == e[0] && cur[1] == e[1] && cur[2] == e[2]) {
      return 0;
    }
    for (int j = 0; j < 6; ++j) {
      int x_ = cur[0] + nex[j][0];
      int y_ = cur[1] + nex[j][1];
      int z_ = cur[2] + nex[j][2];
      if (x_ < 0 || x_ >= mp.size() || y_ < 0 || y_ >= mp[0].size() || z_ < 0 ||
          z_ >= mp[0][0].size()) {
        continue;
      }
      if (mp[x_][y_][z_] == '.' || mp[x_][y_][z_] == 'E') {
        curs.push(from(x_, y_, z_));
        mp[x_][y_][z_] = 'x';
      }
    }
  }
  return 1 + bfs(mp, curs, e);
}

int main() {
  int l, r, c;
  while (true) {
    scanf("%d%d%d", &l, &r, &c);
    getchar();
    if (l + r + c == 0) {
      return 0;
    }

    vector<vector<vector<char>>> mp(l,
                                    vector<vector<char>>(r, vector<char>(c)));
    int x1, y1, z1, x2, y2, z2;
    for (int x = 0; x < l; ++x) {
      for (int y = 0; y < r; ++y) {
        for (int z = 0; z < c; ++z) {
          char ch;
          scanf("%c", &ch);
          // cout << "ch = " << ch << endl;
          mp[x][y][z] = ch;
          if (ch == 'S') {
            x1 = x;
            y1 = y;
            z1 = z;
          } else if (ch == 'E') {
            x2 = x;
            y2 = y;
            z2 = z;
          }
        }
        getchar();
      }
      getchar();
    }

    queue<vector<int>> curs;
    curs.push(from(x1, y1, z1));
    vector<int> e = from(x2, y2, z2);
    int ans = bfs(mp, curs, e);
    if (mp[x2][y2][z2] == 'x') {
      printf("Escaped in %d minute(s).\n", ans);
    } else {
      printf("Trapped!\n");
    }
  }
}