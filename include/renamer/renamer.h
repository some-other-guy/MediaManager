#ifndef RENAMER_H_
#define RENAMER_H_

#include "logger/logger.h"
#include "file_handlers/filehandler.h"

class Renamer
{
public:
    ~Renamer();
    Renamer( FileHdlr* configuration, std::string& mappings );

private:
    Logger _logger;
    FileHdlr* _configuration;
    std::string _mapping_file;

    static const std::string LOGGER_NAME;
};
#endif /* RENAMER_H_ */
