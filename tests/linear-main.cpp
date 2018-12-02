#include "Linear.h"

#include <iostream>

void print_matrix(std::ostream& os, const Matrix& m) {
	for (size_t i {0}; i < m.size(); ++i) {
		for (size_t j {0}; j < m[i].size(); ++j)
			os << m[i][j] << " ";
		os << '\n';
	}
}

int main(void) {
	size_t n, m;
	std::cin >> n >> m;

	Matrix a {create_matrix(n, m)};
	std::cerr << "Created matrix\n";
	for (size_t i {0}; i < a.size(); ++i)
		for (size_t j {0}; j < a[i].size(); ++j)
			std::cin >> a[i][j];
	std::cerr << "Read Matrix\n";
	print_matrix(std::cout, a);
	std::cerr << "Printed Matrix\n";
	a = rref(a);
	print_matrix(std::cout, a);
}
