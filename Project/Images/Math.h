
class LGVector2D
{

public:

	float x, y;
	LGVector2D();
	LGVector2D(float xInit, float yInit);

	void zero(LGVector2D& v);
	void set(LGVector2D& v);
	void set(float xs, float ys);
	LGVector2D clone();

	void setAngle(float a);
	void setAngleDeg(float a);
	float getAngle();
	float getAngleDeg();
	void rotateBy(float l);

	void add(LGVector2D& v);
	void subtract(LGVector2D& v);
	void multiply(float s);
	void divide(float s);

	void normalize();
	void setLength(float l);
	float getLength();

	float dot(LGVector2D& v);
	float cross(LGVector2D& v);
	float distanceTo(LGVector2D v);
	void lookAt(LGVector2D& v);

	void print(bool includeEndline = true);

	LGVector2D operator+ (const LGVector2D& v) const;
	LGVector2D operator- (const LGVector2D& v) const;
	LGVector2D operator* (const float s) const;
	float operator* (const LGVector2D& v) const; //dot product
	float operator^ (const LGVector2D& v) const; //cross product	
	LGVector2D operator/ (const float s) const;
	LGVector2D operator/ (const LGVector2D& v) const;
	bool operator== (const LGVector2D& v) const;
	void operator= (const LGVector2D& v);
	void operator+= (const LGVector2D& v);
	void operator-= (const LGVector2D& v);
	void operator*= (const float s);
	void operator/= (const float s);
	float operator[] (int i);

};


#include <math.h>

LGVector2D::LGVector2D() {
	x = 0;
	y = 0;
}

LGVector2D::LGVector2D(float xInit, float yInit) {
	x = xInit;
	y = yInit;
}

void LGVector2D::set(LGVector2D& v) {
	x = v.x;
	y = v.y;
}

void LGVector2D::set(float xs, float ys) {
	x = xs;
	y = ys;
}

LGVector2D LGVector2D::clone() {
	return LGVector2D(x, y);
}

void LGVector2D::zero(LGVector2D& v) {
	x = 0;
	y = 0;
}

void LGVector2D::add(LGVector2D& v) {
	x += v.x;
	y += v.y;
}

void LGVector2D::subtract(LGVector2D& v) {
	x -= v.x;
	y -= v.y;
}

void LGVector2D::multiply(float s) {
	x *= s;
	y *= s;
}

void LGVector2D::divide(float d) {
	x /= d;
	y /= d;
}

void LGVector2D::normalize() {
	float length = sqrt(x * x + y * y);
	x = x / length;
	y = y / length;
}

float LGVector2D::getLength() {
	return sqrt(x * x + y * y);
}

void LGVector2D::setLength(float l) {
	float length = sqrt(x * x + y * y);
	x = (x / length) * l;
	y = (y / length) * l;
}

float LGVector2D::getAngle() {
	return atan2(y, x);
}

float LGVector2D::getAngleDeg() {
	return atan2(y, x) * 57.2957;
}

void LGVector2D::setAngle(float a) {
	float length = sqrt(x * x + y * y);
	x = cos(a) * length;
	y = sin(a) * length;
}

void LGVector2D::setAngleDeg(float a) {
	float length = sqrt(x * x + y * y);
	a *= 0.0174532925;
	x = cos(a) * length;
	y = sin(a) * length;
}

void LGVector2D::rotateBy(float l) {
	float angle = getAngle();
	float length = sqrt(x * x + y * y);
	x = cos(l + angle) * length;
	y = sin(l + angle) * length;
}

float LGVector2D::dot(LGVector2D& v) {
	return x * v.x + y * v.y;
}

float LGVector2D::cross(LGVector2D& v) {
	return (x * v.y) - (y * v.x);
}

float LGVector2D::distanceTo(LGVector2D v) {
	LGVector2D distanceVector = LGVector2D(v.x - x, v.y = y);
	return distanceVector.getLength();
}

void LGVector2D::lookAt(LGVector2D& v) {
	LGVector2D* vectorToTarget = new LGVector2D(v.x - x, v.y - y);
	setAngle(vectorToTarget->getAngle());
}

//OPERATORS

LGVector2D LGVector2D::operator+ (const LGVector2D& v) const {
	return LGVector2D(x + v.x, y + v.y);
}

LGVector2D LGVector2D::operator- (const LGVector2D& v) const
{
	LGVector2D Ret;
	Ret.set(x - v.x, y - v.y);
	return Ret;
}

LGVector2D LGVector2D::operator* (const float s) const {
	return LGVector2D(x * s, y * s);
}

//dot product
float LGVector2D::operator* (const LGVector2D& v) const {
	return (x * v.x + y * v.y);
}

//cross product	
float LGVector2D::operator^ (const LGVector2D& v) const {
	return (x * v.y) - (y * v.x);
}

LGVector2D LGVector2D::operator/ (const float s) const {
	return LGVector2D(x / s, y / s);
}

LGVector2D LGVector2D::operator/ (const LGVector2D& v) const {
	return LGVector2D(x / v.x, y / v.y);
}

bool LGVector2D::operator== (const LGVector2D& v) const {
	return (x == v.x && y == v.y);
}

void LGVector2D::operator= (const LGVector2D& v) {
	x = v.x;
	y = v.y;
}

void LGVector2D::operator+= (const LGVector2D& v) {
	x += v.x;
	y += v.y;
}

void LGVector2D::operator-= (const LGVector2D& v) {
	x -= v.x;
	y -= v.y;
}

void LGVector2D::operator*= (const float s) {
	x *= s;
	y *= s;
}

void LGVector2D::operator/= (const float s) {
	x /= s;
	y /= s;
}

float LGVector2D::operator[] (int i) {
	if (i == 0) return x;
	else return y;
}
