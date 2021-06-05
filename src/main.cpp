#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>
#include <fstream>

double intersect_sphere(const point3& circle_center,
                      const double circle_radius,
                      const Ray& r) {
    Vec3 orig_circle_vec = r.origin() - circle_center;
    auto a = r.direction().length_squared();
    auto half_b = dot(r.direction(), orig_circle_vec);
    auto c = orig_circle_vec.length_squared() - circle_radius * circle_radius;
    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        // return smallest real t (closest hitpoint on sphere).
        return (-half_b - std::sqrt(discriminant)) / a;
    }
}

color ray_color(const Ray& r) {
    double t = intersect_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        // Vec3 light_dir(0, 0, 1);
        Vec3 normal = unit_vector(r.at(t) - Vec3(0, 0, -1));
        // x, y, z component in [0, 1].
        return 0.5*color(normal.x()+1, normal.y()+1, normal.z()+1);
        // auto diffuse_intensity = dot(light_dir, normal);
        // return color(1, 0, 0) * diffuse_intensity;
    }
    // Background gradient coloring
    Vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}


int main()
{
    std::ofstream ppm_file;
    ppm_file.open("../images/image.ppm");

    // Image parameters
    const double aspect_ratio = 16.0 / 9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width / aspect_ratio);

    // Camera settings
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);

    // Image rendering with PPM image format
    ppm_file << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for (int row = img_height-1; row >= 0; --row) {
        std::cout << "\rScanlines remaining: " << row << ' ' << std::flush;
        for (int col = 0; col < img_width; ++col) {
            /*auto r = double(col) / (img_width-1);
            auto g = double(row) / (img_height-1);
            auto b = 0.9;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            ppm_file << ir << ' ' << ig << ' ' << ib << '\n';*/

            // color pixel_color(double(col) / (img_width-1), double(row) / (img_height-1), 0.5);
            // color pixel_color(0.5, 0.7, 1.0);
            auto u = double(col) / (img_width-1);
            auto v = double(row) / (img_height-1);
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(ppm_file, pixel_color);
        }
    }
    std::cout << "\nRendering complete.\n";
    ppm_file.close();

    return 0;
}
