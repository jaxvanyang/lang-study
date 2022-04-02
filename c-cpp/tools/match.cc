// use KMP algorithm to match a string in a longer text
// reference: https://cp-algorithms.com/string/prefix-function.html

#include <iostream>
#include <vector>

void parse_input(std::string &s, std::string &t, const int argc, const char* argv[]) {
	if (argc == 1) {
		std::cin >> s >> t;
	} else if (argc == 3) {
		s.assign(argv[1]);
		t.assign(argv[2]);
	} else {
		std::cerr << "invalid parameter" << std::endl;
		exit(1);
	}
	if (s.size() < t.size()) std::swap(s, t);
}

std::vector<unsigned int> prefix_func(const std::string s) {
	std::cout << s << std::endl;
	size_t n = s.size();
	std::vector<unsigned int> next(n);
	for (size_t i = 1; i < n; ++i) {
		int len = next[i - 1];
		while (0 < len && s[len] != s[i]) {
			len = next[len - 1];	// Note: minus 1 to indicate it is a index rather than a length
		}
		if (s[len] == s[i]) {
			++len;
		}
		next[i] = len;
	}
	return next;
}

template<typename T>
void print(const std::vector<T> arr) {
	for (auto val : arr) {
		std::cout << val << ' ';
	}
	std::cout << std::endl;
}


int main(const int argc, const char* argv[]) {
	std::string text, str;
	parse_input(text, str, argc, argv);
	auto next = prefix_func(str);

	size_t n = text.size(), m = str.size();
	auto f = std::vector<unsigned int>(n);
	bool found = false;
	f[0] = str[0] == text[0] ? 1 : 0;	// Note: we have to evaluate f[0] first
	for (size_t i = 1; i < n; ++i) {
		size_t len = f[i - 1];
		while (0 < len && (str[len] != text[i] || len == m)) {
			len = next[len - 1];
		}
		if (str[len] == text[i]) {
			++len;
		}
		f[i] = len;
	}
	for (size_t i = 0; i < n; ++i) {
		if (f[i] == m) {
			found = true;
			std::cout << "found " << str << " at index " << i - m + 1 << std::endl;
		}
	}
	if (!found) {
		std::cout << "no " << str << " was found in " << text << std::endl
				  << "and there is the matching result:" << std::endl;
		print(f);
	}
}
