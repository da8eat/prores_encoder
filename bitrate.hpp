#ifndef __PRORES_BITRATE_HPP__
#define __PRORES_BITRATE_HPP__

#include <utility>

class RateControl
{
public:
	static std::pair<unsigned int, unsigned int> frameSize(int quality, unsigned int width, unsigned int height, int alpha);
};

#endif //__PRORES_BITRATE_HPP__


