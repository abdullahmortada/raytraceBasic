#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.hpp"


class material
{
    public:
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const = 0;
};

class lambertian : public material
{
    public:
        lambertian(const color& a) : albedo(a) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            vec3 scatter_direction = rec.normal + rand_in_sphere();

            if(scatter_direction.near_zero())
                scatter_direction = rec.normal;
            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }
    public:
        color albedo;
};

class metal: public material
{
    public:
        metal(const color& a, double f): albedo(a), fuzz(f){}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override
        {
            vec3 reflected = reflect(normalize(r_in.dir), rec.normal);
            scattered = ray(rec.p, reflected + fuzz * rand_in_sphere());
            attenuation = albedo;
            return (dot(scattered.dir, rec.normal) > 0);
        }

    public:
        color albedo;
        double fuzz;
};

class dielectric: public material
{
    public:
        dielectric(double i): ir(i) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override
        {
            attenuation = color(1,1,1);
            double refr_ratio = rec.front_face? (1.0/ir) : ir;

            vec3 unit_dir = normalize(r_in.dir);
            double cos_theta = fmin(dot(-unit_dir, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = refr_ratio * sin_theta > 1.0;
            vec3 direction;

            if(cannot_refract || reflectance(cos_theta, refr_ratio) > random_double())
                direction = reflect(unit_dir, rec.normal);

            else
                direction = refract(unit_dir, rec.normal, refr_ratio);

            scattered = ray(rec.p, direction);
            return true;
        }
    public:
        double ir;
    
    private:
        static double reflectance(double cosine, double ref_idx)
        {
            double r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 *= r0;
            return r0 + (1 - r0) * pow(1 - cosine, 5);
        }
};
#endif