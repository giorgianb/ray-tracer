#include "PointLightSource.h"

PointLightSource::PointLightSource(const Vector& position, const double brightness):
	_position {position},
	_brightness {brightness} {
}

double PointLightSource::brightness() const {
	return _brightness;
}

Vector PointLightSource::position() const {
	return _position;
}
