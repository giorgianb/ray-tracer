#include "Ray.h"

Ray::Ray(const Vector& dir, const Vector& off): line {dir, off} {
}

Vector Ray::direction() const {
	return line.direction();
}

Vector Ray::offset() const {
	return line.offset();
}
