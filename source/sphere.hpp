#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable
{
    public:
        sphere(){}
        sphere(point3 cen, double r, shared_ptr<material> m): center(cen), radius(r), mat_ptr(m) {};

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    vec3 oc = r.orig - center;
    double a = r.dir.length_2();
    double bover2 = dot(oc, r.dir);
    double c = oc.length_2() - radius*radius;

    double discrim = bover2*bover2 - a*c; 
    if(discrim < 0)
        return false;
    double sqrtd = sqrt(discrim);

    double root = (-bover2 - sqrtd) / a;
    if(root < t_min || root > t_max)
    {
        root = (-bover2 + sqrtd) / a;
        if (root < t_min || root > t_max)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 out_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, out_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif