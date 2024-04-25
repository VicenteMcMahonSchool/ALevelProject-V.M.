#pragma once
#include <math.h>

#define POSITION(vector2) vector2.x, vector2.y
struct Vector2
{
    double x, y;
    double lengthSquared();
    double length();
    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator+(const double &other) const;
    Vector2 operator-(const double &other) const;
    Vector2 operator*(const double &other) const;
    Vector2 operator/(const double &other) const;
    friend Vector2 operator+(const double &left, const Vector2 &right);
    friend Vector2 operator-(const double &left, const Vector2 &right);
    friend Vector2 operator*(const double &left, const Vector2 &right);
    friend Vector2 operator/(const double &left, const Vector2 &right);
};
