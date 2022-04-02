#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.hpp"

class Camera
{
    public:
        Camera(double vfov, double aspect_ratio, point3 lookfrom, point3 lookat, vec3 vup)
        {
            double theta = degrees_to_radians(vfov);
            double h = tan(theta/2);
            double viewport_height = 2.0 * h;
            double viewport_width = aspect_ratio * viewport_height;

            vec3 w = normalize(lookfrom - lookat);
            vec3 u = normalize(cross(vup, w));
            vec3 v = cross(w,u);

            origin = lookfrom;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
        }

        ray get_ray(double u, double v) const
        {
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};

#endif