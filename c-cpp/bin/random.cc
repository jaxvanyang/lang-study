/*
 * Usage:
 *		random.out [size] [lmt]
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using ll = long long;

int random(int lmt);
void parse_input(std::vector<double> &arr, int &n, int &size, const int argc, const char* argv[]);

int main(const int argc, const char* argv[]) {
	srand((unsigned)time(0));

	std::vector<double> arr;
	int size = 100;
	int lmt = 1000;

	parse_input(arr, lmt, size, argc, argv);

	for (int i = 0; i < size; ++i) arr.push_back(random(lmt));
	
	for (auto num : arr) {
		std::cout << num << ' ';
	}
	std::cout << std::endl;
}

void parse_input(std::vector<double> &arr, int &lmt, int &size, const int argc, const char* argv[]) {
	if (argc >= 2) {
		size = std::stoi(argv[1]);
	}
	if (argc == 3) {
		lmt = std::stoi(argv[2]);
	}
}

int random(int n) {
	return (ll)rand() * rand() % n;
}
