#include "mandelbrot.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <vector>

int main()
{
	// static auto canvas = Canvas<2000, 2000>(-2.0, 0.47, -1.235, 1.235);
	static auto canvas = Canvas<1500, 1500>(Point(-1.4021230042960, 0), 0.000'000'000'01);


	static auto histogram = [] {
		std::array<Color, 255> ret_arr{};
		const auto begin = Color(182, 0.00, 0.0);
		const auto end = Color(1.0, 1.00, 1.0);
		auto t = 1;
		for (auto & c : ret_arr)
			c = begin.lerp(end, (double)t / 255.0), ++t;

		return ret_arr;
	}();

	auto mandelbrot = [](std::complex<long double> coordinate) {
		const auto max_iteration = 20000ul;
		auto x = 0.0L;
		auto y = 0.0L;
		auto x_squared = 0.0L;
		auto y_squared = 0.0L;
		auto iteration = 0u;

		while (std::islessequal((x_squared + y_squared), 4) &&
		       (iteration < max_iteration)) {
			y = fma(2 * x, y, coordinate.imag());
			x = x_squared - y_squared + coordinate.real();
			x_squared = x * x;
			y_squared = y * y;
			iteration++;
		}

		return histogram[iteration & 0xFF];
	};

	canvas.construct(mandelbrot);
	canvas.save_to_ppm("image.ppm");

	return 0;
}
