#ifndef __VECTORS_HPP__
#define __VECTORS_HPP__

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cmath>

template <typename T>
class Vec3
{
    public:
        Vec3() : x(0), y(0), z(0) {}
        Vec3(T value) : x(value), y(value), z(value) {}
        Vec3(T xValue, T yValue, T zValue) : x(xValue), y(yValue), z(zValue) {}

        Vec3<T> operator + (const Vec3<T> &v) const
        {
            return Vec3<T>(x + v.x, y + v.y, z + v.z);
        }
        Vec3<T> operator - (const Vec3<T> &v) const
        {
            return Vec3<T>(x - v.x, y - v.y, z - v.z);
        }
        Vec3<T> operator - () const
        {
            return Vec3<T>(-x, -y, -z);
        }
        Vec3<T> operator * (const T &r) const
        {
            return Vec3<T>(x*r, y*r, z*r);
        }
        friend Vec3<T> operator * (const T &r, const Vec3<T> &v)
        {
            return Vec3<T>(r*v.x, r*v.y, r*v.z);
        }
        Vec3<T> operator / (const T &r) const
        {
            T factor = T(1)/r;
            return Vec3<T>(x*factor, y*factor, z*factor);
        }
        T dotProduct(const Vec3<T> &v) const
        {
            return x*v.x + y*v.y + z*v.z;
        }
        Vec3<T> crossProduct(const Vec3<T> &v) const
        {
            return Vec3<T>(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
        }
        T norm() const
        {
            return (x*x + y*y + z*z);
        }
        Vec3<T>& normalize()
        {
            T norm = x*x + y*y + z*z;
            if(norm > T(0))
            {
                T factor = 1/T(std::sqrt(norm));
                x *= factor, y *= factor, z *= factor;
            }
            return *this;
        }
        T length() const
        {
            T norm = x*x + y*y + z*z;
            return T(std::sqrt(norm)); 
        }
        const T& operator [] (uint8_t i) const
        {
            return (&x)[i];
        }
        T& operator [] (uint8_t i)
        {
            return (&x)[i];
        }
        friend std::ostream& operator << (std::ostream &stream, const Vec3<T> &v)
        {
            return stream << '(' << v.x << ' ' << v.y << ' ' << v.z << ')';
        }
    
    public:
        T x, y, z;
};

template <typename T>
class Vec4
{
    public:
        Vec4() : x(0), y(0), z(0), w(0) {}
        Vec4(T value) : x(value), y(value), z(value), w(value) {}
        Vec4(T xValue, T yValue, T zValue, T wValue) : x(xValue), y(yValue), z(zValue), w(wValue) {}
        Vec4(const Vec3<T> &v, T wValue) : x(v.x), y(v.y), z(v.z), w(wValue) {}
        
        Vec4<T> operator + (const Vec4<T> &v) const
        {
            return Vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
        }
        Vec4<T> operator - (const Vec4<T> &v) const
        {
            return Vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
        }
        Vec4<T> operator - () const
        {
            return Vec4<T>(-x, -y, -z, -w);
        }
        Vec4<T> operator * (const T &r) const
        {
            return Vec4<T>(x*r, y*r, z*r, w*r);
        }
        friend Vec4<T> operator * (const T &r, const Vec4<T> &v)
        {
            return Vec4<T>(r*v.x, r*v.y, r*v.z, r*v.w);
        }
        Vec4<T> operator / (const T &r) const
        {
            T factor = T(1)/r;
            return Vec4<T>(x*factor, y*factor, z*factor, w*factor);
        }
        T dotProduct(const Vec4<T> &v) const
        {
            return x*v.x + y*v.y + z*v.z + w*z.w;
        }
        T norm() const
        {
            return x*x + y*y + z*z + w*w;
        }
        Vec4<T>& normalize()
        {
            T norm = x*x + y*y + z*z + w*w;
            if(norm > T(0))
            {
                T factor = 1/T(std::sqrt(norm));
                x *= factor, y *= factor, z *= factor, w *= factor;
            }
            return *this;
        }
        T length() const
        {
            T norm = x*x + y*y + z*z + w*w;
            return T(std::sqrt(norm));
        }
        const T& operator [] (uint8_t i) const
        {
            return (&x)[i];
        }
        T& operator [] (uint8_t i)
        {
            return (&x)[i];
        }
        friend std::ostream& operator << (std::ostream &stream, const Vec4<T> &v)
        {
            return stream << '(' << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << ')';
        }
    
    public:
        T x, y, z, w;
};

typedef Vec3<float> Vec3f;
typedef Vec3<int32_t> Vec3i;

typedef Vec4<float> Vec4f;
typedef Vec4<int32_t> Vec4i;



#endif
