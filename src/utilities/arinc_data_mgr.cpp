#include "utilities/arinc_data_mgr.h"

ArincDataMgr::~ArincDataMgr(){}
ArincDataMgr::ArincDataMgr( std::string data_filename ) :
    _file_hdlr( data_filename )
{
    while( _file_hdlr.has_next() )
    {
        arinc::packet* arinc_packet = _file_hdlr.get_next();
        if( 0 != arinc_packet )
            _data_hdlrs.push_back( ArincDataHdlrFactory::make_hdlr( arinc_packet ));
    }
}
