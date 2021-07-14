// output input's complement representation to stdout

#include <iostream>
using namespace std;
using ll = long long;
using ull = unsigned long long;

void parse_input(ll &num, const int argc, const char* argv[]);
string itob(ull num);

int main(const int argc, const char* argv[]) {
	ll num;
	parse_input(num, argc, argv);
	printf("0x%llX\n", num);
	printf("0%llo\n", num);
	cout << itob(num) << endl;
}

void parse_input(ll &num, const int argc, const char* argv[]) {
	if (argc == 2) {
		num = stol(argv[1]);
	} else {
		cin >> num;
	}
}

string itob(ull num) {
	if (num == 0) return "0";
	string ret;
	while (num) {
		if (num & 1) ret.insert(0, "1");
		else ret.insert(0, "0");
		num >>= 1;
	}
	return ret;
}
