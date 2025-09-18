#pragma once
#include <cstdint>
using size_t = std::size_t;

#include <array>
#include <complex>
#include <fstream>
#include <iostream>

struct RGB {
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
	RGB(uint8_t red, uint8_t green, uint8_t blue);
};

struct Color {
	double hue;
	double saturation;
	double value;
	Color();
	Color(uint32_t val);
	Color(double hue, double saturation, double value);

	auto to_rgb() const -> RGB;
	auto lerp(const Color&, double) const -> Color;
};

class Point {
      public:
	long double x;
	long double y;

	Point(long double x, long double y);
};

template <size_t width, size_t height> class Canvas {
      public:
	size_t m_width = width;
	size_t m_height = height;
	double x_max;
	double x_min;
	double y_max;
	double y_min;
	std::array<Color, width * height> pixels;
	Canvas(double min_x, double max_x, double min_y, double max_y)
	    : x_max(max_x), x_min(min_x), y_max(max_y), y_min(min_y)
	{
	}

	Canvas(Point p, long double size)
	{
		auto delta = size / 2.0;
		x_max = p.x + delta;
		x_min = p.x - delta;
		y_max = p.y + delta;
		y_min = p.y - delta;
	}

	auto save_to_ppm(const char* file_path) const -> void
	{
		auto f =
		    std::fstream(file_path, std::ios::binary | std::ios::out);
		f << "P6\n" << width << " " << height << " 255\n";
		for (auto const& color : pixels) {
			auto c = color.to_rgb();
			uint8_t rgb[3] = {c.Red, c.Green, c.Blue};
			f << rgb[1] << rgb[2] << rgb[3];
		}
		f.close();
	}

	auto coordinate(size_t index) const -> std::complex<long double>
	{
		return std::complex<long double>(
		    std::lerp(x_min, x_max,
			      (index % width) / (long double)width),
		    std::lerp(y_min, y_max,
			      ((long double)index / height) / height));
	}

	auto construct(auto op) -> void
	{
#pragma omp parallel for
		for (size_t idx = 0; idx < width * height; idx++)
			pixels[idx] = op(coordinate(idx));
	}

	auto operator[](size_t index) -> Color&
	{
		return pixels[index];
	}

	auto operator()(size_t row, size_t col) -> Color&
	{
		return pixels[row * width + col];
	}
};
