#include "Vec3.h"

Vec3::Vec3() {
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(double num) {
	x = num;
	y = num;
	z = num;
}

Vec3::Vec3(double inX, double inY, double inZ) {
	x = inX;
	y = inY;
	z = inZ;
}

Vec3 Vec3::operator+(const Vec3 v) {
	Vec3 result;
	result.x = x + v.x;
	result.y = y + v.y;
	result.z = z + v.z;
	return result;
}

Vec3 Vec3::operator-(const Vec3 v) {
	Vec3 result;
	result.x = x - v.x;
	result.y = y - v.y;
	result.z = z - v.z;
	return result;
}

Vec3 Vec3::operator*(const Vec3 v) {
	Vec3 result;
	result.x = x * v.x;
	result.y = y * v.y;
	result.z = z * v.z;
	return result;
}

Vec3 Vec3::operator*(const float c) {
	Vec3 result;
	result.x = x * c;
	result.y = y * c;
	result.z = z * c;
	return result;
}

Vec3 Vec3::operator/(const float c) {
	Vec3 result;
	result.x = x / c;
	result.y = y / c;
	result.z = z / c;
	return result;
}

float Vec3::dot(Vec3 v) {
	return (x * v.x) + (y * v.y) + (z * v.z);
}

void Vec3::normalize() {
	float magnitude = sqrt((x * x) + (y * y) + (z * z));
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}

float Vec3::calculateMagnitude() {
	float magnitude = sqrt((x * x) + (y * y) + (z * z));
	return magnitude;
}

void Vec3::setAll(float val) {
	x = val;
	y = val;
	z = val;
}

void Vec3::setEach(float xNew, float yNew, float zNew) {
	x = xNew;
	y = yNew;
	z = zNew;
}

std::ostream& operator<<(std::ostream& os, Vec3 const& v) {
	os << "{" << v.x << ", " << v.y << ", " << v.z << "}";
	return os;
}
