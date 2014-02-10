#include "common.h"
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include "file_handlers/xmlfilehandler.h"
#include <boost/property_tree/xml_parser.hpp>

const std::string XmlFileHdlr::LOGGER_NAME_STR( "XmlFileHdlrLogger" );

XmlFileHdlr::~XmlFileHdlr()
{
    if( _write_on_destroy )
        write();
    if( 0 != _proptree )
        delete _proptree;
}

XmlFileHdlr::XmlFileHdlr( std::string filename, std::string& root ) : FileHdlr(
    LOGGER_NAME_STR, filename, FileHdlr::FILE_HDLR_XML ),
    _root_tag( root ), _proptree( 0 )
{
    if( !_root_tag.empty() )
        load();
}

void XmlFileHdlr::write()
{
    using namespace boost::filesystem;
    using namespace boost::property_tree;

    if( 0 != _proptree )
        delete _proptree;
    try
    {
        _proptree = new ptree();
        Hexx::StrMapItr_t itr = _items.begin();
        for( ; itr != _items.end(); ++itr )
        {
            Hexx::StrContainerItr_t listItr = itr->second.begin();
            for( ; listItr != itr->second.end(); ++listItr )
            {
                _proptree->add( itr->first, *listItr );
            }
        }

        if( !exists( boost::filesystem::path( _filename ).parent_path() ))
        {
            boost::filesystem::create_directories(  boost::filesystem::path( _filename ).parent_path() );
        }
        boost::property_tree::xml_writer_settings<char> settings( '\t', 1 );
        write_xml( _filename, *_proptree, std::locale(), settings );
    }
    catch( std::exception& ex )
    {
        _logger.log( ex.what() );
    }
}

void XmlFileHdlr::set_write_on_destroy( bool save )
{
    _write_on_destroy = save;
}

FileHdlr::FileHdlrType XmlFileHdlr::get_type() const
{
    return _type;
}

std::string XmlFileHdlr::get_filename() const
{
    return _filename;
}

void XmlFileHdlr::set_root_tag( std::string& tag )
{
    _root_tag.assign( tag );
}

uint32_t XmlFileHdlr::count_instances( std::string key )
{
    uint32_t instances = 0;
    if( _items.end() != _items.find( key ))
    {
        instances = _items[key].size();
    }
    return instances;
}

std::string XmlFileHdlr::get_instance_value( std::string key, uint32_t instance )
{
    std::string value;
    if( _items.end() != _items.find( key ))
    {
        if( count_instances( key ) > instance )
            value.assign( _items[key].at( instance ));
    }
    return value;
}

void XmlFileHdlr::add( std::string& value, std::string& tag )
{
    _items[tag].push_back( value );
}

void XmlFileHdlr::load()
{
    using namespace boost::property_tree;

    if( 0 != _proptree )
        delete _proptree;
    try
    {
        _proptree = new ptree();
        read_xml( _filename, *_proptree );
        iterate_ptree( _root_tag );
    }
    catch( std::exception& ex )
    {
        _logger.log( ex.what() );
    }
}

void XmlFileHdlr::iterate_ptree( std::string root_tag )
{
    using namespace boost::property_tree;

    BOOST_FOREACH( ptree::value_type& value, _proptree->get_child( root_tag ))
    {
        if( !value.second.empty() )
        {
            // There are sub elements that need to be handled.
            iterate_ptree( root_tag + Hexx::XML_TAG_SEPERATOR + value.first );
        }
        else
        {
            // There are no sub-elements so get the data
            _items[root_tag + Hexx::XML_TAG_SEPERATOR + value.first].push_back( value.second.data() );
        }
    }
}

bool XmlFileHdlr::has_key( std::string key )
{
    bool found = false;
    if( _items.end() != _items.find( key ))
        found = true;
    return found;
}

bool XmlFileHdlr::has_value( std::string key, std::string value )
{
    bool found = false;
    if( has_key( key ))
    {
        if( _items[key].end() != std::find( _items[key].begin(), _items[key].end(), value ))
            found = true;
    }
    return found;
}
