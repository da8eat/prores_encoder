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
            uyvy = 1,
            v210 = 2,
            v216 = 3,
            r408 = 4,
            v408 = 5,
            r4fl = 6,
            rgb8 = 7,
            BGRA = 8,
            n302 = 9,
            b64a = 10,
            R10k = 11,
            l302 = 12,
            y408 = 13,
            y416 = 14,
            r210 = 15
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

    struct AlphaType
    {
        enum
        {
            NoAlpha = 0,
            Alpha8bit = 1,
            Alpha16bit = 2
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

    struct QuantMatrix
    {
        unsigned char Luma255[] =
        {
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03,
            0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x04,
            0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04,
        };

        unsigned char Luma63[] =
        {
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03,
            0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x04,
            0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04,
        };
    };

    //
};

typedef void (* AllocFunc)(void * handle, void ** buffer, unsigned int size);

#endif //__PRORES_DEFS_HPP__

