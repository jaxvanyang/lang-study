#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

vector<ll> as, bs;
vector<ll> idx{0};
vector<ll> tree;

void build(int l, int r, int p) {
  if (l == r) {
    tree[p] = bs[l];
    return;
  }
  int m = (l + r) / 2;
  build(l, m, p * 2);
  build(m + 1, r, p * 2 + 1);
  tree[p] = gcd(tree[p * 2], tree[p * 2 + 1]);
}

ll getGcd(int l, int r, int begin, int end, int p) {
  if (l <= begin && end <= r) {
    return tree[p];
  }
  int m = (begin + end) / 2;
  if (l <= m && m < r) {
    return gcd(getGcd(l, r, begin, m, p * 2),
               getGcd(l, r, m + 1, end, p * 2 + 1));
  }
  if (l > m) {
    return getGcd(l, r, m + 1, end, p * 2 + 1);
  }
  return getGcd(l, r, begin, m, p * 2);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    ll num;
    scanf("%lld", &num);
    as.push_back(num);
    idx.push_back(idx.back() + num);
  }

  for (int i = 0; i < n; ++i) {
    ll num;
    scanf("%lld", &num);
    bs.push_back(num);
  }

  tree = vector<ll>(4 * n);
  build(0, n - 1, 1);

  int q;
  scanf("%d", &q);
  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    ll a = idx[x2] - idx[x1 - 1];
    ll b = getGcd(y1 - 1, y2 - 1, 0, n - 1, 1);
    printf("%lld\n", a * b);
  }
}