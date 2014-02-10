#include <iostream>
#include "utilities/utility_functions.h"

const std::string Utility::DEFAULT_MSG_STR( "Enter a value: " );

void Utility::to_lower( std::string& str ){}
void Utility::to_upper( std::string& str ){}

void Utility::convert_to_slashes( std::string& str )
{
    for( uint32_t i = 0; i < str.size(); i++ )
    {
        if( 0 == Hexx::BACK_SLASH_STR.compare( str.substr( i, 1 )))
        {
            str.replace( i, 1, Hexx::SLASH_STR );
        }
    }
}

void Utility::get_user_input( std::string& msg, std::string& input )
{
    if( msg.empty() )
    {
        msg.assign( DEFAULT_MSG_STR );
    }
    std::cout << msg << " ";
    std::cin >> input;
}

void Utility::remove_root_string( std::string& str, const std::string& remove_string )
{
    if( !remove_string.empty() && str.npos != str.find( remove_string ))
    {
        str.erase( 0, remove_string.size() );
    }
}
