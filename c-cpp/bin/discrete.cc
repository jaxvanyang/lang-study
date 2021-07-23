// discrete input

#include <iostream>
#include <algorithm>
#include <vector>

void parse_input(std::vector<double> &arr, const int argc, const char* argv[]);

int main(const int argc, const char* argv[]) {
	std::vector<double> arr;
	std::vector<double> res;
	parse_input(arr, argc, argv);

	std::sort(arr.begin(), arr.end());

	res.assign(arr.begin(), std::unique(arr.begin(), arr.end()));

	for (auto num : res) {
		std::cout << num << " ";
	}
	std::cout << std::endl;
}
	
void parse_input(std::vector<double> &arr, const int argc, const char* argv[]) {
	if (argc == 1) {
		double num;
		while (std::cin >> num) {
			arr.push_back(num);
		}
	} else {
		for (int i = 1; i < argc; ++i) {
			arr.push_back(std::stod(argv[i]));
		}
	}
}
