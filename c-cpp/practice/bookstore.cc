#include <iostream>
#include <climits>
#include "Sales_item.h"

int main() {
	Sales_item total, curr_item;
	if (std::cin >> total) {
		while (std::cin >> curr_item) {
			if (total.isbn() == curr_item.isbn()) {
				total += curr_item;
			} else {
				std::cout << total << std::endl;
				total = curr_item;
			}
		}
		std::cout << total << std::endl;
	}
	return 0;
}
