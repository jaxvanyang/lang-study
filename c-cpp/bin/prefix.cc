// calculate prefix sum or finite difference

#include <iostream>
#include <vector>
using namespace std;

bool endwith(const string s, const string t);
void parse_input(vector<double> &arr, const int argc, const char* argv[]);
void calc_prefix(vector<double> &arr, vector<double> &res);
void calc_diff(vector<double> &arr, vector<double> &res);

int main(const int argc, const char* argv[]) {
	vector<double> arr{0}, res{0};

	parse_input(arr, argc, argv);
	string arg0 = argv[0];
	if (endwith(arg0, "prefix.out")) {
		calc_prefix(arr, res);
	} else if (endwith(arg0, "diff.out")) {
		calc_diff(arr, res);
	} else {
		cout << "invalid command!" << endl;
		return 1;
	}
	for (int i = 1; i < res.size(); ++i) {
		printf("%.1lf ", res[i]);
	}
	puts("");
}

bool endwith(const string s, const string t) {
	return s.rfind(t) == s.size() - t.size();
}

void parse_input(vector<double> &arr, const int argc, const char* argv[]) {
	if (argc == 1) {
		double tmp;
		while (cin >> tmp) {
			arr.push_back(tmp);
		}
	} else {
		for (int i = 1; i < argc; ++i) {
			arr.push_back(stod(argv[i]));
		}
	}
}

void calc_prefix(vector<double> &arr, vector<double> &res) {
	for (int i = 1; i < arr.size(); ++i) {
		res.push_back(arr[i] + res.back());
	}
}

void calc_diff(vector<double> &arr, vector<double> &res) {
	for (int i = 1; i < arr.size(); ++i) {
		res.push_back(arr[i] - arr[i - 1]);
	}
}
