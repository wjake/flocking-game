#ifndef VEC_H_
#define VEC_H_

#include <cmath>

/**
 * @brief A 2D vector class
 * @tparam T The type of the vector
 */
template <class T = float>
class Vec2
{
public:
    T m_x, m_y;

    Vec2() : m_x(0), m_y(0) {}
    Vec2(T _x, T _y) : m_x(_x), m_y(_y) {}

    Vec2<T> operator+(const Vec2<T>& _vec) const
    {
        return Vec2<T>(m_x + _vec.m_x, m_y + _vec.m_y);
    }

    Vec2<T> operator-(const Vec2<T>& _vec) const
    {
        return Vec2<T>(m_x - _vec.m_x, m_y - _vec.m_y);
    }

    Vec2<T> operator*(const T& _scalar) const
    {
        return Vec2<T>(m_x * _scalar, m_y * _scalar);
    }

    Vec2<T> operator/(const T& _scalar) const
    {
        return Vec2<T>(m_x / _scalar, m_y / _scalar);
    }

    Vec2<T>& operator+=(const Vec2<T>& _scalar)
    {
        m_x += _scalar.m_x;
        m_y += _scalar.m_y;
        return *this;
    }

    Vec2<T>& operator*=(const T& _scalar)
    {
        m_x *= _scalar;
        m_y *= _scalar;
        return *this;
    }

    Vec2<T>& operator/=(const T& _scalar)
    {
        m_x /= _scalar;
        m_y /= _scalar;
        return *this;
    }

    bool operator==(const Vec2<T>& _vec) const {
        return m_x == _vec.m_x && m_y == _vec.m_y;
    }

    bool operator!=(const Vec2<T>& _vec) const
    {
        return m_x != _vec.m_x || m_y != _vec.m_y;
    }

    T magnitude() const
    {
        return sqrt(m_x * m_x + m_y * m_y);
    }

    Vec2<T> normalise() const
    {
        float mag = magnitude();
        if (mag > 0)
            return *this / mag;
        return Vec2<T>(0, 0);
    }
};

#endif