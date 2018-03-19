#ifndef __PRORES_DEFS_HPP__
#define __PRORES_DEFS_HPP__

struct ProRes
{
    struct Quality
    {
        enum
        {
            _422Proxy,
            _422LT,
            _422,
            _422HQ,
            _4444,
            _4444XQ
        };
    };

    struct FieldOrder
    {
        enum
        {
            Progressive,
            TopFieldFirst,
            BottomFieldFirst
        };
    };

    struct ColorSpace
    {
        enum
        {
            yuv8_422_planar,
            yuv10_422_planar,
            yuv16_422_planar,
            ayuv16_444_planar,
        //todo
        };
    };

    struct SourceColorSpace
    {
        enum
        {
            Unknown = 0,
            uyvy,
            v210,
            v216,

        };
    };

    struct FrameRate
    {
        enum
        {
            Unknown = 0,
            _23976,
            _24,
            _25,
            _2997,
            _30,
            _50,
            _5994,
            _60,
            _100,
            _11988,
            _120
        };
    };

    struct AspectRatio
    {
        enum {
            Unknown = 0,
            _1x1 = 1,
            _4x3 = 2,
            _16x9 = 3
        };
    };

    struct ColorPrimaries
    {
        enum
        {
            ITU709 = 1,
            Unknown = 2,
            ITU601_625 = 5,
            ITU601_525 = 6,
            ITU2020 = 9,
        };
    };

    struct TransferCharacteristic
    {
        enum
        {
            ITU709 = 1,
            Unknown = 2,
            ST2084_PQ = 16,
            BT2100_HLG = 18,
        };
    };

    struct MatrixCoefficients
    {
        enum
        {
            ITU709 = 1,
            Unknown = 2,
            ITU601 = 6,
            ITU202 = 9,

        };
    };

    struct RawFrame
    {
        void ** plane;
        unsigned int * stride;
        unsigned int planes;
    };

    struct CompressedFrame
    {
        void * buffer;
        unsigned int size;
    };

    //
};

typedef void (* AllocFunc)(void * handle, void ** buffer, unsigned int size);

#endif //__PRORES_DEFS_HPP__

