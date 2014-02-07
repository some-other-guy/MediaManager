#ifndef ARINC_DATA_MGR_H_
#define ARINC_DATA_MGR_H_

#include "utilities/arinc_data_hdlr.h"
#include "utilities/arinc_datafile_hdlr.h"

class ArincDataMgr
{
public:
    ~ArincDataMgr();
    ArincDataMgr( std::string data_filename );

private:
    ArincDataFileHdlr _file_hdlr;
    std::vector<ArincDataHdlr*> _data_hdlrs;
};
#endif /* ARINC_DATA_MGR_H_ */
