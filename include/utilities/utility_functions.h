#ifndef UTILITY_FUNCTIONS_H_
#define UTILITY_FUNCTIONS_H_

#include <string>
#include "common.h"

class Utility
{
public:
    static void to_lower( std::string& str );
    static void to_upper( std::string& str );
    static void convert_to_slashes( std::string& str );
    static void get_user_input( std::string& msg, std::string& input );
    static void remove_root_string( std::string& str, std::string& remove_string );

private:
    static const std::string DEFAULT_MSG_STR;
};
#endif /* UTILITY_FUNCTIONS_H_ */
