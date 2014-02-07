#include "common.h"
#include <boost/filesystem.hpp>
#include "file_handlers/filehandler.h"
#include "file_handlers/csvfilehandler.h"
#include "file_handlers/xmlfilehandler.h"


FileHdlr::~FileHdlr(){}
FileHdlr::FileHdlr( std::string loggerName, std::string filename, FileHdlr::FileHdlrType type ) :
    _logger( loggerName ), _filename( filename ), _write_on_destroy( true ), _type( type ){}

void FileHdlr::write(){}
void FileHdlr::add( std::string& value ){}
void FileHdlr::set_root_tag( std::string& tag ){}
void FileHdlr::add( std::string& value, std::string& tag ){}

std::string FileHdlr::get_filename() const{ return _filename; }
uint32_t FileHdlr::count_instances( std::string key ){ return 0; }
std::string FileHdlr::get_instance_value( std::string key, uint32_t instance){ return std::string( "" ); }

FileHdlr* FileHdlrFactory::make_file_handler( std::string filename, uint32_t columns )
{
    using namespace boost::filesystem;

    path file( filename );
    std::string extention = file.extension().string();

    FileHdlr* filehdlr = 0;
    if( 0 == extention.compare( Hexx::CSV_EXTENTION_STR ))
    {
        filehdlr = new CsvFileHdlr( filename, columns );
    }
    return filehdlr;
}

FileHdlr* FileHdlrFactory::make_file_handler( std::string filename, std::string root_tag )
{
    using namespace boost::filesystem;

    path file( filename );
    std::string extention = file.extension().string();

    FileHdlr* filehdlr = 0;
    if( 0 == extention.compare( Hexx::XML_EXTENTION_STR ))
    {
        filehdlr = new XmlFileHdlr( filename, root_tag );
    }
    return filehdlr;
}
