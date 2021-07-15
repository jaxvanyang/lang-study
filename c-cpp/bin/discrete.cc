// discrete input

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void parse_input(vector<double> &arr, const int argc, const char* argv[]);

int main(const int argc, const char* argv[]) {
	vector<double> arr;
	vector<double> res;
	parse_input(arr, argc, argv);

	sort(arr.begin(), arr.end());
	for (auto num : arr) {
		if (res.empty() || num != res.back()) {
			res.push_back(num);
		}
	}

	for (auto num : res) {
		cout << num << " ";
	}
	cout << endl;
}
	
void parse_input(vector<double> &arr, const int argc, const char* argv[]) {
	if (argc == 1) {
		double num;
		while (cin >> num) {
			arr.push_back(num);
		}
	} else {
		for (int i = 1; i < argc; ++i) {
			arr.push_back(stod(argv[i]));
		}
	}
}
