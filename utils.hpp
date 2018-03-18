#ifndef __PRORES_UTILS_HPP__
#define __PRORES_UTILS_HPP__

bool isValidQuality(int quality);
bool isValidFieldOrder(int interlaced);
bool isValidColorSpace(int cs);

//store integer to buffer
template <class T>
void writeInteger(void * buffer, const T & v)
{
    unsigned char * buf = static_cast<unsigned char *>(buffer);

    if (!buf)
    {
        return;
    }

    for (size_t i = 0; i < sizeof(T); ++i)
    {
        buf[i] = (v >> (sizeof(T) - i - 1)) & 0xff;
    }
}

#endif //__PRORES_UTILS_HPP__


