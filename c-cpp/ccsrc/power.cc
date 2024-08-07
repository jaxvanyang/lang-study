// quick power & calculate sum of geometric progression

#include <iostream>
using namespace std;
using ll = long long;

void parse_input(ll &p, ll &c, const int argc, const char* argv[]);
bool endwith(const string s, const string t);
ll quick_power(ll p, ll c);
ll sum(ll p, ll c);

int main(const int argc, const char* argv[]) {
	ll p = 1, c = 1;
	parse_input(p, c, argc, argv);
	ll res;

	string arg0 = argv[0];
	if (endwith(arg0, "power.out")) {
		if (p == 0 && c == 0) {
			cout << "input invalid" << endl;
			return 1;
		}
		res = quick_power(p, c);
	} else if (endwith(arg0, "sum.out")) {
		if (p < 2) {
			cout << "input invalid" << endl;
			return 1;
		}
		res = sum(p, c);
	} else {
		cout << "invalid command" << endl;
		return 2;
	}
	cout << res << endl;
}

bool endwith(const string s, const string t) {
	return s.rfind(t) == s.size() - t.size();
}

void parse_input(ll &p, ll &c, const int argc, const char* argv[]) {
	if (argc == 3) {
		p = stoll(argv[1]);
		c = stoll(argv[2]);
	} else {
		cin >> p >> c;
	}
}
	
ll quick_power(ll p, ll c) {
	if (p == 0) return 0;
	ll ret = 1;
	while (c) {
		if (c & 1) ret *= p;
		p *= p;
		c >>= 1;
	}
	return ret;
}

ll sum(ll p, ll c) {
	if (c == 0) return 1;
	if (p & 1) {
		return (1 + quick_power(p, c / 2 + 1)) * sum(p, c / 2 - 1);
	}
	return p * sum(p, c - 1) + 1;
}

