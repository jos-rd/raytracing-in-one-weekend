#ifndef TRACEABLE_H
#define TRACEABLE_H

#include "ray.h"

struct intersection_info {
    point3 p;
    Vec3 normal;
    double t;
    bool outward_face;

    inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        outward_face = dot(r.direction(), outward_normal) < 0;
        normal = outward_face ? outward_normal : -outward_normal;
    }
};

class Traceable {
public:
    virtual bool hit(const Ray& r,
                     double t_min,
                     double t_max,
                     intersection_info& intersect_info) const = 0;
};

#endif // TRACEABLE_H
