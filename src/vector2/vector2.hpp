#pragma once
#include <math.h>

#define POSITION(vector2) vector2.x, vector2.y
struct Vector2
{
    double x, y;
    double lengthSquared(void);
    double length(void);
    bool isXBiggerThanY(void);
    bool isYBiggerThanX(void);
    bool isXBiggerThanNegativeY(void);
    bool isYBiggerThanNegativeX(void);
    bool isNegativeXBiggerThanY(void);
    bool isNegativeYBiggerThanX(void);
    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator+(const double &other) const;
    Vector2 operator-(const double &other) const;
    Vector2 operator*(const double &other) const;
    Vector2 operator/(const double &other) const;
    void operator+=(const Vector2 &other);
    void operator-=(const Vector2 &other);
    void operator+=(const double &other);
    void operator-=(const double &other);
    void operator*=(const double &other);
    void operator/=(const double &other);
    friend Vector2 operator+(const double &left, const Vector2 &right);
    friend Vector2 operator-(const double &left, const Vector2 &right);
    friend Vector2 operator*(const double &left, const Vector2 &right);
    friend Vector2 operator/(const double &left, const Vector2 &right);
};
