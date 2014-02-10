#ifndef BACKUP_H_
#define BACKUP_H_

#include "common.h"
#include "logger/logger.h"
#include "file_handlers/filehandler.h"

class Backup
{
public:
    ~Backup();
    Backup( FileHdlr* configuration );

    void perform_backup();
    void copy_to_backup();
    void scan_directory( std::string& src );

private:
    Logger _logger;
    FileHdlr* _configuration;

    static const std::string LOGGER_NAME;
    static const std::string CONFIG_FILE_TYPE;
    static const std::string CONFIG_MOUNT_POINT;
    static const std::string CONFIG_BACKUP_ROOT;
    static const std::string CONFIG_SUBDIRECTORY;
};
#endif /* BACKUP_H_ */
