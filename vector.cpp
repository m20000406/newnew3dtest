/////////////////////////////
//vector.cpp
//ヴェクタ関係の云々
/////////////////////////////
#include "vector.h"
#include <math.h>

vector vector::zero = vector(0, 0, 0);

vector::vector(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}

vector::vector():x(0),y(0),z(0){}

vector operator+(vector a, vector b) {
	return vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

vector operator-(vector a, vector b) {
	return vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

vector operator*(float r, vector a) {
	return vector(a.x*r, a.y*r, a.z*r);
}

vector operator*(vector a, float r) {
	return r*a;
}

vector operator/(vector a, float r) {
	if (r != 0)return vector(a.x / r, a.y / r, a.z / r);
	else return vector(0, 0, 0);
}

float operator*(vector a, vector b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

float vector::norm() {
	return sqrtf(x*x + y*y + z*z);
}

vector normalize(vector a) {
	float f = a.norm();
	if (f == 0)return vector::zero;
	else return a / f;
}

vector vector::operator+=(vector a) {
	return vector(this->x + a.x, this->y + a.y, this->z + a.z);
}

vector vector::operator-=(vector a) {
	return vector(this->x - a.x, this->y - a.y, this->z - a.z);
}

vector vector::operator*=(float a) {
	return vector(this->x*a, this->y*a, this->z*a);
}

vector vector::operator/=(float a) {
	if (a == 0)return vector::zero;
	return vector(this->x / a, this->y / a, this->z / a);
}

float vector::operator*=(vector a) {
	return this->x*a.x + this->y*a.y + this->z*a.z;
}

vector round(vector v) {
	return vector(round(v.x),round(v.y),v.z);
}