#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>
#include <fstream>

bool intersect_sphere(const point3& circle_center,
                      const double circle_radius,
                      const Ray& r) {
    Vec3 orig_circle_vec = r.origin() - circle_center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(r.direction(), orig_circle_vec);
    auto c = dot(orig_circle_vec, orig_circle_vec) - circle_radius * circle_radius;
    return (b*b-4*a*c >= 0);
}

color ray_color(const Ray& r) {
    // Color the pixels of a sphere centered at (0, 0, -1) red.
    if (intersect_sphere(point3(0, 0, -1), 0.5, r)) {
        return color(1, 0, 0);
    }
    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
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
