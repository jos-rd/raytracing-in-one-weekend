#ifndef SPHERE_H
#define SPHERE_H

#include "traceable.h"
#include "vec3.h"

class Sphere : public Traceable {
public:
    Sphere() {}
    Sphere(point3 c, double r) : center(c), radius(r) {}

    virtual bool hit(const Ray& r,
                     double t_min,
                     double t_max,
                     intersection_info& intersect_info) const override;
public:
    point3 center;
    double radius;
};


bool Sphere::hit(const Ray& r,
            double t_min,
            double t_max,
            intersection_info& intersect_info) const {
    Vec3 orig_circle_vec = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(r.direction(), orig_circle_vec);
    auto c = orig_circle_vec.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) {
        return false;
    }
    auto srqt_discr = std::sqrt(discriminant);
    // return smallest real t (closest hitpoint on sphere) in acceptable range [t_min,t_max].
    auto root = (-half_b - srqt_discr) / a; // smallest root
    if (root < t_min || t_max < root) {
        root = (-half_b + srqt_discr) / a; // largest root
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    // Save intersection info
    intersect_info.t = root;
    intersect_info.p = r.at(root);
    Vec3 outward_normal = (intersect_info.p - center) / radius;
    intersect_info.set_face_normal(r, outward_normal);

    return true;
}

#endif // SPHERE_H
