#include <string>
#include <3ds.h>
#include <sf2d.h>
#include "BmpFont.h"
#include "Common.h"
#include "Slider.h"

extern BmpFont mainFont;
extern int keys;

Slider::Slider()
{
	value = 0.0;
	min = 0.0;
	max = 1.0;
}

Slider::Slider(double min, double max)
{
	value = min;
	this->min = min;
	this->max = max;
}

void Slider::TouchingAnywhere(int x, int y)
{
	value = Interpolate((double)x, 1.0, (double)(width - 2), min, max);
	
	if (keys & (KEY_L | KEY_R)) {
		if (value < min) min = value;
		else if (value > max) max = value;
	} else {
		if (value < min) value = min;
		else if (value > max) value = max;
	}
}

void Slider::Draw(int x, int y, int w, int h)
{
	width = w;
	int fillWidth = (int)Interpolate(value, min, max, 0.0, (double)(w - 2));
	sf2d_draw_rectangle_gradient(x+1, y+1, w-2, h-2, RGBA8(0xF0, 0xF0, 0xF0, 0xFF), RGBA8(0xFF, 0xFF, 0xFF, 0xFF), SF2D_TOP_TO_BOTTOM);
	sf2d_draw_rectangle(x+1, y+1, fillWidth, h-2, RGBA8(0x00, 0xCC, 0xFF, 0xFF));
    mainFont.drawStr(ssprintf("%.5f", value), x + 8, y + h/2 - mainFont.height()/2, RGBA8(0x00, 0x00, 0x00, 0xFF));
    sf2d_draw_rectangle_gradient(x+1, y+1, w-2, h/2-2, RGBA8(0xFF, 0xFF, 0xFF, 0x20), RGBA8(0xFF, 0xFF, 0xFF, 0x60), SF2D_TOP_TO_BOTTOM);
}

void Slider::TouchingInside(int x, int y)
{
	Control::TouchingInside(x, y);
	TouchingAnywhere(x, y);
}

void Slider::TouchingOutside(int x, int y)
{
	Control::TouchingOutside(x, y);
	TouchingAnywhere(x, y);
}

void Slider::SetRange(double min, double max)
{
	if (min > max) std::swap(min, max);
	this->min = min;
	this->max = max;
}

void Slider::SetMinimum(double min)
{
	if (min < max) this->min = min;
}

void Slider::SetMaximum(double max)
{
	if (max > min) this->max = max;
}

double Slider::GetMinimum() const
{
	return min;
}

double Slider::GetMaximum() const
{
	return max;
}