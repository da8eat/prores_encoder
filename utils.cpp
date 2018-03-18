#include "utils.hpp"
#include "defs.hpp"

bool isValidQuality(int quality)
{
    return quality >= ProRes::Quality::_422Proxy && quality <= ProRes::Quality::_4444XQ;
}

bool isValidFieldOrder(int interlaced)
{
    return interlaced >= ProRes::FieldOrder::Progressive && interlaced <= ProRes::FieldOrder::BottomFieldFirst;
}

bool isValidColorSpace(int cs)
{
    switch (cs)
    {
    case ProRes::ColorSpace::yuv8_422_planar:
    case ProRes::ColorSpace::yuv10_422_planar:
    case ProRes::ColorSpace::yuv16_422_planar:
    case ProRes::ColorSpace::ayuv16_444_planar:
        return true;
    default:
        return false;
    }
}

