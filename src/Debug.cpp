#include "Debug.h"
std::ostream& operator<<(std::ostream& os, const Matrix& m) {
	for (size_t i {0}; i < m.size(); ++i) {
		for (size_t j {0}; j < m[i].size(); ++j)
			os << m[i][j] << " ";
		os << '\n';
	}

	return os;
}  

std::ostream& operator<<(std::ostream& os, const Vector& v) {
	os << '('<< v.x() << ", " << v.y() << ", " << v.z() << ")";

	return os;
}

std::ostream& operator<<(std::ostream& os, const Line& l) {
	os << 's' << l.direction() << " + " << l.offset();

	return os;
}


std::ostream& operator<<(std::ostream& os, const Plane& p) {
	os << 's' << p.u() << " + t" << p.v() << " + " << p.offset();

	return os;
}
