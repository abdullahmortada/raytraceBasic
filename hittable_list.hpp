#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "hittable.hpp"

#include <memory>
#include <vector>

using std:: shared_ptr;
using std:: make_shared;

class hittable_list: public hittable
{
    public:
        hittable_list(){}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() {objects.clear();}
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    public:
        std::vector<shared_ptr<hittable> > objects;
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    hit_record temp;
    bool hit_anything = false;
    double closest = t_max;

    for(const auto& object : objects)
    {
        if(object ->hit(r, t_min, closest, temp))
        {
            hit_anything = true;
            closest = temp.t;
            rec = temp;
        }
    }

    return hit_anything;
}

#endif