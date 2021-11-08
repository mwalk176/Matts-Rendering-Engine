#include "Vec2.h"

Vec2::Vec2() {
	u = 0;
	v = 0;
}

Vec2::Vec2(float num) {
	u = num;
	v = num;
}

Vec2::Vec2(float inU, float inV) {
	u = inU;
	v = inV;
}

Vec2 Vec2::operator+(const Vec2 vec) {
	Vec2 result;
	result.u = u + vec.u;
	result.v = v + vec.v;
	return result;
}

Vec2 Vec2::operator-(const Vec2 vec) {
	Vec2 result;
	result.u = u - vec.u;
	result.v = v - vec.v;
	return result;
}

Vec2 Vec2::operator*(const Vec2 vec) {
	Vec2 result;
	result.u = u * vec.u;
	result.v = v * vec.v;
	return result;
}

Vec2 Vec2::operator*(const float c) {
	Vec2 result;
	result.u = u * c;
	result.v = v * c;
	return result;
}

Vec2 Vec2::operator/(const float c) {
	Vec2 result;
	result.u = u / c;
	result.v = v / c;
	return result;
}

float Vec2::dot(Vec2 vec) {
	return (u * vec.u) + (v * vec.v);
}

void Vec2::normalize() {
	float magnitude = sqrt((u * u) + (v * v));
	u /= magnitude;
	v /= magnitude;
}

float Vec2::calculateMagnitude() {
	float magnitude = sqrt((u * u) + (v * v));
	return magnitude;
}

void Vec2::setAll(float val) {
	u = val;
	v = val;
}

void Vec2::setEach(float uNew, float vNew) {
	u = uNew;
	v = vNew;
}

void Vec2::clamp() {
	if (u > 1) u = 1;
	if (v > 1) v = 1;
}

std::ostream& operator<<(std::ostream& os, Vec2 const& vec) {
	os << "{" << vec.u << ", " << vec.v << "}";
	return os;
}
