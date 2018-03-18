#ifndef __PRORES_ENCODER_HPP__
#define __PRORES_ENCODER_HPP__

#include "defs.hpp"

#include <memory>

class ProResEncoder
{
public:
    ProResEncoder(unsigned short width, unsigned short height, int interlaced, int quality, int cs, AllocFunc alloc);
    ~ProResEncoder();
public:
    bool encode(const ProRes::RawFrame * input, ProRes::CompressedFrame * output);
private:
    void encodeHeader();
private:
    unsigned short m_width;
    unsigned short m_height;
    int m_interlaced;
    int m_quality;
    int m_cs;

    unsigned int m_maxSize;
    unsigned int m_avgSize;

    AllocFunc m_alloc;

    std::shared_ptr<void> m_header;
    std::shared_ptr<void> m_frame;
};

#endif //__PRORES_ENCODER_HPP__


