// calculate integer expression

#include <iostream>
#include <cmath>
#include <regex>
#include <cctype>
#include <map>
#include <stack>

using ll = long long;

std::map<char, int> opt_priority{
	std::pair<char, int>(' ', -1),	// 冗余
	std::pair<char, int>('(', 0),
	std::pair<char, int>('+', 1),
	std::pair<char, int>('-', 1),
	std::pair<char, int>('*', 2),
	std::pair<char, int>('/', 2),
	std::pair<char, int>('^', 3),
};

void parse_input(std::string &infix_expr, const int argc, const char* argv[]);
void format_expr(std::string &expr);
ll get_ll(std::string &s, size_t &begin);
std::string get_ll_str(std::string &s, size_t &begin);
std::string trans_formated_expr(std::string infix_expr);
ll calc_formated_expr(std::string &expr);

int main(const int argc, const char* argv[]) {
	std::string infix_expr, post_expr;
	parse_input(infix_expr, argc, argv);
	format_expr(infix_expr);
	std::cout << "formated infix expr = " << infix_expr << std::endl;
	
	// TODO: add detailed error message in every function
	// TODO: add check function
	// if (!check(infix_expr)) {
	// 	std::cerr << "invalid input expression!" << std::endl;
	// 	return 1;
	// }

	post_expr = trans_formated_expr(infix_expr);
	std::cout << post_expr << std::endl;
	std::cout << calc_formated_expr(post_expr) << std::endl;
}

void parse_input(std::string &infix_expr, const int argc, const char* argv[]) {
	if (argc == 1) {
		getline(std::cin, infix_expr);
	} else {
		infix_expr.clear();
		for (int i = 1; i < argc; ++i) {
			infix_expr.append(argv[i]);
		}
	}
}

void format_expr(std::string &expr) {
	expr.assign(std::regex_replace(expr, std::regex("\\s"), ""));
	if (expr.size()) {
		auto first = expr.front();
		if (first == '+' || first == '-') {
			expr.insert(0, "0");
		}
	}
}

// also change the input index
ll get_ll(std::string &s, size_t &begin) {
	ll ret = 0;
	size_t len = s.size();
	for (; begin < len && isdigit(s[begin]); ++begin) {
		ret = ret * 10 + s[begin] - '0';
	}
	return ret;
}

std::string get_ll_str(std::string &s, size_t &begin) {
	std::string ret;
	size_t len = s.size();
	for (; begin < len && isdigit(s[begin]); ++begin) {
		ret.push_back(s[begin]);
	}
	return ret;
}

std::string trans_formated_expr(std::string infix_expr) {
	std::string post_expr;

	std::stack<char> opt_stk;
	opt_stk.push(' ');
	size_t i = 0, len = infix_expr.length();

	while (i < len) {
		char ch = infix_expr[i];
		if (isdigit(ch)) {
			post_expr.append(get_ll_str(infix_expr, i));
			// Trick: append a space to split each number, while not append to operator
			post_expr.push_back(' ');
		} else {
			if (ch == '(') opt_stk.push(ch);
			else if (ch == ')') {
				while (opt_stk.size() > 1 && opt_stk.top() != '(') {
					post_expr.push_back(opt_stk.top());
					opt_stk.pop();
				}
				opt_stk.pop();
			} else {
				while (opt_stk.size() > 1) {
					int pr = opt_priority[ch], stk_pr = opt_priority[opt_stk.top()];
					if (pr > stk_pr) break;
					post_expr.push_back(opt_stk.top());
					opt_stk.pop();
				}
				opt_stk.push(ch);
			}
			++i;
		}
	}

	while (opt_stk.size() > 1) {
		post_expr.push_back(opt_stk.top());
		opt_stk.pop();
	}

	return post_expr;
}

ll calc_formated_expr(std::string &expr) {
	std::stack<ll> stk;
	size_t i = 0, len = expr.size();
	while (i < len) {
		char ch = expr[i];
		if (isdigit(ch)) {
			stk.push(get_ll(expr, i));
		} else {
			ll val1 = stk.top();
			stk.pop();
			ll val0 = stk.top();
			stk.pop();
			ll res;
			if (ch == '+') res = val0 + val1;
			else if (ch == '-') res = val0 - val1;
			else if (ch == '*') res = val0 * val1;
			else if (ch == '/') res = val0 / val1;
			else if (ch == '^') res = pow(val0, val1);
			else {
				std::cerr << "unknown operator:" << ch << std::endl;
				exit(2);
			}
			stk.push(res);
		}
		// after read a number, i will point a space, so i should be increased, so does operator
		++i;
	}
	return stk.top();
}