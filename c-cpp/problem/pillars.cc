/*
 * @from https://vjudge.net/contest/417989#problem/I
 */

#include <iostream>

int main() {
	int n = 3;
	std::cin >> n;
	int a, b, i = 1;
	std::cin >> a;
	while (i < n) {
		std::cin >> b;
		++i;
		if (a >= b) {
			break;
		}
		a = b;
	}
	a = b;
	while (i < n) {
		std::cin >> b;
		if (a <= b) {
			break;
		}
		a = b;
		++i;
	}
	if (i == n) {
		std::cout << "YES" << std::endl;
	} else {
		std::cout << "NO" << std::endl;
	}

	return 0;
}
