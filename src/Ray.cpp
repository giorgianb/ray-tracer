#include "Ray.h"

Ray::Ray(const Vector& dir, const Vector& off): line {dir, off} {
}

Ray::direction() const {
	return line.direction();
}

Ray::offset() const {
	return line.offset();
}
