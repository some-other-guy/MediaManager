// DEBUG ONLY -- REMOVE
#include <sstream>
// END DEBUG

#include <boost/foreach.hpp>
#include "manifest/mainfest.h"
#include <boost/filesystem.hpp>
#include <boost/property_tree/xml_parser.hpp>

const std::string Manifest::MANIFEST_ENTRY_TAG( "Entry" );
const std::string Manifest::LOGGER_NAME( "MainfestLogger" );
const std::string Manifest::MANIFEST_ROOT_TAG( "Manifest" );
const std::string Manifest::MANIFEST_FILENAME( "manifest.xml" );
std::string Manifest::MANIFEST_FULL_PATH_TAG(
    Hexx::XML_ROOT_TAG + Hexx::XML_TAG_SEPERATOR + MANIFEST_ROOT_TAG + Hexx::XML_TAG_SEPERATOR + MANIFEST_ENTRY_TAG );

Manifest::~Manifest(){}
Manifest::Manifest( FileHdlr* configuration ) :
    _logger( LOGGER_NAME ), _manifest( 0 ), _configuration( configuration )
{
    generate();
}

void Manifest::generate()
{
    using namespace boost::filesystem;

    if( 0 != _configuration )
    {
        uint32_t numDirs = _configuration->count_instances( "Hexx.ScanDirectories.Directory" );
        std::string dirBase =
            _configuration->get_instance_value( "Hexx.MountPoint" );

        for( uint32_t i = 0; i < numDirs; i++ )
        {
            std::string absDir( dirBase + _configuration->get_instance_value( "Hexx.ScanDirectories.Directory", i ));
            if( exists( absDir ) && is_directory( absDir ))
            {
                scan_directory( absDir );
            }
        }

        if( 0 != _manifest )
            _manifest->write();
    }
}

void Manifest::add_to_manifest( std::string& entry )
{
    if( 0 == _manifest )
    {
        std::string dirBase =
            _configuration->get_instance_value( "Hexx.MountPoint" ) +
            _configuration->get_instance_value( "Hexx.MetadataDirectory" ) + "/" +
            MANIFEST_FILENAME;
        _manifest = FileHdlrFactory::make_file_handler( dirBase, Hexx::EMPTY_STR );
    }
    _manifest->add( entry, MANIFEST_FULL_PATH_TAG );
}

void Manifest::scan_directory( std::string& subdir )
{
    using namespace boost::filesystem;

    directory_iterator end_itr;
    for( directory_iterator dir_itr( subdir ); dir_itr != end_itr; ++dir_itr )
    {
        if( is_regular_file( dir_itr->path() ))
        {
            if( _configuration->has_value( "Hexx.FileTypes.Extention", dir_itr->path().extension().string() ))
            {
                std::string entry( dir_itr->path().string() );
                add_to_manifest( entry );
            }
        }
        else
        {
            std::string subdirectory( dir_itr->path().string() );
            scan_directory( subdirectory );
        }
    }
}
