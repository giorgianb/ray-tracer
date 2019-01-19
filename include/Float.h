#ifndef __RAY_TRACER_FLOAT_INCLUDED
#define __RAY_TRACER_FLOAT_INCLUDED
#include <cmath>

class Float {
	private:
		double _f;
	public:
		constexpr static double epsilon {1e-9};

		constexpr Float(const double f) noexcept;
		constexpr Float(const Float& f) = default;

		constexpr double value() const noexcept;

		explicit constexpr operator double() const noexcept;
		constexpr Float& operator+=(const Float& f) noexcept;
		constexpr Float& operator-=(const Float& f) noexcept;
		constexpr Float& operator*=(const Float& f) noexcept;
		constexpr Float& operator/=(const Float& f) noexcept;
};

constexpr Float operator+(const Float& f1, const Float& f2) noexcept;
constexpr Float operator-(const Float& f1, const Float& f2) noexcept;
constexpr Float operator*(const Float& f1, const Float& f2) noexcept;
constexpr Float operator/(const Float& f1, const Float& f2) noexcept;
constexpr Float operator-(const Float& f) noexcept;
constexpr bool operator==(const Float& f1, const Float& f2) noexcept;
constexpr bool operator!=(const Float& f1, const Float& f2) noexcept;
constexpr bool operator<(const Float& f1, const Float& f2) noexcept;
constexpr bool operator<=(const Float& f1, const Float& f2) noexcept;
constexpr bool operator>(const Float& f1, const Float& f2) noexcept;
constexpr bool operator>=(const Float& f1, const Float& f2) noexcept;

constexpr Float::Float(const double f) noexcept: _f {f} {
}

constexpr double Float::value() const noexcept {
	return _f;
}

constexpr Float::operator double() const noexcept {
	return _f;
}

constexpr Float& Float::operator+=(const Float& f) noexcept {
	_f += f.value();
	return *this;
}

constexpr Float& Float::operator-=(const Float& f) noexcept {
	_f -= f.value();
	return *this;
}

constexpr Float& Float::operator*=(const Float& f) noexcept {
	_f *= f.value();
	return *this;
}

constexpr Float& Float::operator/=(const Float& f) noexcept {
	_f /= f.value();
	return *this;
}

constexpr Float operator+(const Float& f1, const Float& f2) noexcept {
	return f1.value() + f2.value();
}

constexpr Float operator-(const Float& f1, const Float& f2) noexcept {
	return f1.value() - f2.value();
}

constexpr Float operator*(const Float& f1, const Float& f2) noexcept {
	return f1.value() * f2.value();
}

constexpr Float operator/(const Float& f1, const Float& f2) noexcept {
	return f1.value() / f2.value();
}


constexpr Float operator-(const Float& f) noexcept {
	return -f.value();
}

constexpr bool operator==(const Float& f1, const Float& f2) noexcept {
	return std::fabs(f1.value() - f2.value()) <= Float::epsilon;
}

constexpr bool operator!=(const Float& f1, const Float& f2) noexcept {
	return !(f1 == f2);
}

constexpr bool operator<(const Float& f1, const Float& f2) noexcept {
	return f1 != f2 && f1.value() < f2.value();
}

constexpr bool operator<=(const Float& f1, const Float& f2) noexcept {
	return f1 == f2 || f1.value() < f2.value();
}

constexpr bool operator>(const Float& f1, const Float& f2) noexcept {
	return f1 != f2 && f1.value() > f2.value();
}

constexpr bool operator>=(const Float& f1, const Float& f2) noexcept {
	return f1 == f2 || f1.value() > f2.value();
}
#endif
