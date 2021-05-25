#include <iostream>
#include <fstream>

int main()
{
    std::ofstream ppm_file;
    ppm_file.open("../images/image.ppm");

    // Image parameters
    const int img_width = 256;
    const int img_height = 256;

    // Image rendering with PPM image format
    // std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";
    ppm_file << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for (int row = img_height-1; row >= 0; --row) {
        std::cout << "\rScanlines remaining: " << row << ' ' << std::flush;
        for (int col = 0; col < img_width; ++col) {
            auto r = double(col) / (img_width-1);
            auto g = double(row) / (img_height-1);
            auto b = 0.9;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            ppm_file << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cout << "\nRendering complete.\n";
    ppm_file.close();

    return 0;
}
