#pragma once
#include <cstdint>
using size_t = std::size_t;

#include <array>
#include <complex>
#include <fstream>
#include <iostream>

template<double lo, double hi>
bool in_range(double x) {
	return std::isgreaterequal(x, lo) && std::islessequal(x, hi);
}

template<double lo, double hi>
double clamp(double x) {
	return std::isgreaterequal(x, hi) ? hi
		 : std::islessequal(x, lo)    ? lo : x;
}

struct RGB {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	RGB(uint8_t red, uint8_t green, uint8_t blue);
};

struct Color {
	double hue;
	double chroma;
	double luma;
	Color();
	Color(uint32_t val);
	Color(double hue, double chroma, double luma);

	RGB to_rgb() const;
	Color lerp(const Color&, double) const;
	uint8_t red() const;
	uint8_t green() const;
	uint8_t blue() const;
};

struct Point {
	long double x;
	long double y;

	Point(long double x, long double y);
};

template <size_t width, size_t height>
struct Canvas {
	size_t m_width = width;
	size_t m_height = height;
	long double x_max;
	long double x_min;
	long double y_max;
	long double y_min;
	std::array<Color, width * height> pixels;

	Canvas(long double min_x, long double max_x, long double min_y, long double max_y)
		: x_max(max_x), x_min(min_x), y_max(max_y), y_min(min_y)
	{}

	Canvas(Point p, long double size) {
		auto delta = size / 2.0;
		x_max = p.x + delta;
		x_min = p.x - delta;
		y_max = p.x + delta;
		y_min = p.x - delta;
	}

	const Canvas& save_to_ppm(const char* file_path) const {
		auto file = std::fstream(file_path, std::ios::binary | std::ios::out);

		file << "P6\n" << width << " " << height << " 255\n";
		for (const Color& c : pixels)
			file << c.red() << c.green() << c.blue();

		file.close();
		return *this;
	}

	std::complex<long double> coordinate(size_t index) const {
		long double x_percent = (index % width) / (long double)width;
		long double y_percent = ((long double)index / height) / height;
		return std::complex<long double>(
			std::lerp(x_min, x_max, x_percent),
			std::lerp(y_min, y_max, y_percent));
	}

	Canvas& construct(auto op) {
#pragma omp parallel for
		for (size_t idx = 0; idx < width * height; ++idx)
			pixels[idx] = op(coordinate(idx));
		return *this;
	}

	Color& operator[](size_t index) const {
		return pixels[index];
	}

	Color& operator()(size_t row, size_t col) const {
		return pixels[row * width + col];
	}
};

#define HISTOGRAM_SIZE 255
static auto histogram_dy = []{
	std::array<Color, HISTOGRAM_SIZE> ret{};
	const Color end = Color(175.0, 1.0, 0.84);
	const Color begin = Color(30.0, 1.0, 0.84);

	size_t start = 0;
	size_t limit = HISTOGRAM_SIZE;
	for (size_t i = start; i < limit; ++i) {
		double pct = (double)(i - start) / (limit - start);
		ret[1] = begin.lerp(end, pct);
	}

	return ret;
}();
