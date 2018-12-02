#include "debug.h"

void print_matrix(std::ostream& os, const Matrix& m) {
	for (size_t i {0}; i < m.size(); ++i) {
		for (size_t j {0}; j < m[i].size(); ++j)
			os << m[i][j] << " ";
		os << '\n';
	}
}  

void print_vector(std::ostream& os, const Vector& v) {
	os << '('<< v.x() << ", " << v.y() << ", " << v.z() << ")";
}

void print_line(std::ostream& os, const Line& l) {
	os << 's';
	print_vector(os, l.direction());
	os << " + ";
	print_vector(os, l.offset());
}


void print_plane(std::ostream& os, const Plane& p) {
	os << 's';
	print_vector(os, p.u());
	os << " + ";
	os << 't';
	print_vector(os, p.v());
	os << " + ";
	print_vector(os, p.offset());
}


