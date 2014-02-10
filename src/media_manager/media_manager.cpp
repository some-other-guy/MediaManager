#include <stdint.h>
#include <iostream>
#include <boost/bind.hpp>
#include "logger/logger.h"
#include "renamer/renamer.h"
#include "manifest/mainfest.h"
#include "folder_prep/folder_prep.h"
#include "media_manager/media_manager.h"

const std::string MediaManager::LOGGER_NAME( "MediaManagerLogger" );

const std::string MediaManager::OPTION_QUIT( "-q" );
const std::string MediaManager::OPTION_FILE_RENAME( "-r" );
const std::string MediaManager::OPTION_PREP_FOLDER( "-p" );
const std::string MediaManager::OPTION_DISPLAY_USAGE( "-h" );
const std::string MediaManager::OPTION_GENERATE_MANIFEST( "-g" );

MediaManager::~MediaManager(){}
MediaManager::MediaManager( int argc, char** argv, std::string configfile ) :
    _logger( LOGGER_NAME ), _configuration( 0 )
{
    _options_map[OPTION_QUIT] = boost::bind( &MediaManager::quit, this );
    _options_map[OPTION_FILE_RENAME] = boost::bind( &MediaManager::file_rename, this );
    _options_map[OPTION_PREP_FOLDER] = boost::bind( &MediaManager::prep_folder, this );
    _options_map[OPTION_DISPLAY_USAGE] = boost::bind( &MediaManager::display_usage, this );
    _options_map[OPTION_GENERATE_MANIFEST] = boost::bind( &MediaManager::generate_manifest, this );

    _configuration = FileHdlrFactory::make_file_handler( configfile, Hexx::XML_ROOT_TAG );

    parse_args( argc, argv );
}


void MediaManager::parse_args( int argc, char** argv )
{
    if( 1 == argc )
    {
        display_main_menu();
    }
    else
    {
        if( _options_map.end() != _options_map.find( argv[1] ))
            ( _options_map[argv[1]] )();
        else
            display_usage();
    }
}

void MediaManager::quit()
{
    _logger.log( "Thanks for playing" );
}

void MediaManager::file_rename()
{
    std::string mapping_file;
    Renamer renamer( _configuration, mapping_file );
}

void MediaManager::prep_folder()
{
    FolderPrep fp( _configuration );
}

void MediaManager::display_usage()
{
    std::cout << "MediaManager [option:arguments]" << std::endl;
}

void MediaManager::generate_manifest()
{
    Manifest manifest( _configuration );
}

void MediaManager::display_main_menu()
{
    std::string user_response;

    std::cout << "Media Manager Main Menu:" <<std::endl;
    std::cout << "g - Generate Manifest File" << std::endl;
    std::cout << "r - Rename Files" << std::endl;
    std::cout << "q - Quit" << std::endl;
    std::cout << "Pick an option: ";
    std::cin >> user_response;
    user_response.insert( 0, "-" );
    if( _options_map.end() != _options_map.find( user_response))
        ( _options_map[user_response] )();
}

