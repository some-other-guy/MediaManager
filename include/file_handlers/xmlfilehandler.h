#ifndef XMLFILEHANDLER_H_
#define XMLFILEHANDLER_H_

#include "common.h"
#include "filehandler.h"
#include "../logger/logger.h"
#include <boost/property_tree/ptree.hpp>

class XmlFileHdlr : public FileHdlr
{
public:
    ~XmlFileHdlr();
    XmlFileHdlr( std::string filename, std::string& root );

    void write();
    std::string get_filename() const;
    void set_root_tag( std::string& tag );
    void set_write_on_destroy( bool save );
    FileHdlr::FileHdlrType get_type() const;
    uint32_t count_instances( std::string key );
    std::string get_instance_value( std::string key, uint32_t instance = 0 );

    void add( std::string& value, std::string& tag );

    bool has_key( std::string key );
    bool has_value( std::string key, std::string value );


protected:
    void load();
    void iterate_ptree( std::string root_tag );

private:
    Hexx::StrMap_t _items;
    std::string _root_tag;
    boost::property_tree::ptree* _proptree;

    static const std::string LOGGER_NAME_STR;
};
#endif /* XMLFILEHANDLER_H_ */
