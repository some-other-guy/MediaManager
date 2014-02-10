#ifndef MEDIA_MANAGER_H_
#define MEDIA_MANAGER_H_

#include "common.h"
#include "logger/logger.h"
#include <boost/function.hpp>
#include "file_handlers/xmlfilehandler.h"

class MediaManager
{
public:
    ~MediaManager();
    MediaManager( int argc, char** argv, std::string configfile );

    void parse_args( int argc, char** argv );

    void quit();
    void backup();
    void file_rename();
    void prep_folder();
    void display_usage();
    void generate_manifest();
    void display_main_menu();

protected:

private:
    typedef std::map<std::string, boost::function<void()> > OptionsContainer_t;

    Logger _logger;
    FileHdlr* _configuration;
    OptionsContainer_t _options_map;

    static const std::string LOGGER_NAME;

    static const std::string OPTION_QUIT;
    static const std::string OPTION_BACKUP;
    static const std::string OPTION_FILE_RENAME;
    static const std::string OPTION_PREP_FOLDER;
    static const std::string OPTION_DISPLAY_USAGE;
    static const std::string OPTION_GENERATE_MANIFEST;
};
#endif /* MEDIA_MANAGER_H_ */
