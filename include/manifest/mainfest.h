#ifndef MAINFEST_GENERATOR_H_
#define MAINFEST_GENERATOR_H_

#include "logger/logger.h"
#include "file_handlers/filehandler.h"
#include <boost/property_tree/ptree.hpp>

class Manifest
{
public:
    ~Manifest();
    Manifest( FileHdlr* configuration );

    void generate();

protected:
    void add_to_manifest( std::string& entry );
    void scan_directory( std::string& subdir );

private:
    Logger _logger;
    FileHdlr* _manifest;
    FileHdlr* _configuration;

    static const std::string LOGGER_NAME;
    static const std::string MANIFEST_FILENAME;
    static const std::string MANIFEST_ROOT_TAG;
    static const std::string MANIFEST_ENTRY_TAG;
    static std::string MANIFEST_FULL_PATH_TAG;
};
#endif /* MAINFEST_GENERATOR_H_ */
