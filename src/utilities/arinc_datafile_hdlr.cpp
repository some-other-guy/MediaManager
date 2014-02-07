#include <fstream>
#include <iostream>
#include "utilities/arinc_datafile_hdlr.h"

ArincDataFileHdlr::~ArincDataFileHdlr(){}
ArincDataFileHdlr::ArincDataFileHdlr( std::string src_file ) :
    _num_bytes( 0 ), _src_file( src_file ), _current_byte( 0 )
{
    load();
}

void ArincDataFileHdlr::load()
{
    char buffer[1];
    std::ifstream file_stream( _src_file.c_str(), std::ios::binary );
    while( !file_stream.eof() )
    {
        file_stream.read( buffer, 1 );
        _bytes.push_back( buffer[0] );
    }

    // Setup the initial byte offsets.
    // Ignore all bytes before a start byte where the lower 4 bits == !the upper 4 bits
    _current_byte = find_start_byte();
    _num_bytes = _bytes.size() - _current_byte;

    // Trim any dangling bits on the end that do not add up to a complete
    // packet ( 16 bytes )
    _num_bytes = _num_bytes - ( _num_bytes % sizeof( arinc::packet ));
}

bool ArincDataFileHdlr::has_next()
{
    return ( _num_bytes > _current_byte );
}

arinc::packet* ArincDataFileHdlr::get_next()
{
    arinc::packet* ret_pckt = 0;
    if( _num_bytes > _current_byte )
    {
        ret_pckt = new arinc::packet();
        ret_pckt->_raw.word0 = _bytes[_current_byte + 0] |
            ( _bytes[_current_byte + 1] << 8 ) |
            ( _bytes[_current_byte + 2] << 16 ) |
            ( _bytes[_current_byte + 3] << 24 );
        ret_pckt->_raw.word1 = _bytes[_current_byte + 4] |
            ( _bytes[_current_byte + 5] << 8 ) |
            ( _bytes[_current_byte + 6] << 16 ) |
            ( _bytes[_current_byte + 7] << 24 );
        ret_pckt->_raw.word2 = _bytes[_current_byte + 8] |
            ( _bytes[_current_byte + 9] << 8 ) |
            ( _bytes[_current_byte + 10] << 16 ) |
            ( _bytes[_current_byte + 11] << 24 );
        ret_pckt->_raw.word3 = _bytes[_current_byte + 12] |
            ( _bytes[_current_byte + 13] << 8 ) |
            ( _bytes[_current_byte + 14] << 16 ) |
            ( _bytes[_current_byte + 15] << 24 );
        _current_byte += 16;
    }
    return ret_pckt;
}

uint32_t ArincDataFileHdlr::find_start_byte()
{
    bool found = false;
    uint32_t start = 0;
    while( !found && start < _bytes.size() )
    {
        uint8_t lower = _bytes[start] & 0x0F;
        uint8_t upper = ( ~( _bytes[start] ) & 0xF0 ) >> 4;
        if( lower == upper )
            found = true;
        else
            start++;
    }
    std::cout << "First Byte to consider: " << start << std::endl;
    return start;
}
