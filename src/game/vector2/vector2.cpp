#include "./vector2.hpp"

double Vector2::lengthSquared() {
    return this->x * this->x + this->y * this->y;
}
double Vector2::length() {
    return std::sqrt(this->x * this->x + this->y * this->y);
}
bool Vector2::isXBiggerThanY(void) { return this->x > this->y; }
bool Vector2::isYBiggerThanX(void) { return this->x < this->y; }
bool Vector2::isXBiggerThanNegativeY(void) { return this->x > -this->y; }
bool Vector2::isYBiggerThanNegativeX(void) { return -this->x < this->y; }
bool Vector2::isNegativeXBiggerThanY(void) { return this->x > -this->y; }
bool Vector2::isNegativeYBiggerThanX(void) { return this->x < -this->y; }
Vector2 Vector2::operator+(const Vector2 &other) const {
    return Vector2{this->x + other.x, this->y + other.y};
}
Vector2 Vector2::operator-(const Vector2 &other) const {
    return Vector2{this->x - other.x, this->y - other.y};
}
Vector2 Vector2::operator+(const double &other) const {
    return Vector2{this->x + other, this->y + other};
}
Vector2 Vector2::operator-(const double &other) const {
    return Vector2{this->x - other, this->y - other};
}
Vector2 Vector2::operator*(const double &other) const {
    return Vector2{this->x * other, this->y * other};
}
Vector2 Vector2::operator/(const double &other) const {
    return Vector2{this->x / other, this->y / other};
}

void Vector2::operator+=(const Vector2 &other) {
    this->x = this->x + other.x;
    this->y = this->y + other.y;
}
void Vector2::operator-=(const Vector2 &other) {
    this->x = this->x - other.x;
    this->y = this->y - other.y;
}
void Vector2::operator+=(const double &other) {
    this->x = this->x + other;
    this->y = this->y + other;
}
void Vector2::operator-=(const double &other) {
    this->x = this->x - other;
    this->y = this->y - other;
}
void Vector2::operator*=(const double &other) {
    this->x = this->x * other;
    this->y = this->y * other;
}
void Vector2::operator/=(const double &other) {
    this->x = this->x / other;
    this->y = this->y / other;
}

Vector2 operator+(const double &left, const Vector2 &right) {
    return Vector2{left + right.x, left + right.y};
}
Vector2 operator-(const double &left, const Vector2 &right) {
    return Vector2{left - right.x, left - right.y};
}
Vector2 operator*(const double &left, const Vector2 &right) {
    return Vector2{left * right.x, left * right.y};
}
Vector2 operator/(const double &left, const Vector2 &right) {
    return Vector2{left / right.x, left / right.y};
}