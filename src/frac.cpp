#include "frac.hpp"
#include <array>
#include <cmath>
#include <cassert>

RGB::RGB(uint8_t red, uint8_t green, uint8_t blue)
	: red(red), green(green), blue(blue) {}

Color::Color()
	: hue(0.0), chroma(0.0), luma(0.0) {}

Color::Color(double hue, double chroma, double luma)
	: hue(hue), chroma(chroma), luma(luma) {
		this->chroma = clamp<0.0, 1.0>(chroma);
		this->luma = clamp<0.0, 1.0>(luma);
		this->hue = fmod(hue, 360.0);
}

Color::Color(uint32_t val)
	: hue(0.0), chroma(0.0), luma((double)val / 255.0) {}

RGB Color::to_rgb() const {
	double cube_hue = hue / 60.0;
	double tmp = chroma * (1.0 - fabs(fmod(cube_hue, 2.0) - 1.0));

	std::array<double, 3> components =
		cube_hue < 1.0 ? std::array{chroma, tmp, 0.0} :
		cube_hue < 2.0 ? std::array{tmp, chroma, 0.0} :
		cube_hue < 3.0 ? std::array{0.0, chroma, tmp} :
		cube_hue < 4.0 ? std::array{0.0, tmp, chroma} :
		cube_hue < 5.0 ? std::array{tmp, 0.0, chroma} :
		/* otherwise  */ std::array{chroma, 0.0, tmp};
	if (cube_hue == 6) components = std::array{0.0,0.0,0.0};

	double match = luma - (0.3 * components[0] + 0.59 * components[1] + 0.11 * components[2]);
	for (double& component : components)
		component = round((component + match) * 255);

	return RGB(components[0], components[1], components[2]);
}

uint8_t Color::red() const {
	return to_rgb().red;
}

uint8_t Color::green() const {
	return to_rgb().green;
}

uint8_t Color::blue() const {
	return to_rgb().blue;
}

Color Color::lerp(const Color& rhs, double t) const {
	return Color(
		std::lerp(hue, rhs.hue, t),
		std::lerp(chroma, rhs.chroma, t),
		std::lerp(luma, rhs.luma, t));
}

Point::Point(long double x, long double y)
	: x(x), y(y) {}
