#include "encoder.hpp"

#include "bitrate.hpp"
#include "utils.hpp"

#include <cstdlib>

static const unsigned int ALIGMENT = 64; //should be not less of sizeof(void *) as we use it to store real buffer

static const unsigned short FRAME_HEADER_SIZE = 148;
static const int FRAME_MAGIC = 'icpf';
static const unsigned int MAGIC_SIZE = 4;

void * aligned_memory_alloc(unsigned int size)
{
    void * buffer = malloc(size + ALIGMENT + ALIGMENT - 1);

    if (!buffer)
    {
        return 0;
    }

    size_t ptr = reinterpret_cast<size_t>(buffer) + ALIGMENT + ALIGMENT - 1;

    size_t mask = ~(static_cast<size_t>(ALIGMENT - 1));
    ptr &= mask;

    size_t ptr0 = ptr - ALIGMENT;
    *reinterpret_cast<size_t *>(ptr0) = reinterpret_cast<size_t>(buffer);
    return reinterpret_cast<void *>(ptr);
}

void aligned_memory_free(void * buffer)
{
    if (!buffer)
    {
        return;
    }

    size_t ptr = reinterpret_cast<size_t>(buffer);
    ptr -= ALIGMENT;
    buffer = reinterpret_cast<void *>(*reinterpret_cast<size_t *>(ptr));
    free(buffer);
}


ProResEncoder::ProResEncoder(unsigned short width, unsigned short height, int interlaced, int quality, int cs, AllocFunc alloc)
    : m_width(width)
    , m_height(height)
    , m_interlaced(interlaced)
    , m_quality(quality)
    , m_cs(cs)
    , m_alloc(alloc)
{
    if (!isValidQuality(m_quality) || !isValidFieldOrder(m_interlaced) || !isValidColorSpace(m_cs))
    {
        return false;
    }

    int alpha = static_cast<int>(m_cs == ProRes::ColorSpace::ayuv16_444_planar);
    static std::pair<unsigned int, unsigned int> avg_max = RateControl::frameSize(m_quality, m_width, m_height, alpha);//no alpha yet

    m_avgSize = avg_max.first;
    m_maxSize = avg_max.second;

    m_header.reset(aligned_memory_alloc(FRAME_HEADER_SIZE + MAGIC_SIZE + sizeof(MAGIC_SIZE)), aligned_memory_free);
    m_frame.reset(aligned_memory_alloc(m_maxSize - FRAME_HEADER_SIZE - MAGIC_SIZE - sizeof(MAGIC_SIZE)), aligned_memory_free);

    encodeHeader();
}

ProResEncoder::~ProResEncoder() {

}

bool ProResEncoder::encode(const ProRes::RawFrame * input, ProRes::CompressedFrame * output) {

}

void ProResEncoder::encodeHeader()
{
    unsigned char * header = static_cast<unsigned char *>(m_header.get());
    writeInteger<unsigned int>(header, 0);//we dont know size yet will be written at the end
    header += sizeof(MAGIC_SIZE);

    writeInteger(header, FRAME_MAGIC);
    header += MAGIC_SIZE;

    writeInteger(header, FRAME_HEADER_SIZE);
    header += sizeof(FRAME_HEADER_SIZE);

    //basically apple set version 0 for all 422 colorspaces and set version to 1 if cs 444 or we encode alpha
    unsigned short version = static_cast<unsigned short>(m_cs == ProRes::ColorSpace::ayuv16_444_planar);
    writeInteger(header, version);
    header += sizeof(version);

    int creator = 'acd0'; //I assume apple codec 0
    writeInteger(header, creator);
    header += sizeof(creator);

    writeInteger(header, m_width);
    header += sizeof(m_width);

    writeInteger(header, m_height);
    header += sizeof(m_height);

    unsigned char chroma_field_flags = ((2 + static_cast<unsigned char>(m_cs == m_cs == ProRes::ColorSpace::ayuv16_444_planar)) << 6) +
            static_cast<unsigned char>(m_interlaced);

    writeInteger(header, chroma_field_flags);
    header += sizeof(chroma_field_flags);

    //we dont set any info property on current stage as we dont really know
    // but there will be helper functions which allows to set needed info prop
    unsigned char ar_fps = ((ProRes::AspectRatio::Unknown) << 4) + ProRes::FrameRate::Unknown;

    writeInteger(header, ar_fps);
    header += sizeof(ar_fps);

    unsigned char primaries = ProRes::ColorPrimaries::Unknown;
    writeInteger(header, primaries);
    header += sizeof(primaries);

    unsigned char characteristic = ProRes::TransferCharacteristic::Unknown;
    writeInteger(header, characteristic);
    header += sizeof(characteristic);

    unsigned char matrix = ProRes::MatrixCoefficients::Unknown;
    writeInteger(header, matrix);
    header += sizeof(matrix);
}

