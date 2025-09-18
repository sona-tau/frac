#include "mandelbrot.hpp"
#include <cmath>
#include <fstream>
#include <utility>
#include <array>

RGB::RGB(uint8_t red, uint8_t green, uint8_t blue)
	: Red(red)
	, Green(green)
	, Blue(blue)
{
}

Color::Color() : hue(0.0), saturation(0.0), value(0.0)
{
}

Color::Color(double hue, double saturation, double value)
	: hue(hue)
	, saturation(saturation)
	, value(value)
{
}

Color::Color(uint32_t val)
	: hue(0.0)
	, saturation(0.0)
{
	value = (double) val / 255.0;
}

auto Color::to_rgb() const -> RGB
{
	auto chroma = saturation * value;
	auto cube_hue = hue / 60.0;
	auto tmp = chroma * (1.0 - fabs(fmod(cube_hue, 2.0) - 1.0));

	auto components = std::array{ 0.0, 0.0, 0.0 };
	if (cube_hue < 1.0)
		components = { chroma, tmp, 0.0 };
	else if (cube_hue < 2.0)
		components = { tmp, chroma, 0.0 };
	else if(cube_hue < 3.0)
		components = { 0.0, chroma, tmp };
	else if(cube_hue < 4.0)
		components = { 0.0, tmp, chroma };
	else if(cube_hue < 5.0)
		components = { tmp, 0.0, chroma };
	else
		components = { chroma, 0.0, tmp };

	auto match = value - chroma;
	for (auto& component : components)
		component += match, component *= 255;

	const auto c = RGB(round(components[0]), round(components[1]), round(components[2]));

	// std::cout << round(components[0]) << " " << round(components[1]) << " " << round(components[2]) << std::endl;

	return c;
}

auto Color::lerp(const Color& rhs, double t) const -> Color
{

	return Color(std::lerp(hue, rhs.hue, t), std::lerp(saturation, rhs.saturation, t), std::lerp(value, rhs.value, t));
}

Point::Point(long double x, long double y)
	: x(x)
	, y(y)
{
}
