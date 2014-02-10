#include "backup/backup.h"
#include <boost/filesystem.hpp>

const std::string Backup::LOGGER_NAME( "BackupLogger" );
const std::string Backup::CONFIG_MOUNT_POINT( "Hexx.MountPoint" );
const std::string Backup::CONFIG_BACKUP_ROOT( "Hexx.BackupDirectory" );
const std::string Backup::CONFIG_FILE_TYPE( "Hexx.FileTypes.Extention" );
const std::string Backup::CONFIG_SUBDIRECTORY( "Hexx.ScanDirectories.Directory" );

Backup::~Backup(){}
Backup::Backup( FileHdlr* configuration ) :
    _logger( LOGGER_NAME ), _configuration( configuration )
{
    perform_backup();
}

void Backup::perform_backup()
{
    if( 0 != _configuration && _configuration->has_key( CONFIG_MOUNT_POINT ) && _configuration->has_key( CONFIG_BACKUP_ROOT ))
    {
        _logger.log( "Performing Backup from " +
            _configuration->get_instance_value( CONFIG_MOUNT_POINT ) + " to " +
            _configuration->get_instance_value( CONFIG_BACKUP_ROOT ) );
        copy_to_backup();
    }
    else
    {
        _logger.log( "Unable to backup ... missing configuration" );
    }
}

void Backup::copy_to_backup()
{
    using namespace boost::filesystem;

    for( uint32_t i = 0; i < _configuration->count_instances( CONFIG_SUBDIRECTORY ); i++ )
    {
        std::string src( _configuration->get_instance_value( CONFIG_MOUNT_POINT ) + Hexx::SLASH_STR +
            _configuration->get_instance_value( CONFIG_SUBDIRECTORY, i ));
        if( exists( src ))
        {
            scan_directory( src );
        }
    }
}

void Backup::scan_directory( std::string& src )
{
    using namespace boost::filesystem;
    directory_iterator end_itr;

    for( directory_iterator dir_itr( src ); dir_itr != end_itr; ++dir_itr )
    {
        std::string dst = src.c_str();
        Utility::remove_root_string( dst, _configuration->get_instance_value( CONFIG_MOUNT_POINT ));
        dst = _configuration->get_instance_value( CONFIG_BACKUP_ROOT ) + dst;

        if( is_directory( dir_itr->path() ))
        {
            _logger.log( "Directory " + dir_itr->path().string() );

            if( !exists( dst ))
                create_directories( dst );

            std::string newsrc = dir_itr->path().string();
            scan_directory( newsrc );
        }
        else
        {
            _logger.log( "File " + dir_itr->path().string() );

        }
    }
}
