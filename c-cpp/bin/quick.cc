#include <iostream>
using namespace std;
using ll = long long;

void parse_input(ll &p, ll &c, const int argc, const char** args);
bool endwith(const string s, const string t);
ll quick(ll p, ll c);
ll sum(ll p, ll c);

int main(const int argc, const char** args) {
	ll p = 1, c = 1;
	parse_input(p, c, argc, args);
	ll res;

	string arg0 = args[0];
	if (endwith(arg0, "quick.out")) {
		if (p == 0 && c == 0) {
			cout << "input invalid" << endl;
			return 1;
		}
		res = quick(p, c);
	} else if (endwith(arg0, "sum.out")) {
		if (p == 0) {
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

void parse_input(ll &p, ll &c, const int argc, const char** args) {
	if (argc == 3) {
		p = stoll(args[1]);
		c = stoll(args[2]);
	} else {
		cin >> p >> c;
	}
}
	
ll quick(ll p, ll c) {
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
		return (1 + quick(p, c / 2 + 1)) * sum(p, c / 2 - 1);
	}
	return p * sum(p, c - 1) + 1;
}

