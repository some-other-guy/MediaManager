#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

class Logger
{
public:
    enum LoggerVolume
    {
        LOUD,
        WHISPER,
        SILENT
    };

    ~Logger();
    Logger( std::string name, Logger::LoggerVolume volume = LOUD );

    void log( std::string msg, LoggerVolume volume = LOUD );

private:
    std::string _name;
    LoggerVolume _volume;
};
#endif /* LOGGER_H_ */
