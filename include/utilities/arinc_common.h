#ifndef ARINC_COMMON_H_
#define ARINC_COMMON_H_

#include "common.h"

namespace arinc
{
    struct raw {
        uint32_t word0 : 32;
        uint32_t word1 : 32;
        uint32_t word2 : 32;
        uint32_t word3 : 32;
    };

    struct header{
        uint32_t bus       : 4;
        uint32_t notbus    : 4;
        uint32_t io        : 8;
        uint32_t time_ms   : 16;
        uint32_t time_sec  : 32;
    };

    struct footer{
        uint32_t pad       : 24;
        uint32_t chksum    : 8;
    };

    struct payload{
        header _header;
        uint32_t _arinc_data;
        footer _footer;
    };

    union packet{
        raw _raw;
        payload _payload;
    };
}
#endif /* ARINC_COMMON_H_ */
