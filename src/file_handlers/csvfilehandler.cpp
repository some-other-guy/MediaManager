#include <fstream>
#include <boost/filesystem.hpp>
#include "file_handlers/csvfilehandler.h"

const std::string CsvFileHdlr::LOGGER_NAME_STR( "CsvFileHdlrLogger" );

CsvFileHdlr::~CsvFileHdlr(){}
CsvFileHdlr::CsvFileHdlr( std::string filename, uint32_t columns ) : FileHdlr(
    LOGGER_NAME_STR, filename, FileHdlr::FILE_HDLR_CSV ),
    _number_columns( columns )
{
    if( boost::filesystem::exists( _filename ))
        load();
}


void CsvFileHdlr::load()
{

}


void CsvFileHdlr::write()
{
    using namespace boost::filesystem;

    if( !exists( boost::filesystem::path( _filename ).parent_path() ))
    {
        boost::filesystem::create_directories(  boost::filesystem::path( _filename ).parent_path() );
    }

    std::ofstream fileout( _filename.c_str() );
    if( fileout.is_open() )
    {
        for( uint32_t j = 0; j < _items.size(); j++ )
        {
            for( uint32_t idx = 0; idx < _items[j].size(); idx++ )
            {
                fileout << _items[j].at( idx );
                if(( idx + 1 ) < _items[j].size() )
                    fileout << Hexx::CSV_TAG_SEPERATOR;
                else
                    fileout << "\n";
            }
        }
        fileout.close();
    }
    else
    {
        _logger.log( "Unable to open CSV file" + _filename );
    }
}

void CsvFileHdlr::add( std::string& value )
{
    // First time adding an item so everything is empty
    // Add an empty Hexx::StrContainer_t to _items
    if( 0 == _items.size() )
        _items.push_back( Hexx::StrContainer_t() );

    Hexx::StrContainer_t& item = _items.back();
    item.push_back( value.c_str() );
    if( _number_columns == item.size() )
    {
        _items.push_back( Hexx::StrContainer_t() );
    }
}
