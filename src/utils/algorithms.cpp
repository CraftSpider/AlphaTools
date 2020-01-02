
#include "utils/algorithms.h"

namespace util {

static uint crc_table[256];
static const uint crc_start = 0xFFFFFFFFul;

static void gen_crc32_table() {
    for (uint i = 0; i < 256; ++i) {
        uint crc = i;
        for (uint j = 0; j < 8; ++j) {
            if (crc & 1u) crc = (crc >> 1u) ^ 0xEDB88320u;
            else crc = crc >> 1u;
        }
        crc_table[i] = crc;
    }
}

uint crc32(const uchar *input, const ulong length) {
    static int init = (gen_crc32_table(), 0);
    (void)init;
    
    uint crc = crc_start;
    if (input != nullptr) {
        for (ulong a = 0; a < length; ++a) {
            crc = (crc >> 8u) ^ crc_table[(crc ^ input[a]) & 0xFFu];
        }
    }
    return crc ^ crc_start;
}

}
