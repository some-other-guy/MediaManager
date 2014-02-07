#include "renamer/renamer.h"

const std::string Renamer::LOGGER_NAME( "RenamerLogger" );

Renamer::~Renamer(){}

Renamer::Renamer( FileHdlr* configuration, std::string& mappings ) :
    _logger( LOGGER_NAME ), _configuration( configuration ), _mapping_file( mappings.c_str() )
{
    // If the passed in mapping_file is an empty string then ask the user for the correct file.
    if( _mapping_file.empty() )
    {
        std::string msg = "Mapping File Name:";
        Utility::get_user_input( msg, _mapping_file );
    }
}
