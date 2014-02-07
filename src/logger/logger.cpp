#include <iostream>

#include "logger/logger.h"

Logger::~Logger(){}
Logger::Logger( std::string name, Logger::LoggerVolume volume ) :
    _name( name ), _volume( volume ){}

void Logger::log( std::string msg, LoggerVolume volume )
{
    if( _volume >= volume )
        std::cout << _name << ": " << msg << std::endl;
}
