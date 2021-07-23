// 求一个字符串的最小表示法

#include <iostream>

void parse_input(std::string &s, const int argc, const char* argv[]);

int main(const int argc, const char* argv[]) {
	std::string s;
	parse_input(s, argc, argv);

	size_t n = s.size();
	s.append(s);

	size_t i = 0, j = 1, k;
	while (i < n && j < n) {
		for (k = 0; k < n && s[i + k] == s[j + k]; ++k);
		if (k == n) break;
		if (s[i + k] > s[j + k]) {
			i = i + k + 1;
		} else {
			j = j + k + 1;
		}
		if (i == j) ++j;
	}

	size_t idx = std::min(i, j);
	s.assign(s.begin() + idx, s.begin() + idx + n);

	std::cout << s << std::endl;
}

void parse_input(std::string &s, const int argc, const char* argv[]) {
	if (argc == 1) {
		std::cin >> s;
	} else {
		s.assign(argv[1]);
		for (size_t i = 2; i < (size_t)argc; ++i) {
			s.push_back(' ');
			s.append(argv[i]);
		}
	}
}
