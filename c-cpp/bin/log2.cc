#include <iostream>
#include <cmath>
using namespace std;
using ll = long long;

int h[37] = {0, 0, 1, 26, 2, 23, 27, 32, 3, 16, 24, 30, 28, 11, 33, 13, 4, 7, 17, 35, 25, 22, 31, 15, 29, 10, 12, 6, 34, 21, 14, 9, 5, 20, 8, 19, 18};

int parse_input(ll &n, const int argc, const char* argv[]);

inline ll lowbit(ll n);
int log2(ll n);

int main(const int argc, const char* argv[]) {
	for (int i = 0; i < 36; ++i) {
		h[(1ll << i) % 37] = i;
	}

	ll n = 1;
	int ret = parse_input(n, argc, argv);

	if (!ret) {
		cout << log2(n) << endl;
	}
	
	return ret;
}

inline ll lowbit(ll n) {
	return n & -n;
}

int parse_input(ll &n, const int argc, const char* argv[]) {
	if (argc == 1) {
		cerr << "no argument" << endl;
		return 1;
	}
	n = stol(argv[1]);

	if (n == 0) {
		cerr << "invalid argument" << endl;
		return 2;
	}
	return 0;
}

int log2(ll n) {
	while (n - lowbit(n)) {
		n -= lowbit(n);
	}
	if (n > (1ll << 35)) {
		return round(log(n) / log(2));
	} else {
		return h[n % 37];
	}
}
