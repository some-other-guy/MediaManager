#include <boost/filesystem.hpp>
#include "folder_prep/folder_prep.h"

const std::string FolderPrep::SUBDIR_TAG( "Hexx.ScanDirectories.Directory" );
const std::string FolderPrep::ROOTDIR_TAG( "Hexx.MountPoint" );

FolderPrep::~FolderPrep(){}
FolderPrep::FolderPrep( FileHdlr* configuration ) :
    _configuration( configuration )
{
    prepare();
}

void FolderPrep::prepare()
{
    if( 0 != _configuration )
    {
        uint32_t num_dirs_to_make = _configuration->count_instances( SUBDIR_TAG );
        if( 0 < _configuration->count_instances( ROOTDIR_TAG ))
        {
            for( uint32_t i = 0; i < num_dirs_to_make; i++ )
            {
                boost::filesystem::path directory( _configuration->get_instance_value( ROOTDIR_TAG ) +
                    Hexx::SLASH_STR + _configuration->get_instance_value( SUBDIR_TAG, i ));
                if( !boost::filesystem::exists( directory ))
                {
                    boost::filesystem::create_directories( directory );
                }
            }
        }
    }
}
