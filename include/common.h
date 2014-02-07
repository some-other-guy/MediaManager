#ifndef COMMON_H
#define COMMON_H

#include <map>
#include <string>
#include <vector>
#include <stdint.h>
#include "utilities/utility_functions.h"

namespace Hexx
{
    typedef std::vector<std::string> StrContainer_t;
    typedef std::vector<StrContainer_t> VecContainer_t;
    typedef std::map<std::string, StrContainer_t> StrMap_t;

    typedef std::vector<std::string>::iterator StrContainerItr_t;
    typedef std::vector<StrContainer_t>::iterator VecContainerItr_t;
    typedef std::map<std::string, StrContainer_t>::iterator StrMapItr_t;

    static const std::string EMPTY_STR( "" );
    static const std::string SLASH_STR( "/" );
    static const std::string XML_ROOT_TAG( "Hexx" );
    static const std::string BACK_SLASH_STR( "\\" );
    static const std::string CSV_TAG_SEPERATOR( "," );
    static const std::string XML_TAG_SEPERATOR( "." );
    static const std::string BIN_EXTENTION_STR( ".dat" );
    static const std::string CSV_EXTENTION_STR( ".csv" );
    static const std::string XML_EXTENTION_STR( ".xml" );
}
#endif
