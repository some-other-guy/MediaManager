#ifndef ARINC_DATA_HDLR_H_
#define ARINC_DATA_HDLR_H_

#include "utilities/arinc_common.h"

class ArincDataHdlr
{
public:
    virtual ~ArincDataHdlr();
    ArincDataHdlr( arinc::packet* data );
};

class ArincDataHdlrFactory
{
public:
    static ArincDataHdlr* make_hdlr( arinc::packet* data );
};
#endif /* ARINC_DATA_HDLR_H_ */
