/*
 * @from https://vjudge.net/contest/417989#problem/J
 */

#include <iostream>
//#include <climits>

const int maxn = 1e6 + 5;
int arr[maxn];

bool is_rainy(int i, int n, int x, int y) {
	int l = i - x, r = i + y;
	while (l < 1) {
		++l;
	}
	while (r > n) {
		--r;
	}
	for (int p = l; p <= r; p++) {
		if (arr[p] < arr[i]) {
			return true;
		}
	}
	return false;
}

int main() {
//	std::cout << INT_MAX << std::endl;
	int n, x, y;
	std::cin >> n >> x >> y;
	for (int i = 1; i <= n; i++) {
		std::cin >> arr[i];
	}
	for (int i = 1; i <= n; i++) {
		if (!is_rainy(i, n, x, y)) {
			std::cout << i << std::endl;
			return 0;
		}
	}

	return 0;
}
