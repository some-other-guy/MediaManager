#ifndef ARINC_DATA_FILE_HDLR_H_
#define ARINC_DATA_FILE_HDLR_H_

#include "utilities/arinc_common.h"

class ArincDataFileHdlr
{
public:
    ~ArincDataFileHdlr();
    ArincDataFileHdlr( std::string src_file );

    void load();
    bool has_next();
    arinc::packet* get_next();

protected:
    uint32_t find_start_byte();

private:
    uint64_t _num_bytes;
    std::string _src_file;
    uint64_t _current_byte;
    std::vector<uint8_t> _bytes;
};
#endif
