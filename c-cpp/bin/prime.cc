/*
 * Usage:
 *		prime.out [range_lmt]
 *	or
 *		prime.out -n <range_lmt>
 * 	or
 * 		prime.out -c <primes_cnt>
 */

#include <iostream>
#include <vector>

class PrimeChecker {
private:
	int range_lmt;
	std::vector<int> v, primes;

public:
	PrimeChecker(const int range_lmt = 1000) : range_lmt(range_lmt) {
		v.resize(range_lmt + 1);
		filter_primes(v, primes);
	}

	void filter_primes(std::vector<int> &v, std::vector<int> &primes) {
		const int n = v.size() - 1;
		for (int i = 2; i <= n; ++i) {
			if (v[i] == 0) {
				v[i] = i;
				primes.push_back(i);
			}
			for (int prime : primes) {
				if (prime > v[i] || prime > n / i) break;
				v[i * prime] = prime;
			}
		}
	}

	bool is_prime(const int num) {
		if (num < 2) {
			return false;
		}
		if (num > range_lmt) {
			for (int i = 2; i <= range_lmt / i; ++i) {
				if (num % i == 0) {
					return false;
				}
			}
			return true;
		}
		return v[num] == num;
	}

	inline std::vector<int> get_primes() {
		return primes;
	}
};


int main(const int argc, const char* argv[]) {
	int range_lmt = 1000;

	if (argc == 3 && std::string(argv[1]) == "-n") {
		range_lmt = std::stoi(argv[2]);
		PrimeChecker primeChecker = PrimeChecker(range_lmt);
		for (int prime : primeChecker.get_primes()) {
			std::cout << prime << ' ';
		}
		std::cout << std::endl;

		return 0;
	} else if (argc == 3 && std::string(argv[1]) == "-c") {
		const int primes_cnt = std::stoi(argv[2]);
		PrimeChecker primeChecker = PrimeChecker(primes_cnt * 3);
		auto primes = primeChecker.get_primes();
		for (int i = 0; i < std::min(primes_cnt, (int)primes.size()); ++i) {
			std::cout << primes[i] << ' ';
		}
		std::cout << std::endl;
		return 0;
	}


	PrimeChecker primeChecker = PrimeChecker(range_lmt);

	if (argc == 1) {
		int num;
		while (std::cin >> num) {
			std::cout << std::boolalpha << "is " << num << " a prime? " << primeChecker.is_prime(num) << std::endl;
		}
	} else {
		for (int i = 1; i < argc; ++i) {
			int num = std::stoi(argv[i]);
			std::cout << std::boolalpha << "is " << num << " a prime? " << primeChecker.is_prime(num) << std::endl;
		}
	}
}
