/*
 * Used for generator sort data
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
using ll = long long;

ll random(ll n) { return (ll)random() * random() % n; }

int main() {
  int n = 1000, size = 1e4;
  srand(time(nullptr));
  FILE *file = fopen("data.in", "w");

  fprintf(file, "%d\n", size);

  for (int i = 0; i < size; ++i) {
    fprintf(file, "%lld\n", random(n));
  }

  fclose(file);
}