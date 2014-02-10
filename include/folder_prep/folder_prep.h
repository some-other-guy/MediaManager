#ifndef FOLDER_PREP_H_
#define FOLDER_PREP_H_

#include "common.h"
#include "file_handlers/filehandler.h"

class FolderPrep
{
public:
    ~FolderPrep();
    FolderPrep( FileHdlr* configuration );

    void prepare();

private:
    FileHdlr* _configuration;

    static const std::string SUBDIR_TAG;
    static const std::string ROOTDIR_TAG;
};
#endif /* FOLDER_PREP_H_ */
