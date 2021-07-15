// implement different sort algorithm

#include <iostream>
#include <vector>
using namespace std;

void parse_input(vector<double> &arr, const int argc, const char* argv[]);
void quick_sort(vector<double> &arr, int l, int r);
void quick_sort(vector<double> &arr);
void merge_sort(vector<double> &arr, vector<double> &cpy, int l, int r);
void merge_sort(vector<double> &arr);

bool check(vector<double> &arr);
void print(vector<double> &arr);

int main(const int argc, const char* argv[]) {
	vector<double> arr;
	
	parse_input(arr, argc, argv);

	if (argv[1][0] != '-' || argv[1][1] <= '9') {
		quick_sort(arr);
	} else if (argv[1][0] == '-') {
		switch (argv[1][1]) {
			case 'q':
				quick_sort(arr);
				break;
			case 'm':
				merge_sort(arr);
				break;
			default:
				cerr << "input invalid" << endl;
				return 1;
		}
	}

	if (check(arr)) {
		print(arr);
	} else {
		return 2;
	}
}

void parse_input(vector<double> &arr, const int argc, const char* argv[]) {
	if (argc == 1 || (argc == 2 && argv[1][0] == '-' && argv[1][1] > '9')) {
		double num;
		while (cin >> num) {
			arr.push_back(num);
		}
	} else {
		int begin = 1;
		if (argv[1][0] == '-' && argv[1][1] > '9') {
			begin = 2;
		}
		for (int i = begin; i < argc; ++i) {
			arr.push_back(stod(argv[i]));
		}
	}
}

void quick_sort(vector<double> &arr, int l, int r) {
	if (l >= r) return;

	int val = arr[(l + r) >> 1];
	int i = l - 1, j = r + 1;
	while (i < j) {
		do ++i; while (arr[i] < val);
		do --j; while (arr[j] > val);
		if (i < j) swap(arr[i], arr[j]);
	}
	quick_sort(arr, l, j);
	quick_sort(arr, j + 1, r);
}

void quick_sort(vector<double> &arr) {
	quick_sort(arr, 0, arr.size() - 1);
}

bool check(vector<double> &arr) {
	for (size_t i = 1; i < arr.size(); ++i) {
		if (arr[i] < arr[i - 1]) {
			cout << "arr is not sorted!" << endl;
			printf("arr[%ld] > arr[%ld]\n", i - 1, i);
			return false;
		}
	}
	return true;
}

void print(vector<double> &arr) {
	for (auto num : arr) {
		cout << num << ' ';
	}
	cout << endl;
}

void merge_sort(vector<double> &arr, vector<double> &cpy, int l, int r) {
	if (l >= r) return;
	int mid = (l + r) >> 1;
	merge_sort(arr, cpy, l, mid);
	merge_sort(arr, cpy, mid + 1, r);

	int i = l, j = mid + 1;
	int p = l;
	while (i <= mid && j <= r) {
		if (arr[i] < arr[j]) cpy[p++] = arr[i++];
		else cpy[p++] = arr[j++];
	}
	while (i <= mid) cpy[p++] = arr[i++];
	while (j <= r) cpy[p++] = arr[j++];

	for (int i = l; i <= r; ++i) arr[i] = cpy[i];
}

void merge_sort(vector<double> &arr) {
	vector<double> cpy(arr.size());
	merge_sort(arr, cpy, 0, arr.size() - 1);
}
