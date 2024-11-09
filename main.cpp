#include <iostream>
#include "color.h"
#include "ray.h"
#include "vec3.h"

double hit_sphere(const point3 &center, double radius, const ray &r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto h = dot(r.direction(), oc);
    // auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    // auto discriminant = b * b - 4 * a * c;
    auto discriminant = h * h - a * c;
    // return (discriminant > 0);
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / (2.0 * a);
    }
}

color ray_color(const ray &r) {
    // return color(0, 0, 0);
    // if (hit_sphere(point3(0, 0, -1), 0.5, r)) {
    //     return color(1, 0, 0);
    // }
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);

    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.5, 1.0);
}

int main(int argc, char **argv) {
    // std::cout << "test !" << std::endl;
    // int image_width = 256;
    // int image_height = 256;
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // auto viewport_height = 2.0;
    // auto viewport_width = viewport_height * (double(image_width) / image_height);

    // camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    const auto camera_center = point3(0, 0, 0);

    // cal vector across the horizontal and down the vertical viewport edges
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // cal the horizontal and vertical delta vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // cal the location of the upper left pixel
    auto viewport_upper_left =
        camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // auto r = double(i) / (image_width - 1);
            // auto g = double(j) / (image_height - 1);
            // auto b = 0.0;

            // int ir = int(255.999 * r);
            // int ig = int(255.999 * g);
            // int ib = int(255.999 * b);

            // std::cout << ir << " " << ig << " " << ib << "\n";
            // 2
            // auto pixel_color =
            //     color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
            // write_color(std::cout, pixel_color);
            //
            // 3
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone  \n";

    return 0;
}
