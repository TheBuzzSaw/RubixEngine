#ifndef POINT_HPP
#define POINT_HPP

#include "Rational.hpp"

template<typename T>
struct Point
{
    T x;
    T y;

    Point& operator+=(const Point& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

template<typename T>
constexpr Point<T> operator+(const Point<T>& a, const Point<T>& b)
{
    return { a.x + b.x, a.y + b.y };
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Point<T>& p)
{
    return stream << '(' << p.x << ", " << p.y << ')';
}

template<typename T>
constexpr Point<T> Divided(const Point<Rational<T>>& p)
{
    return { p.x.a / p.x.b, p.y.a / p.y.b };
}

template<typename T>
constexpr bool operator==(const Point<T>& a, const Point<T>& b)
{
    return a.x == b.x && a.y == b.y;
}

template<typename T>
constexpr bool operator!=(const Point<T>& a, const Point<T>& b)
{
    return a.x != b.x || a.y != b.y;
}

template<typename T>
constexpr T LengthSquared(const Point<T>& p)
{
    return p.x * p.x + p.y * p.y;
}

using Point8 = Point<int8_t>;
using Point16 = Point<int16_t>;
using Point32 = Point<int32_t>;
using Point64 = Point<int64_t>;

#endif
