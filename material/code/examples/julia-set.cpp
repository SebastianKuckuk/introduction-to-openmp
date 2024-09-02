#include <chrono>
#include <complex>
#include <iostream>

#include "lodepng.h"


int main(int argc, char *argv[]) {
    // default parameters
    size_t nx = 1024;  // number of points in x direction
    size_t ny = 1024;  // number of points in y direction

    // override with command line arguments
    int i = 1;
    if (argc > i) nx = atoi(argv[i]);
    ++i;
    if (argc > i) ny = atoi(argv[i]);
    ++i;
    
    // allocate data
    auto image = new unsigned char[4 * nx * ny];

    // Julia set parameters
    std::complex<double> c(-0.7, 0.27015);
    auto maxIterations = 256;

    // start measurement
    auto start = std::chrono::steady_clock::now();

    // compute the Julia set for each pixel
    for (size_t j = 0; j < ny; ++j) {
        for (size_t i = 0; i < nx; ++i) {
            // compute pixel coordinates to [-2, 2]
            double real = (i - 0.5 * nx) / (0.5 * nx);
            double imag = (j - 0.5 * ny) / (0.5 * ny);
            std::complex<double> z(real, imag);

            // compute the Julia set value
            int it = 0;
            while (it < maxIterations && std::abs(z) < 2.0) {
                z = z * z + c;
                ++it;
            }
            auto juliaValue = static_cast<unsigned char>(255 * it / maxIterations);

            // apply color mapping and store in the image
            auto index = 4 * (j * nx + i);
            image[index + 0] = juliaValue;       // Red channel
            image[index + 1] = 0;                // Green channel
            image[index + 2] = 255 - juliaValue; // Blue channel
            image[index + 3] = 255;              // Alpha channel (fully opaque)
        }
    }

    // finish measurement
    auto end = std::chrono::steady_clock::now();
    auto elapsedSeconds = std::chrono::duration<double>(end - start);

    std::cout << "  #cells:       " << nx * ny << "\n";
    std::cout << "  elapsed time: " << 1e3 * elapsedSeconds.count() << " ms\n";
    std::cout << "  MLUP/s:       " << 1e-6 * nx * ny / elapsedSeconds.count() << "\n";

    // save the image using lodepng
    lodepng::encode("julia.png", image, nx, ny);
    std::cout << "  image saved as julia.png" << std::endl;

    // clean up
    delete[] image;

    return 0;
}
