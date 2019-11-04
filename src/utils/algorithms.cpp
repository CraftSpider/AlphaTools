
#include "utils/algorithms.h"

namespace util {

uint crc_table[256];
const uint crc_start = 0xFFFFFFFFul;
bool crc_invoked = false;

void gen_crc32_table() {
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
    if (!crc_invoked) {
        gen_crc32_table();
        crc_invoked = true;
    }
    
    uint crc = crc_start;
    if (input != nullptr) {
        for (ulong a = 0; a < length; ++a) {
            crc = (crc >> 8u) ^ crc_table[(crc ^ input[a]) & 0xFFu];
        }
    }
    return crc ^ crc_start;
}

}
