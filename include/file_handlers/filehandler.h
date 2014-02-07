#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include "common.h"
#include "logger/logger.h"

class FileHdlr
{
public:
    enum FileHdlrType
    {
        FILE_HDLR_CSV,
        FILE_HDLR_INI,
        FILE_HDLR_XML,
        FILE_HDLR_UNKNOWN
    };

    virtual ~FileHdlr();
    FileHdlr( std::string loggerName, std::string filename, FileHdlr::FileHdlrType type );

    virtual void write();
    virtual std::string get_filename() const;
    virtual void set_root_tag( std::string& tag );
    virtual uint32_t count_instances( std::string key );
    virtual std::string get_instance_value( std::string key, uint32_t instance = 0 );

    virtual void add( std::string& value );
    virtual void add( std::string& value, std::string& tag );

protected:
    Logger _logger;
    std::string _filename;
    bool _write_on_destroy;
    FileHdlr::FileHdlrType _type;
};

class FileHdlrFactory
{
public:
    // Create a FileHdlr to read an existing file from disk
    // File type is determined by the extention of filename.
    static FileHdlr* make_file_handler( std::string filename, uint32_t columns );
    static FileHdlr* make_file_handler( std::string filename, std::string root_tag = "" );
};
#endif /* FILEHANDLER_H_ */
