#ifndef CSVFILEHANDLER_H_
#define CSVFILEHANDLER_H_

#include "common.h"
#include "filehandler.h"
#include "../logger/logger.h"

class CsvFileHdlr : public FileHdlr
{
public:
    ~CsvFileHdlr();
    CsvFileHdlr( std::string filename, uint32_t columns );

    void load();
    void write();
    void add( std::string& value );

private:
    uint32_t _number_columns;
    Hexx::VecContainer_t _items;

    static const std::string LOGGER_NAME_STR;
};
#endif /* CSVFILEHANDLER_H_ */
