#include "./vector2.hpp"

double Vector2::lengthSquared()
{
    return this->x * this->x + this->y * this->y;
}
double Vector2::length()
{
    return std::sqrt(this->x * this->x + this->y * this->y);
}
Vector2 Vector2::operator+(const Vector2 &other) const
{
    return Vector2{this->x + other.x, this->y + other.y};
}
Vector2 Vector2::operator-(const Vector2 &other) const
{
    return Vector2{this->x - other.x, this->y - other.y};
}
Vector2 Vector2::operator+(const double &other) const
{
    return Vector2{this->x + other, this->y + other};
}
Vector2 Vector2::operator-(const double &other) const
{
    return Vector2{this->x - other, this->y - other};
}
Vector2 Vector2::operator*(const double &other) const
{
    return Vector2{this->x * other, this->y * other};
}
Vector2 Vector2::operator/(const double &other) const
{
    return Vector2{this->x / other, this->y / other};
}
Vector2 operator+(const double &left, const Vector2 &right)
{
    return Vector2{left + right.x, left + right.y};
}
Vector2 operator-(const double &left, const Vector2 &right)
{
    return Vector2{left - right.x, left - right.y};
}
Vector2 operator*(const double &left, const Vector2 &right)
{
    return Vector2{left * right.x, left * right.y};
}
Vector2 operator/(const double &left, const Vector2 &right)
{
    return Vector2{left / right.x, left / right.y};
}