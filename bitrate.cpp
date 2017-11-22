#include "encoder.hpp"

#include <algorithm>

static const unsigned int RESOLUTION_ITEMS = 8;

static const unsigned int resolutions[RESOLUTION_ITEMS] =
{
	720 * 486,
	720 * 576,
	960 * 720,
	1280 * 720,
	1440 * 1080,
	1920 * 1080,
	2048 * 1152,
	0x7fff * 0x7fff
};

static const unsigned int byterates[RESOLUTION_ITEMS] = 
{
	288 * 1024,
	336 * 1024,
	432 * 1024,
	504 * 1024,
	864 * 1024,
	1008 * 1024,
	1152 * 1024,
	0 //last one
};

static const unsigned int pr_qual_scale[][2] = 
{
	{13, 63}, //proxy
	{13, 28}, //lt
	{2, 3}, //422
	{1, 1}, //hq
	{3, 2}, //4444
	{9, 4}, //xq
};

std::pair<unsigned int, unsigned int> RateControl::frameSize(int quality, unsigned int width, unsigned int height, int alpha)
{
	unsigned int max = 0;
	unsigned int avg = 0;

	unsigned int pixels = width * height;

	unsigned int size = 0;
	const unsigned int * res = 
		std::lower_bound(&resolutions[0], &resolutions[RESOLUTION_ITEMS - 1], pixels);

	size = byterates[res - &resolutions[0]];
	if (size == 0)
	{
		size = pixels / 2;
	}

	max = size * pr_qual_scale[quality][0] / pr_qual_scale[quality][1];

	max &= 0xfffff000;
	avg = 8 * max / 9;

	if (quality >= Quality::_4444 && alpha)
	{
		max += 3 * pixels; //too much, but its what apple has
	}

	return std::make_pair(avg, max);
}
