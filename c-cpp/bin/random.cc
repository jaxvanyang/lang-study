#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
using ll = long long;

int random(int lmt);
void parse_input(vector<double> &arr, int &n, int &size, const int argc, const char* argv[]);

int main(const int argc, const char* argv[]) {
	srand((unsigned)time(0));

	vector<double> arr;
	int size = 100;
	int lmt = 1000;

	parse_input(arr, lmt, size, argc, argv);

	for (int i = 0; i < size; ++i) arr.push_back(random(lmt));
	
	for (auto num : arr) {
		cout << num << ' ';
	}
	cout << endl;
}

void parse_input(vector<double> &arr, int &lmt, int &size, const int argc, const char* argv[]) {
	if (argc >= 2) {
		size = stoi(argv[1]);
	}
	if (argc == 3) {
		lmt = stoi(argv[2]);
	}
}

int random(int n) {
	return (ll)rand() * rand() % n;
}
