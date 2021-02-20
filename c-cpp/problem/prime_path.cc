#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

class UnionFind {
 public:
  vector<int> id;
  UnionFind(int n) : id(n) {
    for (int i = 0; i < n; ++i) {
      id[i] = i;
    }
  }

  void un(int p, int q) { id[find(p)] = find(q); }

  int find(int p) {
    if (id[p] != p) {
      id[p] = find(id[p]);
    }
    return id[p];
  }

  bool isConnected(int p, int q) { return find(p) == find(q); }
};

bool table[10000];
UnionFind uf(10000);

bool isPrime(int num) {
  if (num <= 3) {
    return true;
  }
  for (int i = 2; i * i <= num; ++i) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

void updateTable() {
  for (int i = 1000; i <= 9999; ++i) {
    table[i] = isPrime(i);
    if (table[i]) {
      for (int j = 1; j <= 9; ++j) {
        int q = j * 1000 + i % 1000;
        if (table[q]) {
          uf.un(i, q);
        }
      }
      for (int j = 0; j <= 9; ++j) {
        int a = (i / 1000) * 1000 + j * 100 + i % 100;
        int b = (i / 100) * 100 + j * 10 + i % 10;
        int c = (i / 10) * 10 + j;
        if (table[a]) {
          uf.un(i, a);
        }
        if (table[b]) {
          uf.un(i, b);
        }
        if (table[c]) {
          uf.un(i, c);
        }
      }
    }
  }
}

int bfs(queue<int> &curs, int q, set<int> &st) {
  int n = curs.size();
  // cout << "n = " << n << endl;
  for (int i = 0; i < n; ++i) {
    int p = curs.front();
    // cout << p << " ";
    curs.pop();

    if (p == q) {
      return 0;
    }


    for (int j = 1; j <= 9; ++j) {
      int a = j * 1000 + p % 1000;
      if (a != p && table[a] && !st.count(a)) {
        curs.push(a);
        st.insert(a);
      }
    }

    for (int j = 0; j <= 9; ++j) {
      int a = (p / 1000) * 1000 + j * 100 + p % 100;
      int b = (p / 100) * 100 + j * 10 + p % 10;
      int c = (p / 10) * 10 + j;

      if (table[a] && !st.count(a)) {
        curs.push(a);
        st.insert(a);
      }
      if (table[b] && !st.count(b)) {
        st.insert(b);
        curs.push(b);
      }
      if (table[c] && !st.count(c)) {
        curs.push(c);
        st.insert(c);
      }
    }
  }
  return 1 + bfs(curs, q, st);
}

int main() {
  updateTable();
  int n;
  scanf("%d", &n);
  while (n--) {
    int p, q;
    scanf("%d%d", &p, &q);
    if (uf.isConnected(p, q)) {
      queue<int> curs;
      curs.push(p);
      set<int> st;
      st.insert(p);
      // cout << "p = " << p << " q = " << q << endl;
      int ans = bfs(curs, q, st);
      printf("%d\n", ans);
    } else {
      printf("Impossible\n");
    }
  }
}