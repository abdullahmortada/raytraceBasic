#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3
{
public:
    double e[3] = {0,0,0};
    
    vec3() = default;
    vec3(double e0, double e1, double e2) 
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double &operator[](int i) { return e[i]; }

    vec3 &operator+=(const vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 &operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 &operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    std::ostream &operator<<(std::ostream &out)
    {
        return out << e[0] << ' ' << e[1] << ' ' << e[2];
    }

    vec3 operator * (const vec3 &u)
    {
        return vec3(u.e[0] * e[0], u.e[1] * e[1], u.e[2] * e[2]);
    }

    vec3 operator / (const double t)
    {
        return vec3(e[0] / t, e[1] / t, e[2] / t);
    }

    double length() const
    {
        return sqrt(length_2());
    }

    double length_2() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    bool near_zero() const
    {
        const double s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    inline static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());        
    }

    inline static vec3 random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

inline double dot(const vec3 &u, const vec3 &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 normalize(vec3 u)
{
    return u / u.length();
}

inline vec3 rand_in_sphere()
{
    while(true)
    {
        vec3 p = vec3::random(-1, 1);
        if(p.length_2() >= 1) continue;
       
        return normalize(p);
    }
}

vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

vec3 operator*(const vec3& u,const double t)
{
    return vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

vec3 operator*(const double t, const vec3 &u)
{
    return vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v,n) * n;
}

vec3 refract(const vec3& v, const vec3 &n, double ratio_eta)
{
    double cos_theta = fmin(dot(-v, n), 1.0);
    vec3 r_perp = ratio_eta * (v + cos_theta*n);
    vec3 r_parallel = -sqrt(fabs(1.0 - r_perp.length_2())) * n;
    return r_perp + r_parallel;
}
// Type aliases for vec3
using point3 = vec3; // 3D point
using color = vec3;  // RGB color

#endif