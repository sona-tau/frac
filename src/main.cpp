#include "frac.hpp"

int main() {
	const auto mandelbrot_func = [&](std::complex<long double> coordinate) -> Color {
		long double x = 0.0;
		long double y = 0.0;
		long double x_squared = 0.0;
		long double y_squared = 0.0;

		std::uint64_t max_iter = 0;
		for (int i = 0; i < 20000 && std::islessequal(x_squared + y_squared, 4.0L); ++i) {

			y = fma(2 * x, y, coordinate.imag());
			x = x_squared - y_squared + coordinate.real();
			x_squared = x * x;
			y_squared = y * y;
			max_iter = i;
		}

		return histogram_dy[max_iter & 0xFF];
	};

	double zoom_level;
	static auto canvas = Canvas<1800, 1800>(Point(-1.459979, 0), zoom_level);
	canvas.construct(mandelbrot_func).save_to_ppm("image.ppm");

	return 0;
}
