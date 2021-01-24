/*
 * @from CSUST 2020 寒假集训热身题 H
 */

using namespace std;

int main() {
	int t = 0;
	std::cin >> t;
	while (t--) {
		int n = 0;
		int first = 0, second = 1;
		std::cin >> n;
		for (int i = 0; i < n; i++) {
			int tmp = 0;
			std::cin >> tmp;
			if (tmp > first) {
				second = first;
				first = tmp;
			} else if (tmp > second) {
				second = tmp;
			}
		}
		int ans = second - 1;
		std::cout << min(ans, max(0, n - 2)) << std::endl;
	}

	return 0;
}
