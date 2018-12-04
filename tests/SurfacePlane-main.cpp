#include "Surface.h"
#include "SurfacePlane.h"
#include "Line.h"
#include "Vector.h"

#include <iostream>

void print_vector(std::ostream& os, const Vector& v) {
	os << "Vector {" << v.x() << ", " << v.y() << ", " << v.z() << "}";
}

int main(void) {
	const SurfacePlane s {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1200}}, .4};
	Line ray {{0, 0, 1}, {0, 0, -250}};
	Vector light {ray.offset()};

	if (s.intersection(ray).first) {
		print_vector(std::cout, s.intersection(ray).second);
		std::cout << "\n";
	}
}
